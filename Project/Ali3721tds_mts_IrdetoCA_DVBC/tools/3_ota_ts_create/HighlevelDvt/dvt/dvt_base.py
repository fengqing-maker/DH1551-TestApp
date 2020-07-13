#!/usr/bin/env python

#
# Created on Oct 27, 2011
#
# @author: ethan.li
#

import sys
import os
import re
import inspect
import struct
import socket
import shutil
import binascii
import time


def __abort(err):
    '''Print error message and exit'''
    sys.stderr.write('\n' + err + '\n')
    sys.exit(2)

def __line():
    try:
        raise Exception
    except:
        f = sys.exc_info()[2].tb_frame.f_back
        return (f.f_code.co_name, f.f_lineno)

def __file():
    return inspect.currentframe().f_code.co_filename

def __getTime():
    return '%s' % (time.strftime('%b %d %H:%M:%S', time.localtime(time.time())))

def dvtprintf(type, message):
    print '[%s] DVT-SUITE: %s>> %s' % (__getTime(), type, message)


__debugOn = False

def dvtDisableDbg():
    global __debugOn
    __debugOn = False

def dvtEnableDbg():
    global __debugOn
    __debugOn = True

def dvtdbg(message):
    global __debugOn
    if __debugOn:
        dvtprintf("Debug", message)

def dvtmsg(message):
    dvtprintf('@', message)

def dvtAssert(condition, log = None):
    ''''''
    if not (condition):
        if log is not None:
            dvtError(log)
        dvtprintf(
               "Assert", 
               "failed function: %s, line: %d" % __line()
               )

def dvtError(exception):
    dvtprintf("Error", exception)
    __abort(exception)
    
def dvtPrintStrAsAscii(title, string):
    dvtdbg("%s%s" % (title, binascii.b2a_hex(string)))

def dvtStrToInt(string):
    ''''''
    try:
        if re.match(r"0x", string): # Hex
            integer = int(string, 16)
        elif re.match(r"0b", string):   # Bin
            integer = int(string, 2)
        else:
            integer = int(string, 10)   # Dec
        return integer
    except:
        raise dvtError("error convert string to integer!")

def dvtNetBytesToInt(nb):
    ''''''
    length = len(nb)
    try:
        if length == 1:
            out = struct.unpack("!B", nb)
        elif length == 2:
            out = struct.unpack("!H", nb)
        elif length == 4:
            out = struct.unpack("!I", nb)
        else:
            raise dvtError("Unsupported length of network byte: %d" % length)
    except struct.error, msg:
        raise dvtError("error convert network bytes to integer! %s" % msg)

    return out[0]  # socket.ntohs(int(integer, 10))

def dvtCreateDir(fullpath):
    ''''''
    if not os.path.exists(fullpath):
        os.mkdir(fullpath)
    return fullpath

def dvtDelFileFolder(src):
    ''''''
    if os.path.isfile(src):
        try:
            os.remove(src)
        except:
            pass
    elif os.path.isdir(src):
        for item in os.listdir(src):
            itemsrc = os.path.join(src, item)
            dvtDelFileFolder(itemsrc)
        try:
            os.rmdir(src)
        except:
            pass
  
def dvtCopyFile(src, dst):
    ''''''
    shutil.copyfile(src, dst)    
    
def dvtEnumFilebyExt(rootdir, ext):  
    ''''''
    rc = []
    for parents, dirs, files in os.walk(rootdir):
        for file in files:
            if re.search(ur".%s" % ext, file):
                rc.append(file)
    return rc

class DvtDataBase(object):
    ''''''
    def __init__(self):
        ''''''
        self._classMembersValidRange = {}   # (member, range))
        self._classMemberList = {}  # class members dict (member, value)
        pass
        
    def _setClassMembersValidRange(self, vr):
        ''''''
        self._classMembersValidRange = vr
    
    def __sanityCheck(self, member, value):
        ''''''
        dvtAssert(
                  member in self._classMembersValidRange, 
                  "No such member \"%s\" in this class!!!" % member
                  )   # OR dvtAssert (self._classMembersValidRange.has_key(member))
        if self._classMembersValidRange[member] is not None:
            # self.__checkValue(self, member, value)  # virtual
            dvtAssert(
                      value in self._classMembersValidRange[member], 
                      "Member's value out of range!!!"
                      )
            
    def setMember(self, member, value):
        ''''''
        self.__sanityCheck(member, value)
        self._classMemberList[member] = value
        
    def getMember(self, member):
        ''''''
        dvtAssert(member in self._classMembersValidRange)   # OR dvtAssert (self._classMembersValidRange.has_key(member))
        return self._classMemberList[member]
    
    def getObject(self):
        ''''''
        return self._classMemberList


class DvtFolders:
    """"""
    DIR_PATTERNS = "./patterns"
    DIR_TOOLS = "./tools"
    DIR_WORKFOLDER = "./workfolder"
    DIR_OUTPUT = "./output"
    DIR_INPUT = "./input"
    
    
