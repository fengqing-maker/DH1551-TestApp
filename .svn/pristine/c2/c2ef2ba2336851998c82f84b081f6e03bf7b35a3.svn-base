#!/bin/bash

if [ $# -lt 5 ]
then
    /bin/echo "Usage:"
    /bin/echo " ssu-update.sh dvbssu_ddb_section_directory dsmcc_pid padding_on ratio dvbssu_dsi_dii_section_directory"
    /bin/echo "	dvbssu_ddb_section_directory: the directory to marshal in an object carousel.Only DDB is here."
    /bin/echo "	dsmcc_pid, referenced by PMTs using this carousel"
    /bin/echo "	padding_on, every section is padded, usuful with some buggy decoder, waste bandwith, default off"
    /bin/echo "	ratio, DSI/DII will follow after this number of DDBs."
    /bin/echo "	dvbssu_dsi_dii_section_directory:the directory to marshal in an object carousel.Only DSI and DII are here."
    /bin/echo " Example:"
    /bin/echo " ssu-update.sh dir1 2001 0 20 dir2"
    /bin/echo "	ddb_carousel_directory: dir1"
    /bin/echo "	pid: 2001"
    /bin/echo "	don't pad"
    /bin/echo "	ratio: DSI/DII will follow after every 20 DDBs"
    /bin/echo "	dsi_dii_carousel_directory: dir2"
    exit 65
fi

#Parameters passing
OCDIR=$1
PID=$2
PAD_ON=$3
RATIO_DSI_DII_DDB=$4
OCDIR_DSI_DII=$5

cp $OCDIR/DSI.sec $OCDIR_DSI_DII/DSI.sec
cp $OCDIR/DII-* $OCDIR_DSI_DII/
rm $OCDIR/DSI.sec
rm $OCDIR/DII-*.sec

i="0"

# Check if it is necessary to pad every sections or not, unluckly we have found some decoders having buggy section filtering that needed this

if [ "$PAD_ON" = "1" ]
then	
    #Every section will be padded to the minimum number of packets needed to contain it, all the packets are enqueued into the output ts file
    for file in $OCDIR/*.sec

    do
        /usr/local/bin/sec2ts $PID < $OCDIR_DSI_DII/DSI.sec >> $OCDIR/temp_ts
        /usr/local/bin/sec2ts $PID < $OCDIR_DSI_DII/DII-1.sec >> $OCDIR/temp_ts
        /usr/local/bin/sec2ts $PID < $file >> $OCDIR/temp_ts
	    let i+=1
      let "remainder = $i % $RATIO_DSI_DII_DDB" 
	    if [ $remainder -eq 0 ]; then
	      /bin/echo $i
        /usr/local/bin/sec2ts $PID < $OCDIR_DSI_DII/DSI.sec >> $OCDIR/temp_ts
        /usr/local/bin/sec2ts $PID < $OCDIR_DSI_DII/DII-1.sec >> $OCDIR/temp_ts
	    fi
    done    
 
    /usr/local/bin/tsfixcc $OCDIR/temp_ts > $OCDIR.ts
    rm $OCDIR/temp_ts 
else
    # All the single section files are enqueued in a single file, padding will occur only at the end of the last section
    for file in $OCDIR/*.sec
    do
#	    /bin/cat $OCDIR_DSI_DII/DSI.sec >> $OCDIR/temp_sec   
#	    /bin/cat $OCDIR_DSI_DII/DII-1.sec >> $OCDIR/temp_sec 
	    /bin/cat $file >> $OCDIR/temp_sec
	    let i+=1
      let "remainder = $i % $RATIO_DSI_DII_DDB" 
	    if [ $remainder -eq 0 ]; then
#	      /bin/echo $i
	      /bin/cat $OCDIR_DSI_DII/DSI.sec >> $OCDIR/temp_sec   
	      /bin/cat $OCDIR_DSI_DII/DII-1.sec >> $OCDIR/temp_sec 
	    fi
    done
    
		if [ $i -lt $RATIO_DSI_DII_DDB ]; then
#           	    /bin/echo $i
		    /bin/cat $OCDIR_DSI_DII/DSI.sec >> $OCDIR/temp_sec   
		    /bin/cat $OCDIR_DSI_DII/DII-1.sec >> $OCDIR/temp_sec 
		fi
    
    /usr/local/bin/sec2ts $PID < $OCDIR/temp_sec > $OCDIR.ts
        
    rm $OCDIR/temp_sec
fi

