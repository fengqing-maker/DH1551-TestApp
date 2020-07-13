#!/usr/bin/env python

#
# Created on Oct 27, 2011
#
# @author: ethan.li
#

from dvt_dvb import *


class ManufacturerInfo(DvtDataBase):
    """"""
    __vr = {
                "name" : None,
                "OUI" : (xrange(0x1, 0xFFFFFF)) # not include 0xFFFFFF, 
            }
    
    def __init__(self):
        super(ManufacturerInfo, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
            

class GlobalOptions(DvtDataBase):
    """"""
    __vr = {
                "emm_trigger" : ("on", "off"), 
                "linkage_descriptor_location" : ("NIT", "BAT"), 
                "ssu_location" : ("actual", "other"),
                "linkage_descriptor_multiple" : ("on", "off"),						
            }
    
    def __init__(self):
        super(GlobalOptions, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
        
  
class Cd5(DvtDataBase):
    """"""
    __vr = {
                "name" : None
            }
    
    def __init__(self):
        super(Cd5, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr


class Service(DvtDataBase):
    """"""
    __vr = {
                "service_id" : (xrange(0x0000, 0xFFFF)), # not include 0xFFFF, 
                "service_type" : (0x01, 0x0C), # 0x01 for digital television, 0x0C for software update
                "ssu_pmt_pid" : (xrange(0x0000, 0x1FFF)), # not include 0x1FFF
                "pmt" : None, 
            }
    
    def __init__(self):
        super(Service, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr

class ForceDownloadEmm(DvtDataBase):
    """"""
    __vr = {}
    
    def __init__(self):
        super(ForceDownloadEmm, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr

class MigrationEmm(DvtDataBase):
    """"""
    __vr = {
                "new_variant" : (xrange(0x0001, 0x10000)), # 0x0001 ~ 0xFFFE,   for test case step 10_02 new_variant set as 0xffff
                "new_subvariant" : (xrange(0x0000, 0x10000)), # 0x0000 ~ 0xFFFE,  for test case step 10_04 new_subvariant set as 0xffff 
            }
    
    def __init__(self):
        super(MigrationEmm, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr
                        
class IrdEmm(DvtDataBase):
    """"""
    __vr = {
                "filter_number" : (xrange(0x10, 0x20)), # 0x10 ~ 0x1F. For CCA client, fixed to 0x14
                "message_type" : ("force download", "migration"), # 
                "force download" : None, # force download
                "migration" : None, # migration
            }
    
    def __init__(self):
        super(IrdEmm, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr

class Emm(DvtDataBase):
    """"""
    __vr = {
                "ird_emm" : None, # 
                "cat" : None, # 
            }
    
    def __init__(self):
        super(Emm, self).__init__() # Every child class MUST do it FIRST in __init__!!!
        self._classMembersValidRange = self.__vr


__CRC16_LOOKUP_TABLE = [
    0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
    0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
    0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
    0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
    0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
    0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
    0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
    0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
    0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
    0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
    0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
    0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
    0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
    0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
    0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
    0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
    0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
    0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
    0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
    0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
    0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
    0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
    0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
    0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
    0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
    0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
    0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
    0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
    0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
    0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
    0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
    0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
    ]

def irdetoCrc16(data):
    """
    This is a python version translated from c version in KMS
    """
    
    try:
        # TODO:
        crc = 0
        for c in data:
            crc = ((crc >> 8) & 0xFF) ^ __CRC16_LOOKUP_TABLE[(crc ^ ord(c)) & 0xFF]
    except ImportError:
        dvtError("Failed to calculate CRC32!!!")
    return crc
    