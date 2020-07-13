#!/usr/bin/env python

#
# Created on Oct 27, 2011
#
# @author: ethan.li
#

import os

from dvbobjects.PSI.PAT import *
from dvbobjects.PSI.NIT import *
from dvbobjects.PSI.SDT import *
from dvbobjects.PSI.PMT import *
from dvbobjects.PSI.TDT import *
from dvbobjects.PSI.EMM import *
from dvbobjects.PSI.CAT import *

from dvbobjects.DVB.Descriptors import *
from dvbobjects.MPEG.Descriptors import *
from dvbobjects.DVB.DataCarousel import *

from dvt_base import *
from dvt_irdeto import *


class IrdetoSdlParser(object):
    ''''''
    __maxSsuModuleSize = 4066*65536
    
    def __init__(self, fullpath):
        ''''''
        self.__fullpath = fullpath
        self.__result = {}
        self.__sanityCheck()
        self.__fileObj = open(self.__fullpath, "rb")

    def __sanityCheck(self):
	
        if not os.path.exists(self.__fullpath):
			dvtError("CD5 file \"%s\" does not exist!!!" % self.__fullpath.strip())
        if ((os.path.getsize(self.__fullpath)) > self.__maxSsuModuleSize):
            dvtError("CD5 file \"%s\" exceeds the maximum size %d/%d!!!" % 
                        (self.__fullpath.strip(), os.path.getsize(self.__fullpath), self.__maxSsuModuleSize))
    
    def __getInteger(self, name, offset, length):
        ''''''
        
        try:
            self.__fileObj.seek(offset)
            string = self.__fileObj.read(length)
        except:
            raise dvtError("error access CD5 file!")
        return dvtNetBytesToInt(string)
    
    def __setResult(self, k, v):
        ''''''
        self.__result[k] = v
               
    def parse(self):
        ''''''
        
        if self.__getInteger("download_header_id", 0, 1) != 0x11:
            dvtError("Invalid CD5 file!!!")
        # manufacturer_id
        self.__setResult("manufacturer_id", self.__getInteger("manufacturer_id", 3, 2))
        # hardware_version
        self.__setResult("hardware_version", self.__getInteger("hardware_version", 5, 2))
        # variant
        self.__setResult("variant", self.__getInteger("variant", 11, 2))
        # sub_variant
        self.__setResult("sub_variant", self.__getInteger("sub_variant", 13, 2))
        # download_sequence_number
        self.__setResult("download_sequence_number", self.__getInteger("download_sequence_number", 23, 2))
        
    def getResult(self):
        ''''''
        return self.__result
        

class IrdetoEmmSection(Section):
    """Irdeto specific EMM section"""
    section_max_size = 1024
    
    table_id = 0x82
    section_syntax_indicator = 0
    DVB_reserved = 1
    ISO_reserved = 0
    
    def __sanity_check(self):
        dvtAssert(
            0 <= self.section_length <= self.section_max_size - 3, 
            "Invalid Irdeto EMM section length!!!"
            )
    
    def pack(self):
        __multilinecomment = """
        Irdeto EMM section format:
        table_id                    0x82 (8 bits)
        section_syntax_indicator    0b1 (1 bit)
        DVB_reserved                0b0 (1 bit)
        ISO_reserved                0b00 (2 bits)
        section_length              (12 bits)
        EMM structure               (section_length bytes)
        """
        # EMM payload
        body = self.pack_section_body()
        
        self.section_length = len(body)
        
        length_info_16 = (
            (self.section_syntax_indicator << 15)
            | (self.DVB_reserved << 14)
            | (self.ISO_reserved << 12)
            | (self.section_length)
            )
        
        self.__sanity_check()
        
        data = pack("!BH", 
                    self.table_id,
                    length_info_16
                    ) + body
                    
        return data
    
    def pack_section_body(self):
        return self.emm_structure
    
    
class irdeto_emm_loop_item(emm_loop_item):

    def pack(self):
        ''''''
        # pack program_loop_item
        fmt = "!B"
        return struct.pack(
                    fmt,
                    self.test,
                    )


