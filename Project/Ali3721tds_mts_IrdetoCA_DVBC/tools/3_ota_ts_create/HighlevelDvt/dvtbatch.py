#!/usr/bin/env python

#
# Created on Nov 24, 2011
#
# @author: ethan.li
#

'''Usage: ./dvtbatch.py
Batch generate transport stream files for Loader V5 High-level DVT.
please follow these steps to batch generate the transport streams:
1. Edit and configure the test case file "dvt.xml"(XML format) 
2. Copy the customer signature CD5 file as dvt.CD5 into HighlevelDvt folder;
3. Execute this script and wait for a while (the duration of this procedure depends on the number of cases and the size of CD5 files);
4. If no error occurs, get the transport stream files in "./ouput" after it is finished. Each transport stream file is typically
named as [XML file name].ts (e.g., dvt.xml.ts).
'''

import os

import dvt
from dvt import dvt_base
from dvtgen import *


if __name__ == '__main__':
    '''This code runs if executed directly from the command-line.'''
    
    print __doc__
    
    # batch procedure starts here!!!
    
    dvtmsg("DVT batch has been launched.")
   
    # clean all the input	
    dvtDelFileFolder(DvtFolders.DIR_INPUT)
    dvtCreateDir(DvtFolders.DIR_INPUT)	

    # cp dvt.xml and dvt.CD5 into input folder
    command = "cp ./dvt.CD5 ./input"
    print command
    os.system(command)	
	
    command = "cp ./dvt.CD5 ./dvt_ts1.CD5"
    print command
    os.system(command)	

    command = "./tools/TestDataGenerator -E8 ./dvt_ts1.CD5"
    print command
    os.system(command)
	
    command = "cp ./dvt_ts1.CD5 ./input"
    print command
    os.system(command)
	
    command = "cp ./dvt.xml ./input"
    print command
    os.system(command)
    
    # clean all the outputs
    dvtDelFileFolder(DvtFolders.DIR_OUTPUT)
    dvtCreateDir(DvtFolders.DIR_OUTPUT)

	# build the xml list for cases 
    command = "python ./dvt_xml.py"
    print command
    os.system(command)
   
    # get case list
    cases = dvtEnumFilebyExt(DvtFolders.DIR_INPUT, "xml")
    dvtmsg("(%d) cases in all." % len(cases))
    
    # process all the cases
    for case in cases:
        command = "python ./dvtgen.py --output=%s/%s.ts %s/%s" % (
                        DvtFolders.DIR_OUTPUT, case, 
                        DvtFolders.DIR_INPUT, case
                        )
        print command
        os.system(command)
        
    dvtmsg("Batch completed.")
    
    
    