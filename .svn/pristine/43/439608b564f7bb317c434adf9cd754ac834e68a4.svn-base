#!/usr/bin/env python

#
# Created on Oct 27, 2011
#
# @author: ethan.li
#

import sys
import os

from dvt_base import *


class OCMuxItem(object):

    def __init__(self, tsFileName, bitrate, carousel = False):
        """"""
        self.tsFileName = tsFileName    # .ts file name
        self.bitrate = bitrate    # target bit rate
        self.isCarousel = carousel  # is it a carousel ts file?

class VirtualTsMuxer(object):        
    
    def addMuxItem(self, muxItem):
        raise NotImplementedError("%s : Subclass me!" % (self.__class__))
    
    def doMux(self):
        raise NotImplementedError("%s : Subclass me!" % (self.__class__))
    
    
class OCTsMuxer(VirtualTsMuxer):
    
    __streams = {
        "NULL" : 3008,   # table : bitrate
        "NIT" : 1400,   # table : bitrate
        "BAT" : 1400,   # table : bitrate
        "PAT" : 3008,   # table : bitrate
        "PMT" : 3008,   # table : bitrate
        "CAT" : 3008,   # table : bitrate
        "SDT" : 3008,   # table : bitrate
        "EMM" : 3008,   # table : bitrate
        "SSU" : 200000,   # table : bitrate
        }
    
    __temporary_ts_file = "temp.ts"

    def __init__(self, name, target, ts = 'fifomuxed.ts', totalBitrate = 400000):
        '''
        Constructor
        '''
        self.name = name
        target.register(self)
        self.targetTsFileFullPath = ts  # muxed transport stream
        self.totalBitrate = totalBitrate    # total bit rate
        
        self.__ocMuxItemList = []
        
        self.__prepareBasicPacket()
        
        __multilinecomment = """
        self.__null = OCMuxItem('null.ts', 3008)  # null packet
        self.bat = OCMuxItem('firstbat.ts', 1400)  # BAT
        self.nit = OCMuxItem('firstnit.ts', 1400)  # NIT
        self.pat = OCMuxItem('firstpat.ts', 3008)  # PAT
        self.sdt = OCMuxItem('firstsdt.ts', 3008)  # SDT		
        self.pmt = OCMuxItem('firstpmt.ts', 3008)  # PMT
        self.emm = OCMuxItem('firstemm.ts', 3008)  # EMM
        self.ssu = OCMuxItem('datacarousel.ts', 100000)  # SSU
        """
        
    def addMuxItem(self, ocMuxItem):
        # newMuxItem = OCMuxItem(ocMuxItem)
        self.__ocMuxItemList.append(ocMuxItem)
        
    def __prepareBasicPacket(self):
        # null packet
        dvtCopyFile("%s/null.ts" % DvtFolders.DIR_PATTERNS, "%s/null.ts" % DvtFolders.DIR_WORKFOLDER)
        self.addMuxItem(OCMuxItem('null.ts', 3008))   # null packet
        # null packet
        dvtCopyFile("%s/firstvideo.ts" % DvtFolders.DIR_PATTERNS, "%s/firstvideo.ts" % DvtFolders.DIR_WORKFOLDER)
        self.addMuxItem(OCMuxItem('firstvideo.ts', 100000))
        # null packet
        dvtCopyFile("%s/firstaudio.ts" % DvtFolders.DIR_PATTERNS, "%s/firstaudio.ts" % DvtFolders.DIR_WORKFOLDER)
        self.addMuxItem(OCMuxItem('firstaudio.ts', 16000))   # null packet
        
    def __calcNullPacketBitrate(self):
        """
        Calculate null packets bitrate. 
        It is defined by total bitrate of output TS minus bitrates of all input TSs including bitrates of TS tables.
        """
        bitrate = self.totalBitrate
        for item in self.__ocMuxItemList:
            bitrate -= item.bitrate
        
        __multilinecomment = """            
        self.__null.bitrate = self.totalBitrate 
                            - self.bat.bitrate 
                            - self.nit.bitrate 
                            - self.pat.bitrate
                            - self.sdt.bitrate							
                            - self.pmt.bitrate
                            - self.emm.bitrate 
                            - self.ssu.bitrate 
        """
        # Update null packets bit rate
        self.__ocMuxItemList[0].bitrate = bitrate
        
    def doMux(self):
        """
        Generate the final transport stream containing all the data sections
        """
        # Calculate the bit rate of null packets
        self.__calcNullPacketBitrate()
        # Execute "tscbrmuxer" to generate the final transport stream
        __multilinecomment = """
        command = 'tscbrmuxer b:%d %s b:%d %s b:%d %s c:%d %s > %s' 
                    %self.__null.bitrate %self.null.tsFileName
                    %self.pat.bitrate %self.pat.tsFileName
					%self.sdt.bitrate %self.sdt.tsFileName
                    %self.pmt.bitrate %self.pmt.tsFileName
                    %self.ssu.bitrate %self.ssu.tsFileName
        """
        command = 'tscbrmuxer '
        for item in self.__ocMuxItemList:
            if not item.isCarousel:
                command += 'b:%d %s ' % (
                                         item.bitrate, 
                                         "%s/%s" % (
                                                    DvtFolders.DIR_WORKFOLDER, 
                                                    item.tsFileName
                                                    )
                                         )
            else:
                command += 'c:%d %s ' % (
                                         item.bitrate, 
                                         "%s/%s" % (
                                                    DvtFolders.DIR_WORKFOLDER, 
                                                    item.tsFileName
                                                    )
                                         )
        # command += '> %s ' % (self.targetTsFileFullPath)
        command += '> %s/%s ' % (DvtFolders.DIR_WORKFOLDER, self.__temporary_ts_file)    
        command += '2>/dev/null'   # hide the output information
        dvtdbg(command)
        
        os.system(command)           
        
        # bitrate adjustment
        command = 'tsstamp %s/%s %d > %s &' % (
                                               DvtFolders.DIR_WORKFOLDER, 
                                               self.__temporary_ts_file, 
                                               self.totalBitrate, 
                                               self.targetTsFileFullPath
                                               )

        os.system(command)
        

    def notify(self, event):
        """"""
        msg = event[0].strip()
        file = event[1].strip()
        dvtmsg("---- NEW mux item: %s" % msg)
        if msg in OCTsMuxer.__streams:
            carousel = False
            if msg == "SSU":
                carousel = True
            self.addMuxItem(OCMuxItem(file, OCTsMuxer.__streams[msg], carousel))
            