class IrdetoEmmStruct(object):
    """"""
    CLIENT_BASED_ADDRESSING = ("UNIQUE", "UNIQUE_CAM", "GLOBAL")
    SECTOR_BASED_ADDRESSING = ("GLOABAL_SECTOR", "GROUP_UNIQUE", "GROUP", "SUPER_GROUP")
    ROUTING = {
               "SC" : 0, 
               "CAM" : 1, 
               "IRD" : 2
               }
    
    def __init__(self, address_type, address_bytes, routing):
        """"""
        # addressing
        self.addressing = 0    # 5 bits
        self.address_length = 0 # 3 bits
        self.address_bytes = address_bytes  # address_length bytes
        # flow control
        self.flow_control = 0x00C0 & (routing << 6)   # 2 bytes
        
    def pack(self):
        ''''''
        
        payload = self.packEmmPayload()
        
        header = struct.pack("!B",
                             self.addressing << 3 | 
                             self.address_length
                             )

        if self.address_length > 0:
            # TODO: addressing bytes
            pass
        header += struct.pack("!H",  
                              self.flow_control
                              )
        
        dvtPrintStrAsAscii("EMM Structure: 0x", (header + payload))
        return (header + payload)


class IrdetoGlobalEmmStruct(IrdetoEmmStruct):
    """"""
    
    def __init__(self, filterNumber, routing, destinationId):
        """"""
        super(IrdetoGlobalEmmStruct, self).__init__('GLOBAL', '', self.ROUTING[routing]) # Every child class MUST do it FIRST in __init__!!!
        self.addressing = filterNumber
        self.address_length = 0
        # IRD specific
        self.destination_id = destinationId
        self.message_data = ""
        self.crc16 = 0
        
        self.__sanity_check()
        
    def __sanity_check(self):
        dvtAssert(
            0x10 <= self.addressing <= 0x1F, 
            "Invalid Irdeto EMM filter number!!!"
            )
        
    def packEmmPayload(self):
        ''''''
        dataCrc = (
                   struct.pack("!H", self.destination_id << 12 | len(self.message_data))
                   + self.message_data
                   )
        msg = (
               dataCrc 
               + self.__crc16(dataCrc)
               )

        dvtPrintStrAsAscii("IRD EMM Payload: 0x", "%s" % (msg))
        return msg

    def __crc16(self, data):
        ''''''
        crc = irdetoCrc16(data)
        return struct.pack("!H", crc)


class IrdetoDownloadControlMessage(object):
    """"""
    message_type = 0
    
    def __init__(self):
        """"""
        self.download_allowed = 1
        self.forced_download = 1
        self.profdec_forced_download = 0
        
    def pack(self):
        ''''''
        return struct.pack("!BB",
                           self.message_type << 4, 
                           self.download_allowed << 7 | 
                           self.forced_download << 6 | 
                           self.profdec_forced_download << 5 |
                           0    # spare
                           )

class IrdetoMigrationMessage(object):
    """"""
    message_type = 7
    
    def __init__(self, variant = 0xFFFF, subVariant = 0xFFFF):
        """"""
        self.forced_download = 1
        self.include_new_variant = 1
        self.include_new_subvariant = 1
        self.new_variant = variant
        self.new_subvariant = subVariant
        
    def pack(self):
        ''''''
        return struct.pack("!BBBHH",
                           self.message_type << 4, 
                           self.forced_download << 6, 
                           self.include_new_variant << 7 | self.include_new_subvariant << 6, 
                           self.new_variant,
                           self.new_subvariant
                           )

class OCPackSectionObj(object):
    
    """
    DVB section file ---> transport stream file (.ts)
    """
    
    def __init__(self, sectionObj, targetTs, tsPid):
        """"""
        self._sectionObj = sectionObj  # dvbobject
        self._targetTsFile = targetTs  # string
        self._tsPid = tsPid    # transport stream PID
        
    def pack(self):
        """
        Pack transport stream file
        """
        # Build section
        self._packSection()    # virtual, child class must implement this method
        # Wrap sections and generate a transport stream
        self._sec2ts() # virtual, child class must implement this method
        

class OCPackSISection(OCPackSectionObj):
    
    """
    DVB section string ---> transport stream file (.ts)
    """
    
    __sectionPattern = "sample.sec"   # temporary binary file containing an entire section
    
    def __init__(self, sectionObj, targetTs, tsPid = 0x200):
        """"""
        super(OCPackSISection, self).__init__(sectionObj, targetTs, tsPid)
        self.__fullpath = "%s/%s" % (DvtFolders.DIR_WORKFOLDER, self.__sectionPattern)
        
    def _packSection(self):
        """
        Pack section file
        """
        # Update the SI/PSI section
        out = open(self.__fullpath, "wb")
        out.write(self._sectionObj.pack())
        out.close
        # python flush bug
        out = open(self.__fullpath, "wb")
        out.close
        
    def _sec2ts(self):
        """"""
        target = "%s/%s" % (DvtFolders.DIR_WORKFOLDER, self._targetTsFile)
        command = "/usr/local/bin/sec2ts %d < %s > %s" \
                    % (self._tsPid, self.__fullpath, target)
        os.system(command)
        
        

