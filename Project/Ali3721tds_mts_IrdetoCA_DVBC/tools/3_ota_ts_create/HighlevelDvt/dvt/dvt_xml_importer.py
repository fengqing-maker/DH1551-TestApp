#!/usr/bin/env python

#
# Created on Oct 27, 2011
#
# @author: ethan.li
#



from dvt_base import *
from dvt_dvb import *
from dvt_irdeto import *
from dvt_xml_parser import *


class DvtXmlImporter(object):
    """"""
    def __init__(self, fullpath):
        self.__xmlParser = DvtXmlParser(fullpath)
        self.__downloadList = {}
        self.__xmlfolder = os.path.dirname(fullpath)
        
    def __addDownloadItem(self, idString, item):
        if item is not None:
            self.__downloadList[idString] = item
        
    def getDownloadItemById(self, idString):
        return self.__downloadList[idString]
    
    def getDownloadList(self):
        return self.__downloadList
    
    def analyseXml(self):
        ''''''
        dvtdbg("Analysing XML started...")
        try:    
            """Get the unique download id"""
            result = True
            list = self.__xmlParser.getTagElements(None, 'download')
            for elem in list:
                parsed = {}
                # self.__downloadList[elem.tagName] = elem
                dvtdbg("\nNew DVT download: %s, %s, %s" % 
                       (elem, elem.tagName, elem.getAttribute('id')))
                # Start parsing!!!
                result = self.__analyseSingleDownload(parsed, elem)
                if result:
                    # self.__downloadList[elem.tagName] = parsed
                    self.__addDownloadItem(elem.getAttribute('id'), parsed)
                
                # Something wrong happens!!!
                if not result:
                    break 
            return result
        except IndexError:
            raise dvtError('Parsing XML failed!')
        dvtdbg("Analysing XML finished...")
    
    def __analyseSingleDownload(self, parsed, thisElem):
        ''''''
        result = True

        # manufacturer_info
        if result:
            tag = 'manufacturer_info'
            item = ManufacturerInfo()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseManufacturerInfo(item, self.__xmlParser.getTagElements(thisElem, tag)[0])
            if result:
                parsed[tag] = item.getObject()
        
        # cd5
        if result:
            tag = 'cd5'
            item = Cd5()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseCd5(item, self.__xmlParser.getTagElements(thisElem, tag)[0])
            if result:
                parsed[tag] = item.getObject()
        
        # global options
        if result:
            tag = 'options'
            item = GlobalOptions()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseGlobalOptions(item, self.__xmlParser.getTagElements(thisElem, tag)[0])
            if result:
                parsed[tag] = item.getObject()
        
        # emm
        if result:
            tag = 'emm'
            item = Emm()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseEmm(item, self.__xmlParser.getTagElements(thisElem, tag)[0])
            if result:
                parsed[tag] = item.getObject()

        # linkage descriptor
        if result:
            tag = 'linkage_descriptor'
            item = LinkageDescriptor()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseLinkageDescriptor(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed[tag] = item.getObject()
                
        # multilinkage descriptor
        if result:
            tag = 'multilinkage_descriptor'
            item = MultiLinkageDescriptor()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseLinkageDescriptor(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed[tag] = item.getObject()				
                
        # transport
        if result:
            tag = 'transport'
            item = Transport()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseTransport(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed[tag] = item.getObject()
                
        # service
        if result:
            tag = 'service'
            item = Service()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseService(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed[tag] = item.getObject()
        
        return result
        
    def __parseManufacturerInfo(self, parsed, thisElem):
        '''Parse manufacturer information'''
        result = True
            
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'name')
            if text is None:
                result = False
            else:
                parsed.setMember('name', text.strip())
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'OUI')
            if text is None:
                result = False
            else:
                parsed.setMember('OUI', dvtStrToInt(text.strip()))
            
        return result
        
    def __parseGlobalOptions(self, parsed, thisElem):
        '''Parse global options'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'emm_trigger')
            if text is None:
                result = False
            else:
                parsed.setMember('emm_trigger', text.strip())

        if result:
            text = self.__xmlParser.getTagText(thisElem, 'linkage_descriptor_location')
            if text is None:
                result = False
            else:
                parsed.setMember('linkage_descriptor_location', text.strip())
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'ssu_location')
            if text is None:
                result = False
            else:
                parsed.setMember('ssu_location', text.strip())

        if result:
            text = self.__xmlParser.getTagText(thisElem, 'linkage_descriptor_multiple')
            if text is None:
                result = False
            else:
                parsed.setMember('linkage_descriptor_multiple', text.strip())				
    
        return result
    
    def __parseCd5(self, parsed, thisElem):
        '''Parse cd5'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'name')
            if text is None:
                result = False
            else:
                parsed.setMember('name', "%s/%s" % (self.__xmlfolder, text.strip()))
                
        return result
    
    def __parseLinkageDescriptor(self, parsed, thisElem):
        '''Parse linkage descriptor'''
        result = True
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'linkage_type')
            if text is None:
                result = False
            else:
                parsed.setMember('linkage_type', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'OUI')
            if text is None:
                result = False
            else:
                parsed.setMember('OUI', dvtStrToInt(text.strip()))
                
        if result:
            tag = 'selector_byte'
            item = SelectorByte()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseSelectorByte(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed.setMember('selector_byte', item.getObject())
        
        return result
    
    def __parseSelectorByte(self, parsed, thisElem):
        '''Parse linkage descriptor'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'manufacturer_id')
            if text is None:
                result = False
            else:
                parsed.setMember('manufacturer_id', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'hardware_version')
            if text is None:
                result = False
            else:
                parsed.setMember('hardware_version', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'reserved')
            if text is None:
                result = False
            else:
                parsed.setMember('reserved', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'variant')
            if text is None:
                result = False
            else:
                parsed.setMember('variant', dvtStrToInt(text.strip()))
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'sub_variant')
            if text is None:
                result = False
            else:
                parsed.setMember('sub_variant', dvtStrToInt(text.strip()))
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'download_sequence_number')
            if text is None:
                result = False
            else:
                parsed.setMember('download_sequence_number', dvtStrToInt(text.strip()))
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'trigger_control_byte')
            if text is None:
                result = False
            else:
                parsed.setMember('trigger_control_byte', dvtStrToInt(text.strip()))
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'download_mode')
            if text is None:
                result = False
            else:
                parsed.setMember('download_mode', dvtStrToInt(text.strip()))
        
        return result
    
    def __parseDeliverySystemDescriptor(self, parsed, thisElem):
        '''Parse delivery system descriptor'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'network_type')
            if text is None:
                result = False
            else:
                parsed.setMember('network_type', text.strip())
        
        if result:
            text = parsed.getMember('network_type')
            if text == "cable":
                tag = 'item'
                item = CableDeliverySystemDescriptor()
                dvtdbg(">>>> Start parsing <%s> %s \"type\" = %s </%s>" % (tag, item, text, tag))
                result = self.__parseCableDeliverySystemDescriptor(
                                    item, 
                                    self.__xmlParser.getTagElements(thisElem, tag, 'type', text)[0]
                                    )
                if result:
                    parsed.setMember(text, item.getObject())

            elif text == "satellite":
                tag = 'item'
                item = SatelliteDeliverySystemDescriptor()
                dvtdbg(">>>> Start parsing <%s> %s \"type\" = %s </%s>" % (tag, item, text, tag))
                result = self.__parseSatelliteDeliverySystemDescriptor(
                                    item, 
                                    self.__xmlParser.getTagElements(thisElem, tag, 'type', text)[0]
                                    )
                if result:
                    parsed.setMember(text, item.getObject())
            elif text == "satellite2":
                tag = 'item'    #s2
                item = Satellite2DeliverySystemDescriptor()
                dvtdbg(">>>><<<<<< Start parsing <%s> %s \"type\" = %s </%s>" % (tag, item, text, tag))
                result = self.__parseSatellite2DeliverySystemDescriptor(
                                    item, 
                                    self.__xmlParser.getTagElements(thisElem, tag, 'type', text)[0]
                                    )
                if result:
                    parsed.setMember(text, item.getObject())
            
                   
                tag = 'item'    #s
                text = "satellite"
                item = SatelliteDeliverySystemDescriptor()
                dvtdbg("here here here hereStart parsing <%s> %s \"type\" = %s </%s>" % (tag, item, text, tag))
                result = self.__parseSatelliteDeliverySystemDescriptor(
                                    item, 
                                    self.__xmlParser.getTagElements(thisElem, tag, 'type', text)[0]
                                    )
                if result:
                    parsed.setMember(text, item.getObject())   
            elif text == "terrestrial":
                tag = 'item'
                item = TerrestialDeliverySystemDescriptor()
                dvtdbg(">>>> Start parsing <%s> %s \"type\" = %s </%s>" % (tag, item, text, tag))
                result = self.__parseTerrestialDeliverySystemDescriptor(
                                    item, 
                                    self.__xmlParser.getTagElements(thisElem, tag, 'type', text)[0]
                                    )
                if result:
                    parsed.setMember(text, item.getObject())
            elif text == "terrestrial2":
                tag = 'item'
                item = Terrestial2DeliverySystemDescriptor()
                dvtdbg(">>>> Start parsing <%s> %s \"type\" = %s </%s>" % (tag, item, text, tag))
                result = self.__parseTerrestial2DeliverySystemDescriptor(
                                    item, 
                                    self.__xmlParser.getTagElements(thisElem, tag, 'type', text)[0]
                                    )
                if result:
                    parsed.setMember(text, item.getObject())   
            
            else:
                result = False
                
        return result
    
    def __parseCableDeliverySystemDescriptor(self, parsed, thisElem):
        '''Parse cable delivery system descriptor'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'frequency')
            if text is None:
                result = False
            else:
                parsed.setMember('frequency', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'FEC_outer')
            if text is None:
                result = False
            else:
                parsed.setMember('FEC_outer', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'modulation')
            if text is None:
                result = False
            else:
                parsed.setMember('modulation', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'symbol_rate')
            if text is None:
                result = False
            else:
                parsed.setMember('symbol_rate', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'FEC_inner')
            if text is None:
                result = False
            else:
                parsed.setMember('FEC_inner', dvtStrToInt(text.strip()))
        
        return result
    
    def __parseSatelliteDeliverySystemDescriptor(self, parsed, thisElem):
        '''Parse satellite delivery system descriptor'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'frequency')
            if text is None:
                result = False
            else:
                parsed.setMember('frequency', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'orbital_position')
            if text is None:
                result = False
            else:
                parsed.setMember('orbital_position', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'west_east_flag')
            if text is None:
                result = False
            else:
                parsed.setMember('west_east_flag', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'polarization')
            if text is None:
                result = False
            else:
                parsed.setMember('polarization', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'roll_off')
            if text is None:
                result = False
            else:
                parsed.setMember('roll_off', dvtStrToInt(text.strip()))
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'modulation_system')
            if text is None:
                result = False
            else:
                parsed.setMember('modulation_system', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'modulation_type')
            if text is None:
                result = False
            else:
                parsed.setMember('modulation_type', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'symbol_rate')
            if text is None:
                result = False
            else:
                parsed.setMember('symbol_rate', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'FEC_inner')
            if text is None:
                result = False
            else:
                parsed.setMember('FEC_inner', dvtStrToInt(text.strip()))
        
        return result
    
    def __parseSatellite2DeliverySystemDescriptor(self, parsed, thisElem):
        '''Parse Satellite2 delivery system descriptor'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'scrambling_sequence_selector')
            if text is None:
                result = False
            else:
                parsed.setMember('scrambling_sequence_selector', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'multiple_input_stream_flag')
            if text is None:
                result = False
            else:
                parsed.setMember('multiple_input_stream_flag', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'backwards_compatibility_indicator')
            if text is None:
                result = False
            else:
                parsed.setMember('backwards_compatibility_indicator', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'scrambling_sequence_index')
            if text is None:
                result = False
            else:
                parsed.setMember('scrambling_sequence_index', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'input_stream_identifier')
            if text is None:
                result = False
            else:
                parsed.setMember('input_stream_identifier', dvtStrToInt(text.strip()))

        return result    

    def __parseTerrestial2DeliverySystemDescriptor(self, parsed, thisElem):
        '''Parse terrestrial 2 delivery system descriptor'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'plp_id')
            if text is None:
                result = False
            else:
                parsed.setMember('plp_id', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'T2_system_id')
            if text is None:
                result = False
            else:
                parsed.setMember('T2_system_id', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'SISO_MISO')
            if text is None:
                result = False
            else:
                parsed.setMember('SISO_MISO', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'bandwidth')
            if text is None:
                result = False
            else:
                parsed.setMember('bandwidth', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'guard_interval')
            if text is None:
                result = False
            else:
                parsed.setMember('guard_interval', dvtStrToInt(text.strip()))
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'transmission_mode')
            if text is None:
                result = False
            else:
                parsed.setMember('transmission_mode', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'other_frequency_flag')
            if text is None:
                result = False
            else:
                parsed.setMember('other_frequency_flag', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'tfs_flag')
            if text is None:
                result = False
            else:
                parsed.setMember('tfs_flag', dvtStrToInt(text.strip()))
 
        if result: 
            #for node in thisElem.childNodes:
            nodes = thisElem.getElementsByTagName('T2CellLoop')
            dvtdbg("node data is %s" % nodes )
            cellLoopItem = []
            dvtdbg("T2CellLoop_num data is %d" % nodes.length )
            for i in range(nodes.length):       
              #for childnode in nodes[i].childNodes:
                #if childnode.nodeType == nodes[i].ELEMENT_NODE:
                   dvtdbg("T2CellLoop _num num %d " %i  )
                   tag = 'T2CellLoop'
                   item = T2CellLoop()
                   result = self.__parseT2CellLoop(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[i]
                                        )
                   if result:
                      cellLoopItem.append(item.getObject()) 
              #T2CellLoopData = 'T2CellLoop' + str(i)                           
              #parsed.setMember(T2CellLoopData, item.getObject()) 
              
            parsed.setMember('cellLoopItem', cellLoopItem)# cellLoopItem = [T2CellLoopData1,T2CellLoopData2.......]
            parsed.setMember('T2CellLoop_num', nodes.length)                               
                                                             
        
        return result
        
    def __parseTerrestialDeliverySystemDescriptor(self, parsed, thisElem):
        '''Parse terrestrial delivery system descriptor'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'center_frequency')
            if text is None:
                result = False
            else:
                parsed.setMember('center_frequency', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'bandwidth')
            if text is None:
                result = False
            else:
                parsed.setMember('bandwidth', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'constellation')
            if text is None:
                result = False
            else:
                parsed.setMember('constellation', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'hierarchy_information')
            if text is None:
                result = False
            else:
                parsed.setMember('hierarchy_information', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'code_rate_HP_stream')
            if text is None:
                result = False
            else:
                parsed.setMember('code_rate_HP_stream', dvtStrToInt(text.strip()))
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'code_rate_LP_stream')
            if text is None:
                result = False
            else:
                parsed.setMember('code_rate_LP_stream', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'guard_interval')
            if text is None:
                result = False
            else:
                parsed.setMember('guard_interval', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'transmission_mode')
            if text is None:
                result = False
            else:
                parsed.setMember('transmission_mode', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'other_frequency_flag')
            if text is None:
                result = False
            else:
                parsed.setMember('other_frequency_flag', dvtStrToInt(text.strip()))
        
        return result
    
    def __parsePmt(self, parsed, thisElem):
        '''Parse PMT'''
        result = True
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'ssu_es_pid')
            if text is None:
                result = False
            else:
                parsed.setMember('ssu_es_pid', dvtStrToInt(text.strip()))
                
        if result:
            tag = 'data_broadcast_id_descriptor'
            item = DataBroadcastIdDescriptor()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseDataBroadcastIdDescriptor(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed.setMember('data_broadcast_id_descriptor', item.getObject())
        
        return result
    
    def __parseT2CellLoop(self, parsed, thisElem):
        '''Parse T2CellLoop'''
        result = True
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'cell_id')
            dvtdbg("cell_id data is %s" % text )
            if text is None:
                result = False
            else:
                parsed.setMember('cell_id', dvtStrToInt(text.strip()))
                
        if result:
            tag = 'T2CellCentreFrequencyLoop' 
            item = T2CellCentreFrequencyLoop()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseT2CellCentreFrequencyLoop(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed.setMember('T2CellCentreFrequencyLoop', item.getObject())            
              
        if result:
            tag = 'T2SubCellLoop'
            item = T2SubCellLoop()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseT2SubCellLoop(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed.setMember('T2SubCellLoop', item.getObject())

        return result
        
    def __parseT2CellCentreFrequencyLoop(self, parsed, thisElem):
        '''Parse T2CellCentreFrequencyLoop'''
        result = True
                
        #for node in thisElem.childNodes:
        nodes = thisElem.getElementsByTagName('center_frequency')
        dvtdbg("node data is %s" % nodes )
        rc = [] #""
        for i in range(nodes.length):       
            for childnode in nodes[i].childNodes:
                if childnode.nodeType == nodes[i].TEXT_NODE:
                   #rc += (childnode.data.strip())
                   rc.append(dvtStrToInt(childnode.data.strip()))
                   dvtdbg("[text] (root -> %s , value -> %s)" 
                   % (childnode, rc)) 
                   
        dvtdbg("[text] (rc[0] -> %s , value -> %s)" 
                   % (childnode, rc[1]))
        parsed.setMember('center_frequency_num', nodes.length)                               
        parsed.setMember('center_frequency', rc)
        
        #if result:
        #    text = self.__xmlParser.getTagText(thisElem, 'center_frequency')
        #    if text is None:
        #       result = False
        #  else:
        #       parsed.setMember('center_frequency', dvtStrToInt(text.strip()))
 
        return result    
 
    def __parseT2SubCellLoop(self, parsed, thisElem):
        '''Parse T2SubCellLoop'''
        result = True
        
        if result:
        #for node in thisElem.childNodes:
          nodes = thisElem.getElementsByTagName('cell_id_extension')
          dvtdbg("node data is %s" % nodes )
          rc = [] 
          for i in range(nodes.length):       
            for childnode in nodes[i].childNodes:
                if childnode.nodeType == nodes[i].TEXT_NODE:
                   #rc += (childnode.data.strip())
                   rc.append(dvtStrToInt(childnode.data.strip()))
                   dvtdbg("[text] (root -> %s , value -> %s)" 
                   % (childnode, rc)) 
                   
          dvtdbg("[text222222] (rc[0] -> %s , value -> %s)" 
                   % (childnode, rc[0]))
          parsed.setMember('cell_id_extension_num', nodes.length)                               
          parsed.setMember('cell_id_extension', rc)
                
        #if result:
        #    text = self.__xmlParser.getTagText(thisElem, 'cell_id_extension')
        #    if text is None:
        #        result = False
        #    else:
        #        parsed.setMember('cell_id_extension', dvtStrToInt(text.strip()))

        if result:
          nodes = thisElem.getElementsByTagName('transposer_frequency')
          dvtdbg("node data is %s" % nodes )
          rc = [] 
          for i in range(nodes.length):       
            for childnode in nodes[i].childNodes:
                if childnode.nodeType == nodes[i].TEXT_NODE:
                   #rc += (childnode.data.strip())
                   rc.append(dvtStrToInt(childnode.data.strip()))
                   dvtdbg("[text] (root -> %s , value -> %s)" 
                   % (childnode, rc)) 
                   
          dvtdbg("[text333333] (rc[0] -> %s , value -> %s)" 
                   % (childnode, rc[1]))
          parsed.setMember('transposer_frequency_num', nodes.length)                               
          parsed.setMember('transposer_frequency', rc)        
        
        #    text = self.__xmlParser.getTagText(thisElem, 'transposer_frequency')
        #    if text is None:
        #        result = False
        #    else:
        #        parsed.setMember('transposer_frequency', dvtStrToInt(text.strip()))
 
        return result    
        
        
    def __parseDataBroadcastIdDescriptor(self, parsed, thisElem):
        '''Parse data broadcast id descriptor'''
        result = True
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'OUI')
            if text is None:
                result = False
            else:
                parsed.setMember('OUI', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'update_type')
            if text is None:
                result = False
            else:
                parsed.setMember('update_type', dvtStrToInt(text.strip()))
        if result:
            tag = 'selector_byte'
            item = SelectorByte()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseSelectorByte(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed.setMember('selector_byte', item.getObject())
        
        return result
    
    def __parseEmm(self, parsed, thisElem):
        '''Parse delivery system descriptor'''
        result = True
        
        # ird_emm
        if result:
            tag = 'ird_emm'
            item = IrdEmm()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseIrdEmm(item, self.__xmlParser.getTagElements(thisElem, tag)[0])
            if result:
                parsed.setMember(tag, item.getObject())
        
        # cat        
        if result:
            tag = 'cat'
            item = Cat()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseCat(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed.setMember(tag, item.getObject())
                
        return result
    
    def __parseIrdEmm(self, parsed, thisElem):
        '''Parse IRD EMM'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'filter_number')
            if text is None:
                result = False
            else:
                parsed.setMember('filter_number', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'message_type')
            if text is None:
                result = False
            else:
                parsed.setMember('message_type', text.strip())        
        
        if result:
            text = parsed.getMember('message_type')
            if text == "force download": # force download
                tag = 'item'
                item = ForceDownloadEmm()
                dvtdbg(">>>> Start parsing <%s> %s \"type\" = %s </%s>" % (tag, item, text, tag))
                result = self.__parseForceDownloadEmm(
                                    item, 
                                    self.__xmlParser.getTagElements(thisElem, tag, 'type', text)[0]
                                    )
                if result:
                    parsed.setMember(text, item.getObject())
            elif text == "migration":   # migration
                tag = 'item'
                item = MigrationEmm()
                dvtdbg(">>>> Start parsing <%s> %s \"type\" = %s </%s>" % (tag, item, text, tag))
                result = self.__parseMigrationEmm(
                                    item, 
                                    self.__xmlParser.getTagElements(thisElem, tag, 'type', text)[0]
                                    )
                if result:
                    parsed.setMember(text, item.getObject())
            else:
                result = False
                
        return result
        
    def __parseForceDownloadEmm(self, parsed, thisElem):
        '''Parse force download EMM'''
        result = True
        return result

    def __parseMigrationEmm(self, parsed, thisElem):
        '''Parse migration EMM'''
        result = True
            
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'new_variant')
            if text is None:
                result = False
            else:
                parsed.setMember('new_variant', dvtStrToInt(text.strip()))
                    
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'new_subvariant')
            if text is None:
                result = False
            else:
                parsed.setMember('new_subvariant', dvtStrToInt(text.strip()))
                    
        return result
    
    def __parseCat(self, parsed, thisElem):
        '''Parse CAT'''
        result = True
                
        if result:
            tag = 'ca_descriptor'
            item = CaDescriptor()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseCaDescriptor(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed.setMember('ca_descriptor', item.getObject())
        
        return result
    
    def __parseCaDescriptor(self, parsed, thisElem):
        '''Parse CA descriptor'''
        result = True
            
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'ca_system_id')
            if text is None:
                result = False
            else:
                parsed.setMember('ca_system_id', dvtStrToInt(text.strip()))
                    
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'ca_pid')
            if text is None:
                result = False
            else:
                parsed.setMember('ca_pid', dvtStrToInt(text.strip()))
                    
        return result
    
    def __parseTransport(self, parsed, thisElem):
        '''Parse transport'''
        result = True
        
        # actual
        if result:
            tag = 'transport_stream'
            item = TransportStream()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseTransportStream(
                                item, 
                                self.__xmlParser.getTagElements(thisElem, tag, 'attr', 'actual')[0]
                                )
            if result:
                parsed.setMember('actual', item.getObject())
        
        # other        
        if result:
            tag = 'transport_stream'
            item = TransportStream()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseTransportStream(
                                item, 
                                self.__xmlParser.getTagElements(thisElem, tag, 'attr', 'other')[0]
                                )
            if result:
                parsed.setMember('other', item.getObject())
                
        return result
    
    def __parseTransportStream(self, parsed, thisElem):
        '''Parse transport stream'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'transport_stream_id')
            if text is None:
                result = False
            else:
                parsed.setMember('transport_stream_id', dvtStrToInt(text.strip()))
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'original_network_id')
            if text is None:
                result = False
            else:
                parsed.setMember('original_network_id', dvtStrToInt(text.strip()))
        
        if result:
            tag = 'delivery_system_descriptor'
            item = DeliverySystemDescriptor()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parseDeliverySystemDescriptor(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed.setMember(tag, item.getObject())
                
        return result
    
    def __parseService(self, parsed, thisElem):
        '''Parse service'''
        result = True
        
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'service_id')
            if text is None:
                result = False
            else:
                parsed.setMember('service_id', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'service_type')
            if text is None:
                result = False
            else:
                parsed.setMember('service_type', dvtStrToInt(text.strip()))
                
        if result:
            text = self.__xmlParser.getTagText(thisElem, 'ssu_pmt_pid')
            if text is None:
                result = False
            else:
                parsed.setMember('ssu_pmt_pid', dvtStrToInt(text.strip()))
                
        if result:
            tag = 'pmt'
            item = Pmt()
            dvtdbg(">>>> Start parsing <%s> %s </%s>" % (tag, item, tag))
            result = self.__parsePmt(
                                        item, 
                                        self.__xmlParser.getTagElements(thisElem, tag)[0]
                                        )
            if result:
                parsed.setMember(tag, item.getObject())
                
        return result
    
    
        