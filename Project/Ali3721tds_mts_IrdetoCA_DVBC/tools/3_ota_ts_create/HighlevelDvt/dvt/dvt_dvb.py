#!/usr/bin/env python

#
# Created on Oct 27, 2011
#
# @author: ethan.li
#

from dvt_base import *
from dvbobjects.DVB.Descriptors import *
######################################################################       
class SelectorByte(DvtDataBase):
    ''''''
    __vr = {
                "manufacturer_id" : (xrange(0x0001, 0xFFFF)), # [0x0001, 0xFFFE],  
                "hardware_version" : (xrange(0x0001, 0xFFFF)), # [0x0001, 0xFFFE], 
                "reserved" : (0x0000, 0x0000), # fixed to 0x0000, 
                "variant" : (xrange(0x0001, 0x10000)), # [0x0001, 0xFFFE],     for the case step10_02 varitant = 0xffff
                "sub_variant" : (xrange(0x0000, 0x10000)), # [0x0000, 0xFFFE],   for the case step10_04 sub_varitant = 0xffff
                "download_sequence_number" : (xrange(0x0001, (0xFFFF))), # [0x0001, 0xFFFE],  for the case step-07_10, DSN_d + 100
                "trigger_control_byte" : (xrange(0x00, 0x08)), # [0x01, 0x07],  
                "download_mode" : (xrange(0x00, 0x100)), # [0x00, 0x02], 0xFF for the case step06_07 download mode == 0xFF
            }
    
    def __init__(self):
        super(SelectorByte, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
        
    def __pack(self):
        ''''''
        return struct.pack("!HHHHHHBB", 
                    self.getMember('manufacturer_id'),
                    self.getMember('hardware_version'),
                    self.getMember('reserved'),
                    self.getMember('variant'),
                    self.getMember('sub_variant'),
                    self.getMember('download_sequence_number'),
                    self.getMember('trigger_control_byte'), 
                    self.getMember('download_mode')
                    )
        
    def getObject(self):
        '''Rewrite the method to return a packetized byte array'''
        return self.__pack()
######################################################################
class MultiLinkageDescriptor(DvtDataBase):
    ''''''
    __vr = {
                "linkage_type" : (0x09, 0x09), # fixed to 0x09, 
                "OUI" : (xrange(0x0001, 0xFFFFFF)), # [0x000001, 0xFFFFFF], 
                "selector_byte" : None
            }
    
    def __init__(self):
        super(MultiLinkageDescriptor, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
######################################################################
class LinkageDescriptor(DvtDataBase):
    ''''''
    __vr = {
                "linkage_type" : (0x09, 0x09), # fixed to 0x09, 
                "OUI" : (xrange(0x0001, 0xFFFFFF)), # [0x0001, 0xFFFFFF], 
                "selector_byte" : None
            }
    
    def __init__(self):
        super(LinkageDescriptor, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
		
######################################################################

class CableDeliverySystemDescriptor(DvtDataBase):
    ''''''
    __vr = {
                "frequency" : None, 
                "FEC_outer" : (xrange(0x0, 0x3)), # 0x0 ~ 0x2, 
                "modulation" : (xrange(0x00, 0x06)), # 0x00 ~ 0x05, 
                "symbol_rate" : None,  
                "FEC_inner" : (xrange(0x0, 0x10)), # 0x0 ~ 0xF, 
            }
    
    def __init__(self):
        super(CableDeliverySystemDescriptor, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
        
######################################################################
class SatelliteDeliverySystemDescriptor(DvtDataBase):
    ''''''
    __vr = {
                "frequency" : None,
                "orbital_position" : (xrange(0x0000, 0x999A)), # 0.0 ~ 999.9,
                "west_east_flag" : (0, 1), #
                "polarization" : (xrange(0x0, 0x4)), # not include 0x4,
                "roll_off" : (xrange(0x0, 0x3)), # not include 0x3,
                "modulation_system" : (xrange(0x0, 0x2)), # [0x0,0x01]
                "modulation_type" : (xrange(0x0, 0x4)), # not include 0x4,
                "symbol_rate" : None,  
                "FEC_inner" : (xrange(0x0, 0x10)), # 0x0 ~ 0xF, 
            }
    
    def __init__(self):
        super(SatelliteDeliverySystemDescriptor, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
######################################################################
class Satellite2DeliverySystemDescriptor(DvtDataBase):
    ''''''
    __vr = {
                "scrambling_sequence_selector" : (0, 1),
                "multiple_input_stream_flag" : (0, 1),
                "backwards_compatibility_indicator" : (0, 1),
                "scrambling_sequence_index" :   (xrange(0x0, 0x40000)),
                "input_stream_identifier" : (xrange(0x0, 0xFF)),
            }
        
    def __init__(self):
        super(Satellite2DeliverySystemDescriptor, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
        
######################################################################      
class TerrestialDeliverySystemDescriptor(DvtDataBase):
    ''''''
    __vr = {
                "center_frequency" : None, 
                "bandwidth" : (xrange(0x0, 0x4)), # 0x0 ~ 0x3, 
                "constellation" : (xrange(0x0, 0x4)), # 0x0 ~ 0x3, 
                "hierarchy_information" : (xrange(0x0, 0x8)), # 0x0 ~ 0x7, 
                "code_rate_HP_stream" : (xrange(0x0, 0x5)), # 0x0 ~ 0x4, 
                "code_rate_LP_stream" : (xrange(0x0, 0x5)), # 0x0 ~ 0x4, 
                "guard_interval" : (xrange(0x0, 0x4)), # 0x0 ~ 0x3, 
                "transmission_mode" : (xrange(0x0, 0x3)), # 0x0 ~ 0x2, 
                "other_frequency_flag" : (0, 1), #
            }
    
    def __init__(self):
        super(TerrestialDeliverySystemDescriptor, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
######################################################################    
class Terrestial2DeliverySystemDescriptor(DvtDataBase):
    ''''''
    __vr = {
                "plp_id" : (xrange(0x0, 0x100)), # 0x0 ~ 0xff, 
                "T2_system_id" : (xrange(0x0, 0x10000)), # 0x0 ~ 0xffff, 
                "SISO_MISO" : (xrange(0x0, 0x2)), # 0x0 ~ 0x01, 
                "bandwidth" : (xrange(0x0, 0x06)), # 0x0 ~ 101, 
                "guard_interval" : (xrange(0x0, 0x7)), # 0x0 ~ 110, 
                "transmission_mode" : (xrange(0x0, 0x06)), # # 0x0 ~ 0x5,  
                "other_frequency_flag" : (xrange(0x0, 0x2)), # 0x0 ~ 0x1, 
                "tfs_flag" : (xrange(0x0, 0x2)), # 0x0 ~ 0x1, 
                "T2CellLoop_num" : None,
                "cellLoopItem" : None,
            }
    
    def __init__(self):
        super(Terrestial2DeliverySystemDescriptor, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
        
######################################################################       
class DeliverySystemDescriptor(DvtDataBase):
    ''''''
    __vr = {
                "network_type" : ("cable", "satellite", "terrestrial","terrestrial2","satellite2"), 
                "cable" : None, 
                "satellite" : None, 
                "terrestrial" : None,
                "terrestrial2" : None,
                "satellite2" : None,  
            }
    
    def __init__(self):
        super(DeliverySystemDescriptor, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr

######################################################################
class DataBroadcastIdDescriptor(DvtDataBase):
    ''''''
    __vr = {
                "OUI" : (xrange(0x0001, 0xFFFFFF)), # [0x0001, 0xFFFFFF], 
                "update_type" : (0x01, 0x01),    # fixed to 0x01, extend the range to (0x01, 0x02) to support SSU enhanced profile
                "selector_byte" : None
            }
    
    def __init__(self):
        super(DataBroadcastIdDescriptor, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
######################################################################
class Pmt(DvtDataBase):
    ''''''
    __vr = {
                "ssu_es_pid" : (range(0x20, 0x1FFF)), # 0x20 ~ 0x1FFE, 
                "data_broadcast_id_descriptor" : None
            }
    
    def __init__(self):
        super(Pmt, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
######################################################################
class TransportStream(DvtDataBase):
    ''''''
    __vr = {
                "transport_stream_id" : None, # [0x0000, 0xFFFF], 
                "original_network_id" : None, # [0x0000, 0xFFFF], 
                "service_list" : None, 
                "delivery_system_descriptor" : None,
            }
    
    def __init__(self):
        super(TransportStream, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
######################################################################
class Transport(DvtDataBase):
    ''''''
    __vr = {
                "actual" : None, # 
                "other" : None
            }
    
    def __init__(self):
        super(Transport, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
######################################################################
class CaDescriptor(DvtDataBase):
    ''''''
    __vr = {
                "ca_system_id" : None, 
                "ca_pid" : (xrange(0x20, 0x1FFF)), # 0x20 ~ 0x1FFE, 
            }
    
    def __init__(self):
        super(CaDescriptor, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
######################################################################
class Cat(DvtDataBase):
    ''''''
    __vr = {
                "ca_descriptor" : None
            }
    
    def __init__(self):
        super(Cat, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr 
######################################################################
class T2SubCellLoop(DvtDataBase):
    ''''''
    __vr = {
                "cell_id_extension_num" : None,
                "cell_id_extension" : None, 
                "transposer_frequency_num" : None,
                "transposer_frequency" : None 
            }
    
    def __init__(self):
        super(T2SubCellLoop, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr       

######################################################################
class T2CellCentreFrequencyLoop(DvtDataBase):
    ''''''
    __vr = {
                "center_frequency_num" : None,
                "center_frequency" : None 
            }
    
    def __init__(self):
        super(T2CellCentreFrequencyLoop, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr     
######################################################################      
class T2CellLoop(DvtDataBase):
    ''''''
    __vr = {
                "cell_id" :  (xrange(0x0, 0x10000)), # 0x0 ~ 0xffff, 
                "T2CellCentreFrequencyLoop" : None,     
                "T2SubCellLoop" : None
            }
    
    def __init__(self):
        super(T2CellLoop, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr        

######################################################################

class transport_stream_satellite2_descriptor(Descriptor):
   
    descriptor_tag = 0x79
    
    def bytes(self):

	    if (self.scrambling_sequence_selector == 0) and (self.multiple_input_stream_flag == 0):
	      fmt = "!B " 
	      return pack(fmt,
	                  self.smbr,	                  
                    )
 	    elif (self.scrambling_sequence_selector == 1) and (self.multiple_input_stream_flag == 0): 
	      fmt = "!BBH"  
	      return pack(fmt,
	                  self.smbr,
	                  self.scrambling_sequence_index_HB,
	                  self.scrambling_sequence_index_LH,
	                )
 	    elif (self.scrambling_sequence_selector == 0) and (self.multiple_input_stream_flag == 1): 
	      fmt = "!BB"  
	      return pack(fmt,
	                  self.smbr,
	                  self.input_stream_identifier,
	                )
 	    elif (self.scrambling_sequence_selector == 1) and (self.multiple_input_stream_flag == 1): 
	      fmt = "!BBHB"  
	      return pack(fmt,
	                  self.smbr,
	                  self.scrambling_sequence_index_HB,
	                  self.scrambling_sequence_index_LH,
	                  self.input_stream_identifier,	                  	                  
	                )	  
######################################################################
class transport_stream_s2_descriptor(DVBobject):

    def pack(self):
	transport_stream_sat_byte = string.join(
		    map(lambda x: x.pack(),
		    self.transport_stream_sat),
		    "")

	transport_stream_sat2_byte = string.join(
		    map(lambda x: x.pack(),
		    self.transport_stream_sat2),
		    "")
	fmt = "!%ds%ds" % (len(transport_stream_sat_byte) ,len(transport_stream_sat2_byte))
	return pack(fmt,
                transport_stream_sat_byte,
                transport_stream_sat2_byte
                )
	                	
######################################################################
class transport_stream_terrestrial2_descriptor(Descriptor):

    descriptor_tag = 0x7F

    def bytes(self):
	T2_cell_byte = string.join(
		    map(lambda x: x.pack(),
		    self.T2_cell_loop),
		    "")
		    
	fmt = "!BBHBB%ds" % len(T2_cell_byte)
	return pack(fmt,
           0x04,
           self.plp_id,
           self.T2_system_id,
           self.SISO_MISO_bandwidth,
           self.GTOT,
           T2_cell_byte
           )




######################################################################
class T2_cell_descriptor(DVBobject):

    def pack(self):
	T2_central_frequency_byte = string.join(
		    map(lambda x: x.pack(),
		    self.T2_central_frequency_loop),
		    "")
	T2_sub_cell_byte = string.join(
		    map(lambda x: x.pack(),
		      self.T2_sub_sell_loop),
		      "")    
	fmt = "!H%ds%ds" % (len(T2_central_frequency_byte) ,len(T2_sub_cell_byte))
	return pack(fmt,
                self.Cell_id,
                T2_central_frequency_byte,
                T2_sub_cell_byte,
	)

######################################################################
class T2_central_frequency_descriptor(DVBobject):

    def pack(self):
	center_frequency_length = self.center_frequency_num * 4

	center_frequency_byte = string.join(
		    map(lambda x: x.pack(),
		    self.center_frequency),
		    "")
 
	if self.tfs_flag == 1 :
	    fmt = "!B%ds" % len(center_frequency_byte)
	    return pack(fmt,
	                  center_frequency_length,
	                  center_frequency_byte
                    )
 	else : 
	    fmt = "!%ds" % len(center_frequency_byte)
	    return pack(fmt,
	                  center_frequency_byte
	)	
######################################################################
class T2_centlfreq_descriptor(DVBobject):

    def pack(self):
	    fmt = "!L"
	    return pack(fmt,
	                   self.center_frequency,
	)	

######################################################################
class T2_sub_sell_descriptor(DVBobject):

    def pack(self):
	sub_sell_length = self.cell_id_extension_num * 5

	sub_cell_extension_byte = string.join(
		    map(lambda x: x.pack(),
		    self.sub_cell_extension),
		    "")

	fmt = "!B%ds" % len(sub_cell_extension_byte)
	return pack(fmt,
                    sub_sell_length,
                    sub_cell_extension_byte,                    
	)                     

######################################################################
class T2_sub_cell_extension_descriptor(DVBobject):

    def pack(self):

	fmt = "!BL"
	return pack(fmt,
                    self.cell_id_extension,
                    self.transposer_frequency, 
	)    
            
        