class OCPackSsuSection(OCPackSectionObj):
    
    """
    DVB section object ---> transport stream file (.ts)
    """
    
    ocdir = 'datacarousel'
    __cmdssuupdate = 'ssu-update.sh'
    
    def __init__(self, sectionObj, targetTs, tsPid = 0x300):
        super(OCPackSsuSection, self).__init__(sectionObj, targetTs, tsPid)
        self.__folder = dvtCreateDir("%s/%s" % (DvtFolders.DIR_WORKFOLDER, self.ocdir))
        self.__ssufolder = dvtCreateDir("%s/%s/%s" % (DvtFolders.DIR_WORKFOLDER, self.ocdir,"ssu"))
        
    def _packSection(self):
        """
        Pack section file
        """
        # Generate .sec
        self._sectionObj.generate(self.__folder)
        
    def _sec2ts(self):
        ''''''
        dvtCopyFile(
                    "%s/%s" % (DvtFolders.DIR_TOOLS, self.__cmdssuupdate), 
                    "./%s" % (self.__cmdssuupdate)
                    )
        # Update
        command = 'chmod -R 777 ./*;   ./%s %s %d 0 20 %s' % \
            (self.__cmdssuupdate, self.__folder, self._tsPid, self.__ssufolder)
        os.system(command)
        dvtDelFileFolder("./%s" % (self.__cmdssuupdate))


class VirtualConstructor(object):
    
    def register(self, observer):
        raise NotImplementedError("%s : Subclass me!" % (self.__class__))
    
    def unregister(self, observer):
        raise NotImplementedError("%s : Subclass me!" % (self.__class__))
    
    def notify(self, observer):
        raise NotImplementedError("%s : Subclass me!" % (self.__class__))


