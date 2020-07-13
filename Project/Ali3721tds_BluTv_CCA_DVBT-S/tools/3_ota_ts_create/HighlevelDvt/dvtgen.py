#!/usr/bin/env python

#
# Created on Oct 27, 2011
#
# @author: ethan.li
#

'''Usage: ./dvtgen.py [OPTIONS] <input file(s)>
Generate transport stream files for Loader V5 High-level DVT.

    -d, --debug               Debug mode
    -h, --help                Usage information
    -o, --output=NAME         Write output transport stream to file NAME

Notes:    
- NEVER remove or modify the files in the sub-folder "./dvt".
- The XML file and the corresponding CD5 file (more precisely, the CD5 file wrapped within section 
<cd5></cd5> in the XML file) MUST be placed in the same folder.
- If no output file is specified, "dvt.ts" is set as the default transport stream file name and 
it would be generated in the same folder.
'''

# python lib
import sys
import os
import getopt
import re

# dvt suite specific
import dvt
from dvt.dvt_xml_importer import *
from dvt.dvt_tsbuild import *
from dvt.dvt_tsmux import *


class Loader5HighLevelDvt:        
    '''
    Main procedure
    '''
    
    def __init__(self):
        self.__sysArgv = self.__getSysArgv()    # valid system arguments
        self.__var = {'output' : "dvt.ts", } # global variables
        self.__main() # GO!!!
    
    def __getSysArgv(self):
        if len(sys.argv) < 1:
            return
        
        if 'python' in sys.argv[0]:
            sys.argv = sys.argv[1:]
            
        return sys.argv[1:]
    
    def __usageWords(self):
        '''Build tool usage words'''
        return __doc__ % self.__sysArgv[0]
    
    def __usage(self, err = None):
        '''Print usage information and exit'''
        if err is None:
            print self.__usageWords()
            sys.exit(0)
        else:
            sys.stderr.write(self.usageWords())
            
    def __setOptions(self, options):
        '''Set options parsed from command line'''
        for opt, arg in options:
            if opt in ("-h", "--help"):
                self.__usage()
                sys.exit(2)
            elif opt in ('-o', '--output'):
                self.__var['output'] = arg
            elif opt in ('-d', '--debug'):
                dvtEnableDbg()
            else:
                assert False, "unhandled option"
    
    def __setArgs(self, arguments):
        '''Set arguments parsed from command line'''
        for arg in arguments:
            if re.search(ur".xml", arg):
                self.__var['xmlfile'] = arg
                
    def __processArgs(self):
        '''Process arguments'''
        try:
            opts, args = getopt.getopt(
                            self.__sysArgv, 
                            'ho:d', ['help', 'output=', 'debug']
                            )

        except getopt.GetoptError:
            self.usage()
            sys.exit(2)
        
        self.__setOptions(opts)
        self.__setArgs(args)
        return True
    
    def __preprocess(self):
        ''''''
        dvtDisableDbg()
        dvtDelFileFolder(DvtFolders.DIR_WORKFOLDER)
        dvtCreateDir(DvtFolders.DIR_WORKFOLDER)
        
    def __postprocess(self):
        ''''''
        pass
        
    def __main(self):
        '''Main procedure for high-level DVT suite'''
        result = True
        
        # preprocess
        self.__preprocess()
        
        # process input arguments from command line
        result = self.__processArgs()
        
        # start DVT
        if result:
            dvtmsg("DVT case: %s" % (self.__var['xmlfile']))
        
        # step 1: read configurations (read & parse the xml file)
        if result:
            dvtdbg("\n@@@@@@ Step 1: Parsing XML @@@@@@")
            xmlItem = DvtXmlImporter(self.__var['xmlfile'])
            result = xmlItem.analyseXml()
        
        # step 2: execute OpenCaster scripts to generate data strings 
        if result:
            # go through the download list and handle each download
            dvtdbg("\n@@@@@@ Step 2: Building transform data @@@@@@")
            for (k, v) in xmlItem.getDownloadList().items():

                dvtdbg("%s ---> %s" % (k, v))
                
                cons = OCConstructDownloadMessage(v)
                
                muxer = OCTsMuxer("Irdeto Muxer", cons, self.__var['output'])
                
                # do construct
                cons.construct()
                
                # step 3: execute OpenCaster scripts to generate the TS file.
                if result:
                    dvtdbg("\n@@@@@@ Step 3: Generate transform stream file @@@@@@")
                    muxer.doMux()
        
        # post process
        self.__postprocess()
        
        if result:
            dvtmsg("done ^ ^")
        


if __name__ == '__main__':
    '''This code runs if executed directly from the command-line.'''
    
    # DVT main procedure starts here!!!
    dvt = Loader5HighLevelDvt()

    
    