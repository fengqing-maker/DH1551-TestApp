How to generate high level DVT suite test streams.

1) compile the dvt.xml with manufacturer's input parameters to replace the XXXX in the file.
   the detail is : OUI is a 24-bit field containing an IEEE OUI, 
				   cd5 file name is manufacturer high level application image file name. 
				   linkage_descriptor_location is to identify the the linkage descriptor position.
				   filter number is the EMM filter parameters.
				   new_variant and new_subvariant is for migration function.
				   ca_system_id is allocated for CA system ID.
				   ca_pid is allocated for EMM PID.
				   manufacturer_id and hardware_version is allocated from IRDETO RDA department.
				   download_sequence_number is STB current download sequence number.
				   network_type is allocated from [cable, satellite, terrestrial, satellite2 terrestrial2].				   
					
2) copy the manufacturers high level application code image to replace dvt.CD5

3)run the dvtbatch.py/a to set up all the test streams.