class OCConstructDownloadMessage(VirtualConstructor):
    '''Ethan Notes: REFACTOR!!!!!'''
    
    def __init__(self, downloadItem):
        ''''''
        self.__downloadItem = downloadItem  # a download item containing the configuration information for a specific download
        self.__useBat = False   # add the linkage descriptor into BAT rather than NIT
        self.__networkType = None    # delivery network type
        self.__emmTrigger = False   # 
        self.__actualTs = True  #
        self.__linkagedesriptorMulple = False #		
        self.__setOptions()
        
        self.__observers = []
        
    def register(self, observer):
        self.__observers.append(observer)
    
    def unregister(self, observer):
        self.__observers.remove(observer)
    
    def notify(self, event):
        for ob in self.__observers:
            ob.notify(event)
        
    def __setOptions(self):
        ''''''
        try:
            options = self.__downloadItem['options']
            dvtdbg("options: %s" % options)
            if options is not None:
                if options['linkage_descriptor_location'] == "BAT":
                    self.__useBat = True
                if options['emm_trigger'] == "on":
                    self.__emmTrigger = True
                if options['ssu_location'] == "other":
                    self.__actualTs = False
                if options['linkage_descriptor_multiple'] == "on":
                    self.__linkagedesriptorMulple = True                
        except:
            raise dvtError("error set build options!")
        
    def construct(self):
        ''''''

        # construct component ts files for mux
        # warning: NEVER modify the executing sequence of these methods
        dvtdbg("Roger that, under construction!!!")

        self.__buildBat()
        self.__buildNit()
        self.__buildPat()
        self.__buildPmt()
        self.__buildSdt()		
        if self.__emmTrigger:
            self.__buildIrdEmm()
            self.__buildCat()
        self.__buildSsu()
    
    # SI
    def __buildNit(self):
        ''''''
        # root = self.__downloadItem['signaling']
        linkageDesc = self.__downloadItem['linkage_descriptor']
        transport = self.__downloadItem['transport']
        service = self.__downloadItem['service']
        dvtdbg("actual transport stream: %s" % transport['actual']['delivery_system_descriptor'])
        dvtdbg("other transport stream: %s" % transport['other']['delivery_system_descriptor'])
        if self.__actualTs:
            actualServiceDes = service_descriptor_loop_item(
                                service_ID = service['service_id'], 
                                service_type = 0x0C, # data broadcast service
                                )
            otherServiceDes = service_descriptor_loop_item(
                                service_ID = service['service_id'], 
                                service_type = 0x01, # data broadcast service
                                )
        else:
            otherServiceDes = service_descriptor_loop_item(
                                service_ID = service['service_id'], 
                                service_type = 0x0C, # data broadcast service
                                )
            actualServiceDes = service_descriptor_loop_item(
                                service_ID = service['service_id'], 
                                service_type = 0x01, # data broadcast service
                                )
        
        
        nit = network_information_section(
            network_id = 1,
            network_descriptor_loop = [
                network_descriptor(network_name = "Irdeto",), 
                # Insert a linkage descriptor here!!
                
                ],
            transport_stream_loop = [
                 # actual
                transport_stream_loop_item(
                    transport_stream_id = transport['actual']['transport_stream_id'],
                    original_network_id = transport['actual']['original_network_id'],
                    transport_descriptor_loop = [
                        service_list_descriptor(
                            dvb_service_descriptor_loop = [
                                actualServiceDes,
                                ],
                            ),
                        
                        # Insert a delivery system descriptor here!!!  
                        self.__buildDeliverySystemDescriptor(transport['actual']['delivery_system_descriptor'])
                        ],        
                    ),
                # other
                transport_stream_loop_item(
                    transport_stream_id = transport['other']['transport_stream_id'],
                    original_network_id = transport['other']['original_network_id'],
                    # actual
                    transport_descriptor_loop = [
                        service_list_descriptor(
                            dvb_service_descriptor_loop = [
                                otherServiceDes,
                                ],
                            ),
                        
                        # Insert a delivery system descriptor here!!!    
                        self.__buildDeliverySystemDescriptor(transport['other']['delivery_system_descriptor'])
                        ],        
                    ),
              ],
            version_number = 1, # you need to change the table number every time you edit, so the decoder will compare its version with the new one and update the table
            section_number = 0,
            last_section_number = 0,
            )
        
        # add a service list descriptor
        # add a delivery system descriptor
        # (optional) add a linkage descriptor
        if not self.__useBat:
            if self.__linkagedesriptorMulple:
                nit.network_descriptor_loop.append(self.__buildMultiLinkageDescriptor())
            else:	
                nit.network_descriptor_loop.append(self.__buildLinkageDescriptor())
        # create ts file
        ts = OCPackSISection(nit, "firstnit.ts", 16)
        ts.pack()
        
        # notify muxer to prepare mux operation
        self.notify(('NIT', "firstnit.ts"))
    
    def __buildBat(self):
        ''''''
        # Create a BAT table using a dummy NIT table
        bat = network_information_section(
                table_id = 0x4A, # Bouquet Association section
                network_id = 0xFF00, # Bouquet ID for Loader V5
                network_descriptor_loop = [
                    network_descriptor(    # bouquet_name_descriptor
                        descriptor_tag = 0x47, # bouquet_name_descriptor
                        network_name = "Irdeto",    # bouquet name
                        ),   

                    ],
                transport_stream_loop = [],
                
                version_number = 1, # you need to change the table number every time you edit, so the decoder will compare its version with the new one and update the table
                section_number = 0,
                last_section_number = 0,
                )
        
        # Insert a linkage descriptor here!!
        if self.__useBat:
            if self.__linkagedesriptorMulple:
                bat.network_descriptor_loop.append(self.__buildMultiLinkageDescriptor())
            else:	
                bat.network_descriptor_loop.append(self.__buildLinkageDescriptor())
        
        # create ts file
        ts = OCPackSISection(bat, "firstbat.ts", 17)
        ts.pack()
        
        # notify muxer to prepare mux operation
        self.notify(('BAT', "firstbat.ts"))
        
    def __buildLinkageDescriptor(self):
        ''''''
        linkageDesc = self.__downloadItem['linkage_descriptor']
        transport = self.__downloadItem['transport']
        service = self.__downloadItem['service']
        if self.__actualTs:
            tsInfo = transport['actual']
        else:
            tsInfo = transport['other']
        return linkage_descriptor(
                        transport_stream_id = tsInfo['transport_stream_id'], 
                        original_network_id = tsInfo['original_network_id'], 
                        service_id = service['service_id'], 
                        linkage_type = linkageDesc['linkage_type'], 
                        OUI_loop = [
                            OUI_data (
                                OUI = linkageDesc['OUI'],
                                # manufacturer_id                            16 bits
                                # hardware_version                           16 bits
                                # Reserved                                   16 bits
                                # Software model (variant)                   16 bits
                                # Sub software model (sub variant)           16 bits
                                # Trigger control byte                        8 bits
                                # Download mode                               8 bits
                            
                                # selector_bytes = "\x00\x40\x00\x0b\x00\x00\x12\x34\x56\x78\x00\x32\x80\x00",
                                selector_bytes = linkageDesc['selector_byte']
                                )
                            ],
                        private_data_bytes = "",
                        )
    
    def __buildMultiLinkageDescriptor(self):
        ''''''
        linkageDesc = self.__downloadItem['linkage_descriptor']
        MultiLinkageDesc = self.__downloadItem['multilinkage_descriptor']
        transport = self.__downloadItem['transport']
        service = self.__downloadItem['service']
        if self.__actualTs:
            tsInfo = transport['actual']
        else:
            tsInfo = transport['other']
        return linkage_descriptor(
                        transport_stream_id = tsInfo['transport_stream_id'], 
                        original_network_id = tsInfo['original_network_id'], 
                        service_id = service['service_id'], 
                        linkage_type = linkageDesc['linkage_type'], 
                        OUI_loop = [
                            OUI_data (
                                OUI = linkageDesc['OUI'],
                                # manufacturer_id                            16 bits
                                # hardware_version                           16 bits
                                # Reserved                                   16 bits
                                # Software model (variant)                   16 bits
                                # Sub software model (sub variant)           16 bits
                                # Trigger control byte                        8 bits
                                # Download mode                               8 bits
                            
                                # selector_bytes = "\x00\x40\x00\x0b\x00\x00\x12\x34\x56\x78\x00\x32\x80\x00",
                                selector_bytes = linkageDesc['selector_byte']
                                ),
                            OUI_data (
                                OUI = MultiLinkageDesc['OUI'],
                                # manufacturer_id                            16 bits
                                # hardware_version                           16 bits
                                # Reserved                                   16 bits
                                # Software model (variant)                   16 bits
                                # Sub software model (sub variant)           16 bits
                                # Trigger control byte                        8 bits
                                # Download mode                               8 bits
                            
                                # selector_bytes = "\x00\x40\x00\x0b\x00\x00\x12\x34\x56\x78\x00\x32\x80\x00",
                                selector_bytes = MultiLinkageDesc['selector_byte']
                                )								

                            ],
                        private_data_bytes = "",
                        )
						
    def __buildDeliverySystemDescriptor(self, root = {}):
        ''''''
        networkType = root['network_type']
        data = root[networkType]
        if networkType == "cable":
            dvbobject = transport_stream_cable_descriptor(
                            frequency = data['frequency'], 
                            FEC_outer = data['FEC_outer'], 
                            modulation = data['modulation'], 
                            symbol_rate = data['symbol_rate'], 
                            FEC_inner = data['FEC_inner']
                            )
        elif networkType == "satellite":
            if data['modulation_system'] == 0x01:
                dvbobject = transport_stream_sat_descriptor(
                            frequency = data['frequency'], 
                            orbital_position = data['orbital_position'], 
                            west_east_flag = data['west_east_flag'], 
                            polarization = data['polarization'], 
                            modulation = (data['roll_off'] << 3) | 
                                        (data['modulation_system'] << 2) | 
                                        (data['modulation_type']),
                            symbol_rate = data['symbol_rate'], 
                            FEC_inner = data['FEC_inner']
                            )
            else:		
                dvbobject = transport_stream_sat_descriptor(
                            frequency = data['frequency'], 
                            orbital_position = data['orbital_position'], 
                            west_east_flag = data['west_east_flag'], 
                            polarization = data['polarization'], 
                            modulation = ((data['modulation_system'] << 2) | 
                                        data['modulation_type']),
                            symbol_rate = data['symbol_rate'], 
                            FEC_inner = data['FEC_inner']
                            )			
        elif networkType == "satellite2":
            networkType = "satellite"
            data_s = root[networkType]
            dvbobject = transport_stream_s2_descriptor(
                            transport_stream_sat = [transport_stream_sat_descriptor(
                            frequency = data_s['frequency'], 
                            orbital_position = data_s['orbital_position'], 
                            west_east_flag = data_s['west_east_flag'], 
                            polarization = data_s['polarization'], 
                            modulation = (data_s['roll_off'] << 3) | 
                                        (data_s['modulation_system'] << 2) | 
                                        (data_s['modulation_type']),
                            symbol_rate = data_s['symbol_rate'], 
                            FEC_inner = data_s['FEC_inner']
                            ),],
                            transport_stream_sat2 = [transport_stream_satellite2_descriptor(
                            scrambling_sequence_selector = data['scrambling_sequence_selector'], 
                            multiple_input_stream_flag = data['multiple_input_stream_flag'], 
                            smbr = (data['scrambling_sequence_selector'] << 7 | 
                              data['multiple_input_stream_flag'] << 6 |
                              data['backwards_compatibility_indicator'] << 5 |
                              0x1F), 
                            scrambling_sequence_index_HB = data['scrambling_sequence_index'] >> 16 | 0xFC ,
                            scrambling_sequence_index_LH = (data['scrambling_sequence_index'] & 0xFFFF),
                            input_stream_identifier = data['input_stream_identifier'], 
                            ),],
                          )
        elif networkType == "terrestrial":
            dvbobject = transport_stream_terrestrial_descriptor(
                            center_frequency = data['center_frequency'], 
                            bandwidth = data['bandwidth'], 
                            constellation = data['constellation'], 
                            hierarchy_information = data['hierarchy_information'], 
                            code_rate_HP_stream = data['code_rate_HP_stream'], 
                            code_rate_LP_stream = data['code_rate_LP_stream'], 
                            guard_interval = data['guard_interval'], 
                            transmission_mode = data['transmission_mode'], 
                            other_frequency_flag = data['other_frequency_flag']
                            )
        elif networkType == "terrestrial2":
            T2_cell_loop_num =  data['T2CellLoop_num']
            T2_cell_loop = []
            for i in range(T2_cell_loop_num):
              centre_frequency_loop = []
              sub_cell_extension_loop = []
              if data['tfs_flag'] == 1 :
                for j in range(data['cellLoopItem'][i]['T2CellCentreFrequencyLoop']['center_frequency_num']):
                  centerfreq = data['cellLoopItem'][i]['T2CellCentreFrequencyLoop']['center_frequency'][j]
                  centre_frequency_loop.append(
                                   T2_centlfreq_descriptor(center_frequency = centerfreq)
                             )
              else:
                centerfreq = data['cellLoopItem'][i]['T2CellCentreFrequencyLoop']['center_frequency'][0]
                centre_frequency_loop.append(
                                   T2_centlfreq_descriptor(center_frequency = centerfreq)
                                   )                                 
              for j in range(data['cellLoopItem'][i]['T2SubCellLoop']['cell_id_extension_num']):
                cell_id_extension = data['cellLoopItem'][i]['T2SubCellLoop']['cell_id_extension'][j]
                transposer_frequency = data['cellLoopItem'][i]['T2SubCellLoop']['transposer_frequency'][j]
                sub_cell_extension_loop.append(
                                   T2_sub_cell_extension_descriptor(
                                     cell_id_extension = cell_id_extension,
                                     transposer_frequency = transposer_frequency
                                     )
                             )                                                             
              T2_cell_loop.append(T2_cell_descriptor(
                            Cell_id = data['cellLoopItem'][i]['cell_id'],
                            T2_central_frequency_loop = [T2_central_frequency_descriptor(
                                tfs_flag = data['tfs_flag'],
                                center_frequency_num = data['cellLoopItem'][i]['T2CellCentreFrequencyLoop']['center_frequency_num'],
                                center_frequency = centre_frequency_loop
                                ),],
                            T2_sub_sell_loop = [T2_sub_sell_descriptor(
                                cell_id_extension_num = data['cellLoopItem'][i]['T2SubCellLoop']['cell_id_extension_num'],
                                sub_cell_extension = sub_cell_extension_loop
                                #cell_id_extension = data['cellLoopItem'][i]['T2SubCellLoop']['cell_id_extension'],
                                #transposer_frequency = data['cellLoopItem'][i]['T2SubCellLoop']['transposer_frequency']
                                ),
                                ],
                            ))
            dvbobject = transport_stream_terrestrial2_descriptor(
                            plp_id = data['plp_id'], 
                            T2_system_id = data['T2_system_id'],
                            SISO_MISO_bandwidth = (data['SISO_MISO'] << 6 | data['bandwidth'] << 2 | 0x03),  
                            GTOT = (data['guard_interval'] << 5 | data['transmission_mode'] << 2 | data['other_frequency_flag'] << 1 | data['tfs_flag']), 
                            T2_cell_loop = T2_cell_loop                              
                            )                                                        
        else:
            raise dvtError("Invalid delivery network type found!")
        
        return dvbobject
    
    # PSI
    def __buildPat(self):
        ''''''
        transport = self.__downloadItem['transport']['actual']
        service = self.__downloadItem['service']
        pat = program_association_section(
                    transport_stream_id = transport['transport_stream_id'], 
                    program_loop = [
                        # add a PMT service containing SSU/TV
                        program_loop_item(
                            program_number = service['service_id'], 
                            PID = service['ssu_pmt_pid'], 
                        ), 
                        # add a NIT service
                        program_loop_item(
                            program_number = 0, # special program for the NIT
                            PID = 16, 
                        ),
                    ],
                    version_number = 1, # you need to change the table number every time you edit, so the decoder will compare its version with the new one and update the table
                    section_number = 0,
                    last_section_number = 0,
                )
        
        # create ts file
        ts = OCPackSISection(pat, "firstpat.ts", 0)
        ts.pack()
        
        # notify muxer to prepare mux operation
        self.notify(('PAT', "firstpat.ts"))
    
    def __buildSdt(self):
        ''''''
        transport = self.__downloadItem['transport']['actual']
        service = self.__downloadItem['service']
        service_name_tmp = '0x%x' %transport['transport_stream_id']
        sdt = service_description_section(
                    transport_stream_id = transport['transport_stream_id'], 
					original_network_id = transport['original_network_id'],
					service_loop = [
						service_loop_item(
						service_ID = service['service_id'],
						EIT_schedule_flag = 0, # 0 no current even information is broadcasted, 1 broadcasted
						EIT_present_following_flag = 0, # 0 no next event information is broadcasted, 1 is broadcasted
						running_status = 4, # 4 service is running, 1 not running, 2 starts in a few seconds, 3 pausing
						free_CA_mode = 0, # 0 means service is not scrambled, 1 means at least a stream is scrambled
						service_descriptor_loop = [
							service_descriptor(
							service_type = 0x01, # digital television service
							service_provider_name = "Irdeto",
							service_name = "DVT Tranport_stream_id " + service_name_tmp ,
							),    
					],
					),	
					],
					version_number = 1, # you need to change the table number every time you edit, so the decoder will compare its version with the new one and update the table
					section_number = 0,
					last_section_number = 0,
					)
        
        # create ts file
        ts = OCPackSISection(sdt, "firstsdt.ts", 17)  # SDT PID 0x11
        ts.pack()
        
        # notify muxer to prepare mux operation
        self.notify(('SDT', "firstsdt.ts"))	
	
    def __buildPmt(self):
        ''''''
        # add program number
        # add a stream item in loop
        transport = self.__downloadItem['transport']
        service = self.__downloadItem['service']
        pmtInfo = service['pmt']
        pmt = program_map_section(
            program_number = service['service_id'],
            PCR_PID = 0x810,    # firstvideo.ts
            program_info_descriptor_loop = [],
            
            stream_loop = [
                # Video ES
                stream_loop_item(
                    stream_type = 2, # data stream type
                    elementary_PID = 0x810, # firstvideo.ts
                    element_info_descriptor_loop = []
                ),
                # Audio ES
                stream_loop_item(
                    stream_type = 4, # data stream type
                    elementary_PID = 0x814, # firstaudio.ts
                    element_info_descriptor_loop = []
                ),
                           
                # SSU ES
                # to be inserted here
        
            ],
            version_number = 1, # you need to change the table number every time you edit, so the decoder will compare its version with the new one and update the table
            section_number = 0,
            last_section_number = 0,
            )  
        
        # insert a data broadcast id descriptor for a SSU service
        #if self.__actualTs:
        ssuStream = stream_loop_item(
			stream_type = 11, # data stream type
			elementary_PID = pmtInfo['ssu_es_pid'],
			element_info_descriptor_loop = [
                        data_broadcast_id_descriptor(
                            data_broadcast_ID = 0x000A, # DVB-SSU
                            OUI_info_loop = [
                                OUI_info_loop_item (
                                    OUI = pmtInfo['data_broadcast_id_descriptor']['OUI'],
                                    update_type = pmtInfo['data_broadcast_id_descriptor']['update_type'], # 0x01, 
                                    update_versioning_flag = 0, # no version change
                                    update_version = 1, # increment this at update change
                                    selector_bytes = "", # pmtInfo['data_broadcast_id_descriptor']['selector_byte'] # inner['data_broadcast_id_descriptor']['selector_byte'],
                                ),
                            ],
                            private_data_bytes = "",
                        ),
                    ]
                )
            
        pmt.stream_loop.append(ssuStream)
            
        # create ts file
        ts = OCPackSISection(pmt, "firstpmt.ts", service['ssu_pmt_pid'])
        ts.pack()
        
        # notify muxer to prepare mux operation
        self.notify(('PMT', "firstpmt.ts"))
    
    def __buildCat(self):
        ''''''
        # add ca_descritors
        root = self.__downloadItem['emm']
        inner = root['cat']
        cat = conditional_access_section(
                ca_descriptor_loop = [
                    ca_descriptor(
                        CA_system_ID = inner['ca_descriptor']['ca_system_id'],
                        CA_PID = inner['ca_descriptor']['ca_pid'],
                        ), 
                    ],                          
                version_number = 1, # you need to change the table number every time you edit, so the decoder will compare its version with the new one and update the table
                section_number = 0,
                last_section_number = 0,
                )
        
        # create ts file
        ts = OCPackSISection(cat, "firstcat.ts", 1)
        ts.pack()
        
        # notify muxer to prepare mux operation
        self.notify(('CAT', "firstcat.ts"))
    
    # EMM
    def __buildIrdEmm(self):
        ''''''
        root = self.__downloadItem['emm']['ird_emm']
        type = root['message_type']
        
        # build EMM structure
        emmStruct = IrdetoGlobalEmmStruct(root['filter_number'], 'IRD', 0x0001)
        if type == "force download":
            emmStruct.message_data = IrdetoDownloadControlMessage().pack()
        elif type == "migration":
            emmStruct.message_data = IrdetoMigrationMessage(
                                        root[type]['new_variant'], 
                                        root[type]['new_subvariant']
                                        ).pack()
        else:
            raise dvtError("Unknown IRD message type found!")
        
        # build EMM section
        emm = IrdetoEmmSection(
                emm_structure = emmStruct.pack(), 
                )
        
        # create ts file
        ts = OCPackSISection(
                emm, 
                "firstemm.ts", 
                self.__downloadItem['emm']['cat']['ca_descriptor']['ca_pid']
                )
        ts.pack()
        
        # notify muxer to prepare mux operation
        self.notify(('EMM', "firstemm.ts"))
    
    # SSU
    def __buildSsu(self):
        ''''''
        # Parse SDL file and get information for generating DSMCC sections
        sdlFileName = self.__downloadItem['cd5']['name']
        sdl = IrdetoSdlParser(sdlFileName)
        sdl.parse()
        parsed = sdl.getResult()
        
        # build DSMCC object
        comp_desc1 = compatibility_descriptor(
            compatibility_descriptor_loop = [
                compatibility_descriptor_loop_item (
                    descriptor_type = 0x01, # hardware descriptor
                    specifier_type = 0x01, # IEEE OUI
                    specifier_data = self.__downloadItem['manufacturer_info']['OUI'],
                    model = parsed['manufacturer_id'],  #Manufacturer ID
                    version = parsed['hardware_version'], #Hardware version
                    compatibility_descriptor_subloop = [],
                ),
                compatibility_descriptor_loop_item (
                    descriptor_type = 0x02, # software descriptor
                    specifier_type = 0x01, # IEEE OUI
                    specifier_data = self.__downloadItem['manufacturer_info']['OUI'],
                    model = parsed['variant'],    #Variant
                    version = parsed['download_sequence_number'], #Download sequence 
                    compatibility_descriptor_subloop = [],
                ),
                
                compatibility_descriptor_loop_item (
                    descriptor_type = 0x40, # private descriptor
                    specifier_type = 0x01, # IEEE OUI
                    specifier_data = self.__downloadItem['manufacturer_info']['OUI'],
                    model = parsed['sub_variant'],  #Sub variant 
                    version = 0,
                    compatibility_descriptor_subloop = [],
                ),
            ]
        )
        
        g1 = Group(
            PATH="DII-1.sec",
            transactionId = 0x80000002,
            downloadId    = 0x00000001,
            blockSize     = 4066,
            version      = 1,
            )
        g1.set(
            compatibilityDescriptor = comp_desc1.pack(),
            modules = [
                 Module(
                    INPUT=sdlFileName,
                    moduleId = 0x0001,
                    moduleVersion = 0x00,
                    descriptors = [name_descriptor(name="a bin")],
            ),
        
            ],
            )
        
        dsi = SuperGroup(
            PATH = "/",
            transactionId = 0x80000000,
            version      = 1,
            )
        dsi.set(
            compatibilityDescriptor = "", # as specified in etsi 102 006
        )
        dsi.addGroup(g1)
    
        # create ts file
        ts = OCPackSsuSection(
                dsi, 
                "", 
                self.__downloadItem['service']['pmt']['ssu_es_pid']
                )
        ts.pack()
        
        # notify muxer to prepare mux operation
        self.notify(('SSU', "%s.ts" % (OCPackSsuSection.ocdir)))


