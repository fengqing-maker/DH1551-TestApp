#!/usr/bin/env python

#
# Created on April 27, 2013
#
#


from xml.dom import minidom  
import codecs  

def genStep04xmlFile(inputfilename,outfilename,triggercontrol,emmonoff):
        xmldoc = minidom.parse(inputfilename)  

        downloadNode = xmldoc.getElementsByTagName("download")[0]  
        print("The name attribute of downloadNode: %s"%(downloadNode.getAttribute("id")))  
		
        download_sequence_numberNode = downloadNode.getElementsByTagName("download_sequence_number")[0]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode.firstChild.data)) 
		
        download_sequence_numberNode2 = downloadNode.getElementsByTagName("download_sequence_number")[2]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode2.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode2.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode2.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode2.firstChild.data)) 
		
        trigger_control_byteNode = downloadNode.getElementsByTagName("trigger_control_byte")[0]  
        print("The attribute of trigger_control_byte: %s"%(trigger_control_byteNode.getAttribute("id")))  
        trigger_control_byteNode.firstChild.data = triggercontrol
        print("The data of trigger_control_byte: %s"%(trigger_control_byteNode.firstChild.data))  	

        trigger_control_byteNode = downloadNode.getElementsByTagName("trigger_control_byte")[2]  
        print("The attribute of trigger_control_byte: %s"%(trigger_control_byteNode.getAttribute("id")))  
        trigger_control_byteNode.firstChild.data = triggercontrol
        print("The data of trigger_control_byte: %s"%(trigger_control_byteNode.firstChild.data))  
		

        emm_triggerNode = downloadNode.getElementsByTagName("emm_trigger")[0]  
        emm_triggerNode.firstChild.data = emmonoff
        print("The data of emm_trigger: %s"%(emm_triggerNode.firstChild.data)) 
		
        impl = minidom.getDOMImplementation()
        newdoc = impl.createDocument('\n', "LOADER_V5_HIGHLEVEL_DVT_CONFIG", None)  
        rootNode = newdoc.documentElement
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)
        rootNode.appendChild(downloadNode)
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)	
		
		#Save this XML to file
        result_file = open(outfilename, 'wb+')
        writer = codecs.lookup('utf-8')[3](result_file)
        newdoc.writexml(writer,addindent='  ',encoding='utf-8')
        writer.close() 	

def genStep05xmlFile(inputfilename,outfilename,downloadmode,emmonoff):
        xmldoc = minidom.parse(inputfilename)  

        downloadNode = xmldoc.getElementsByTagName("download")[0]  
        print("The name attribute of downloadNode: %s"%(downloadNode.getAttribute("id")))  
		
        download_sequence_numberNode = downloadNode.getElementsByTagName("download_sequence_number")[0]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode.firstChild.data)) 
		
        download_sequence_numberNode2 = downloadNode.getElementsByTagName("download_sequence_number")[2]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode2.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode2.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode2.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode2.firstChild.data)) 
		
        download_modeNode = downloadNode.getElementsByTagName("download_mode")[0]  
        print("The attribute of downloadmode: %s"%(download_modeNode.getAttribute("id")))  
        download_modeNode.firstChild.data = downloadmode
        print("The data of downloadmode: %s"%(download_modeNode.firstChild.data))  		

        download_modeNode = downloadNode.getElementsByTagName("download_mode")[2]  
        print("The attribute of downloadmode: %s"%(download_modeNode.getAttribute("id")))  
        download_modeNode.firstChild.data = downloadmode
        print("The data of downloadmode: %s"%(download_modeNode.firstChild.data)) 	

        emm_triggerNode = downloadNode.getElementsByTagName("emm_trigger")[0]  
        emm_triggerNode.firstChild.data = emmonoff
        print("The data of emm_trigger: %s"%(emm_triggerNode.firstChild.data)) 		
		
        impl = minidom.getDOMImplementation()
        newdoc = impl.createDocument('\n', "LOADER_V5_HIGHLEVEL_DVT_CONFIG", None)  
        rootNode = newdoc.documentElement
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)
        rootNode.appendChild(downloadNode)
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)	
		
		#Save this XML to file
        result_file = open(outfilename, 'wb+')
        writer = codecs.lookup('utf-8')[3](result_file)
        newdoc.writexml(writer,addindent='  ',encoding='utf-8')
        writer.close() 			


def genStep06xmlFile(inputfilename,outfilename,oui,manu,hard,variant,subvariant,tiggercontrol,downloadmode,downloadseq,downloadseqNum,subvariantEq0,descriptorNum,emmonoff):
        xmldoc = minidom.parse(inputfilename)  

        downloadNode = xmldoc.getElementsByTagName("download")[0]  
        print("The name attribute of downloadNode: %s"%(downloadNode.getAttribute("id")))  
		
        download_sequence_numberNode = downloadNode.getElementsByTagName("download_sequence_number")[0]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode.firstChild.data)) 
		
        download_sequence_numberNode2 = downloadNode.getElementsByTagName("download_sequence_number")[2]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode2.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode2.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode2.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode2.firstChild.data)) 
		
        if(oui):
            OUINode = downloadNode.getElementsByTagName("OUI")[descriptorNum + 1]  
            print("The attribute of OUI: %s"%(OUINode.getAttribute("id")))  
            oui = int(eval(OUINode.firstChild.data));
            print("The data of OUI: 0x%x"%(oui)) 		
            oui = oui + 1;
            OUINode.firstChild.data = hex(oui)		
            print("The data of OUI: %s"%(OUINode.firstChild.data)) 		
		
        if(manu):
            manufacturer_idNode = downloadNode.getElementsByTagName("manufacturer_id")[descriptorNum]  
            print("The attribute of manufacturer_id: %s"%(manufacturer_idNode.getAttribute("id")))  
            manuId = int(eval(manufacturer_idNode.firstChild.data));
            print("The data of manufacturer_id: 0x%x"%(manuId)) 		
            manuId = manuId + 1;
            manufacturer_idNode.firstChild.data = hex(manuId)		
            print("The data of manufacturer_id: %s"%(manufacturer_idNode.firstChild.data)) 	

        if(hard):
            hardware_versionNode = downloadNode.getElementsByTagName("hardware_version")[descriptorNum]  
            print("The attribute of hardware_version: %s"%(hardware_versionNode.getAttribute("id")))  
            hardId = int(eval(hardware_versionNode.firstChild.data));
            print("The data of hardware_version: 0x%x"%(hardId)) 		
            hardId = hardId + 1;
            hardware_versionNode.firstChild.data = hex(hardId)		
            print("The data of hardware_version: %s"%(hardware_versionNode.firstChild.data)) 				

        if(variant):
            variantNode = downloadNode.getElementsByTagName("variant")[descriptorNum]  
            print("The attribute of variant: %s"%(variantNode.getAttribute("id")))  
            vari = int(eval(variantNode.firstChild.data));
            print("The data of variant: 0x%x"%(vari)) 		
            vari = vari + 1;
            variantNode.firstChild.data = hex(vari)		
            print("The data of variant: %s"%(variantNode.firstChild.data)) 
			
        if(subvariant):
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[descriptorNum]  
            print("The attribute of subvariant: %s"%(subvariantNode.getAttribute("id")))  
            subvari = int(eval(subvariantNode.firstChild.data));
            print("The data of subvariant: 0x%x"%(subvari)) 		
            subvari = subvari + 1;
            subvariantNode.firstChild.data = hex(subvari)		
            print("The data of subvariant: %s"%(subvariantNode.firstChild.data)) 

        if(tiggercontrol):
            tiggercontrolNode = downloadNode.getElementsByTagName("trigger_control_byte")[descriptorNum]  
            print("The attribute of tiggercontrol: %s"%(tiggercontrolNode.getAttribute("id")))  
            tiggercontrolNode.firstChild.data = "0x00"		
            print("The data of tiggercontrol: %s"%(tiggercontrolNode.firstChild.data)) 
			
        if(downloadmode):
            downloadmodeNode = downloadNode.getElementsByTagName("download_mode")[descriptorNum]  
            print("The attribute of download_mode: %s"%(downloadmodeNode.getAttribute("id")))  
            downloadmodeNode.firstChild.data = "0xFF"		
            print("The data of download_mode: %s"%(downloadmodeNode.firstChild.data)) 			

        if(downloadseq):
            downloadseqNode = downloadNode.getElementsByTagName("download_sequence_number")[descriptorNum]  
            print("The attribute of downloadseq: %s"%(downloadseqNode.getAttribute("id")))  
            dls = int(eval(downloadseqNode.firstChild.data));
            print("The data of downloadseq: 0x%x"%(seq)) 		
            dls = dls + downloadseqNum - 1 ;
            downloadseqNode.firstChild.data = hex(dls)		
            print("The data of downloadseq: %s"%(downloadseqNode.firstChild.data)) 
			
        if(subvariantEq0):
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[0]  
            print("The attribute of subvariant: %s"%(subvariantNode.getAttribute("id")))  		
            subvari = 0x00;
            subvariantNode.firstChild.data = hex(subvari)		
            print("The data of subvariant: %s"%(subvariantNode.firstChild.data))

            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[2]  
            print("The attribute of subvariant: %s"%(subvariantNode.getAttribute("id")))  		
            subvari = 0x00;
            subvariantNode.firstChild.data = hex(subvari)		
            print("The data of subvariant: %s"%(subvariantNode.firstChild.data)) 

        emm_triggerNode = downloadNode.getElementsByTagName("emm_trigger")[0]  
        emm_triggerNode.firstChild.data = emmonoff
        print("The data of emm_trigger: %s"%(emm_triggerNode.firstChild.data)) 					
			
        impl = minidom.getDOMImplementation()
        newdoc = impl.createDocument('\n', "LOADER_V5_HIGHLEVEL_DVT_CONFIG", None)  
        rootNode = newdoc.documentElement
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)
        rootNode.appendChild(downloadNode)
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)	
		
		#Save this XML to file
        result_file = open(outfilename, 'wb+')
        writer = codecs.lookup('utf-8')[3](result_file)
        newdoc.writexml(writer,addindent='  ',encoding='utf-8')
        writer.close() 	

def genStep07xmlFile(inputfilename,outfilename):
        xmldoc = minidom.parse(inputfilename)  

        downloadNode = xmldoc.getElementsByTagName("download")[0]  
        print("The name attribute of downloadNode: %s"%(downloadNode.getAttribute("id")))  
		
        download_sequence_numberNode = downloadNode.getElementsByTagName("download_sequence_number")[1]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode.firstChild.data)) 

        download_sequence_numberNode2 = downloadNode.getElementsByTagName("download_sequence_number")[2]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode2.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode2.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode2.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode2.firstChild.data)) 
		
        linkage_descriptor_multipleNode = downloadNode.getElementsByTagName("linkage_descriptor_multiple")[0]  
        print("The attribute of manufacturer_id: %s"%(linkage_descriptor_multipleNode.getAttribute("id")))  
        linkage_descriptor_multipleNode.firstChild.data = "on"		
        print("The data of manufacturer_id: %s"%(linkage_descriptor_multipleNode.firstChild.data)) 

        manufacturer_idNode = downloadNode.getElementsByTagName("manufacturer_id")[0]  
        print("The attribute of manufacturer_id: %s"%(manufacturer_idNode.getAttribute("id")))  
        manuId = int(eval(manufacturer_idNode.firstChild.data));
        print("The data of manufacturer_id: 0x%x"%(seq)) 		
        manuId = manuId + 1;
        manufacturer_idNode.firstChild.data = hex(manuId)		
        print("The data of manufacturer_id: %s"%(manufacturer_idNode.firstChild.data)) 		
		
        impl = minidom.getDOMImplementation()
        newdoc = impl.createDocument('\n', "LOADER_V5_HIGHLEVEL_DVT_CONFIG", None)  
        rootNode = newdoc.documentElement
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)
        rootNode.appendChild(downloadNode)
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)	
		
		#Save this XML to file
        result_file = open(outfilename, 'wb+')
        writer = codecs.lookup('utf-8')[3](result_file)
        newdoc.writexml(writer,addindent='  ',encoding='utf-8')
        writer.close() 	

def genStep09xmlFile(inputfilename,outfilename,other):
        xmldoc = minidom.parse(inputfilename)  

        if not (other):
			CD5Node = xmldoc.getElementsByTagName("cd5")[0]
			print("The name attribute of CD5Node: %s"%(CD5Node.getAttribute("id")))  
			dvt_ts1Node = CD5Node.getElementsByTagName("name")[0]
			print("The attribute of dvt_ts1Node: %s"%(dvt_ts1Node.getAttribute("id")))  
			dvt_ts1Node.firstChild.data = "dvt_ts1.CD5";
			print("The data of dvt_ts1Node: %s"%(dvt_ts1Node.firstChild.data))			
			optionNode = xmldoc.getElementsByTagName("options")[0]  
			print("The name attribute of options: %s"%(optionNode.getAttribute("id")))  
			ssu_locationNode = optionNode.getElementsByTagName("ssu_location")[0]
			print("The attribute of ssu_locationNode: %s"%(ssu_locationNode.getAttribute("id")))  
			ssu_locationNode.firstChild.data = "other";
			print("The data of ssu_locationNode: %s"%(ssu_locationNode.firstChild.data)) 	
			
        downloadNode = xmldoc.getElementsByTagName("download")[0]  
        print("The name attribute of downloadNode: %s"%(downloadNode.getAttribute("id")))  
		
        download_sequence_numberNode = downloadNode.getElementsByTagName("download_sequence_number")[0]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode.firstChild.data)) 
		
        download_sequence_numberNode2 = downloadNode.getElementsByTagName("download_sequence_number")[2]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode2.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode2.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode2.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode2.firstChild.data)) 
		
        if(other):
            transport_stream = downloadNode.getElementsByTagName("transport_stream")[0]
			
            transport_stream_idNode = transport_stream.getElementsByTagName("transport_stream_id")[0]
            original_network_idNode = transport_stream.getElementsByTagName("original_network_id")[0]	
            delivery_system_descriptorNode = transport_stream.getElementsByTagName("delivery_system_descriptor")[0]	
			
            transport_stream_actualNode = xmldoc.createElement('transport_stream')
            transport_stream_actualNode.setAttribute('attr', 'other')
            text = xmldoc.createTextNode('\n' + 2 * '\t')
            transport_stream_actualNode.appendChild(text)			
            transport_stream_actualNode.appendChild(transport_stream_idNode)
            text = xmldoc.createTextNode('\n' + 2 * '\t')
            transport_stream_actualNode.appendChild(text)			
            transport_stream_actualNode.appendChild(original_network_idNode)
            text = xmldoc.createTextNode('\n' + 2 * '\t')
            transport_stream_actualNode.appendChild(text)			
            transport_stream_actualNode.appendChild(delivery_system_descriptorNode)
            text = xmldoc.createTextNode('\n' + 2 * '\t')
            transport_stream_actualNode.appendChild(text)			

            transport_stream = downloadNode.getElementsByTagName("transport_stream")[1]			
			
            transport_stream_idNode = transport_stream.getElementsByTagName("transport_stream_id")[0]
            original_network_idNode = transport_stream.getElementsByTagName("original_network_id")[0]	
            delivery_system_descriptorNode = transport_stream.getElementsByTagName("delivery_system_descriptor")[0]	
		
            transport_stream_otherNode = xmldoc.createElement('transport_stream')
            transport_stream_otherNode.setAttribute('attr', 'actual')

            text = xmldoc.createTextNode('\n' + 2 * '\t')
            transport_stream_otherNode.appendChild(text)
            transport_stream_otherNode.appendChild(transport_stream_idNode)
            text = xmldoc.createTextNode('\n' + 2 * '\t')
            transport_stream_otherNode.appendChild(text)			
            transport_stream_otherNode.appendChild(original_network_idNode)
            text = xmldoc.createTextNode('\n' + 2 * '\t')
            transport_stream_otherNode.appendChild(text)			
            transport_stream_otherNode.appendChild(delivery_system_descriptorNode)				
            text = xmldoc.createTextNode('\n' + 2 * '\t')
            transport_stream_otherNode.appendChild(text)			

            newtransport = xmldoc.createElement("transport")
            text = xmldoc.createTextNode('\n')
            newtransport.appendChild(text)			
            newtransport.appendChild(transport_stream_actualNode)
            text = xmldoc.createTextNode('\n')
            newtransport.appendChild(text)			
            newtransport.appendChild(transport_stream_otherNode)				
            text = xmldoc.createTextNode('\n')
            newtransport.appendChild(text)	

            transport = downloadNode.getElementsByTagName("transport")[0]			
            downloadNode.removeChild(transport)
            
            text = xmldoc.createTextNode('\n')
            downloadNode.appendChild(text)	
            downloadNode.appendChild(newtransport)
            text = xmldoc.createTextNode('\n')
            downloadNode.appendChild(text)
		
        impl = minidom.getDOMImplementation()
        newdoc = impl.createDocument('\n', "LOADER_V5_HIGHLEVEL_DVT_CONFIG", None)  
        rootNode = newdoc.documentElement
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)
        rootNode.appendChild(downloadNode)
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)	
		
		#Save this XML to file
        result_file = open(outfilename, 'wb+')
        writer = codecs.lookup('utf-8')[3](result_file)
        newdoc.writexml(writer,addindent='  ',encoding='utf-8')
        writer.close() 	

def genStep10xmlFile(inputfilename,outfilename,samevar,invalidvar,samesubvar,invalidsubvar,subvarEq0,valid):
        xmldoc = minidom.parse(inputfilename)  

        downloadNode = xmldoc.getElementsByTagName("download")[0]  
        print("The name attribute of downloadNode: %s"%(downloadNode.getAttribute("id")))  
		
        download_sequence_numberNode = downloadNode.getElementsByTagName("download_sequence_number")[0]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode.firstChild.data)) 
		
        download_sequence_numberNode2 = downloadNode.getElementsByTagName("download_sequence_number")[2]  
        print("The attribute of download_sequence_number: %s"%(download_sequence_numberNode2.getAttribute("id")))  
        seq = int(eval(download_sequence_numberNode2.firstChild.data));
        print("The data of download_sequence_number: 0x%x"%(seq)) 		
        seq = seq + 1;
        download_sequence_numberNode2.firstChild.data = hex(seq)		
        print("The data of download_sequence_number: %s"%(download_sequence_numberNode2.firstChild.data)) 
		
        message_typeNode = downloadNode.getElementsByTagName("message_type")[0] 
        print("The data of message_type: %s"%(message_typeNode.firstChild.data)) 		
        message_typeNode.firstChild.data = "migration"		
	
        if(samevar):
            variantNode = downloadNode.getElementsByTagName("variant")[0]  
            newsubvariantNode = downloadNode.getElementsByTagName("new_subvariant")[0]  
			
            new_variantNode = downloadNode.getElementsByTagName("new_variant")[0]  
            new_variantNode.firstChild.data = variantNode.firstChild.data			
            print("The data of new_variant: %s"%(new_variantNode.firstChild.data))
			
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[0]  
            subvariantNode.firstChild.data = newsubvariantNode.firstChild.data				
            print("The data of subvariant : %s of %s "%(subvariantNode.firstChild.data, subvariantNode.getAttribute("id")))
			
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[2]  
            subvariantNode.firstChild.data = newsubvariantNode.firstChild.data				
            print("The data of subvariant : %s of %s "%(subvariantNode.firstChild.data, subvariantNode.getAttribute("id")))

        if(invalidvar):
            new_variantNode = downloadNode.getElementsByTagName("new_variant")[0]  
            new_variantNode.firstChild.data = "0xFFFF"			
            print("The data of subvariant: %s"%(new_variantNode.firstChild.data))		
		
            newsubvariantNode = downloadNode.getElementsByTagName("new_subvariant")[0]
			
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[0]  
            subvariantNode.firstChild.data = newsubvariantNode.firstChild.data				
            print("The data of subvariant: %s of %s"%(subvariantNode.firstChild.data,subvariantNode.getAttribute("id")))
			
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[2]  
            subvariantNode.firstChild.data = newsubvariantNode.firstChild.data				
            print("The data of subvariant: %s of %s"%(subvariantNode.firstChild.data,subvariantNode.getAttribute("id")))
			
            variantNode = downloadNode.getElementsByTagName("variant")[0]  
            variantNode.firstChild.data = new_variantNode.firstChild.data				
            print("The data of variant: %s of %s"%(variantNode.firstChild.data,variantNode.getAttribute("id")))
			
            variantNode = downloadNode.getElementsByTagName("variant")[2]  
            variantNode.firstChild.data = new_variantNode.firstChild.data				
            print("The data of variant: %s of %s"%(variantNode.firstChild.data,variantNode.getAttribute("id")))		
	
        if(samesubvar):
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[0]  
            newvariantNode = downloadNode.getElementsByTagName("new_variant")[0]  
			
            new_subvariantNode = downloadNode.getElementsByTagName("new_subvariant")[0]  
            new_subvariantNode.firstChild.data = subvariantNode.firstChild.data			
            print("The data of new_subvariant: %s"%(new_subvariantNode.firstChild.data))
			
            variantNode = downloadNode.getElementsByTagName("variant")[0]  
            variantNode.firstChild.data = newvariantNode.firstChild.data				
            print("The data of variant: %s of %s"%(variantNode.firstChild.data,variantNode.getAttribute("id")))
			
            variantNode = downloadNode.getElementsByTagName("variant")[2]  
            variantNode.firstChild.data = newvariantNode.firstChild.data				
            print("The data of variant: %s of %s"%(variantNode.firstChild.data,variantNode.getAttribute("id")))

        if(invalidsubvar):
            new_subvariantNode = downloadNode.getElementsByTagName("new_subvariant")[0]  
            new_subvariantNode.firstChild.data = "0xFFFF"			
            print("The data of subvariant: %s"%(new_subvariantNode.firstChild.data))		
		
            newvariantNode = downloadNode.getElementsByTagName("new_variant")[0]
			
            variantNode = downloadNode.getElementsByTagName("variant")[0]  
            variantNode.firstChild.data = newvariantNode.firstChild.data				
            print("The data of variant: %s of %s"%(variantNode.firstChild.data,variantNode.getAttribute("id")))
			
            variantNode = downloadNode.getElementsByTagName("variant")[2]  
            variantNode.firstChild.data = newvariantNode.firstChild.data				
            print("The data of variant: %s of %s"%(variantNode.firstChild.data,variantNode.getAttribute("id")))
			
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[0]  
            subvariantNode.firstChild.data = new_subvariantNode.firstChild.data				
            print("The data of subvariant: %s of %s"%(subvariantNode.firstChild.data,subvariantNode.getAttribute("id")))
			
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[2]  
            subvariantNode.firstChild.data = new_subvariantNode.firstChild.data				
            print("The data of subvariant: %s of %s"%(subvariantNode.firstChild.data,subvariantNode.getAttribute("id")))		

        if(subvarEq0):
            newvariantNode = downloadNode.getElementsByTagName("new_variant")[0]  	
		
            newsubvariantNode = downloadNode.getElementsByTagName("new_subvariant")[0]  
            newsubvariantNode.firstChild.data = "0x00"			
            print("The data of subvariant: %s"%(newsubvariantNode.firstChild.data))
			
            variantNode = downloadNode.getElementsByTagName("variant")[0]  
            variantNode.firstChild.data = newvariantNode.firstChild.data				
            print("The data of variant: %s of %s"%(variantNode.firstChild.data,variantNode.getAttribute("id")))
			
            variantNode = downloadNode.getElementsByTagName("variant")[2]  
            variantNode.firstChild.data = newvariantNode.firstChild.data				
            print("The data of variant: %s of %s"%(variantNode.firstChild.data,variantNode.getAttribute("id")))	

            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[0]  
            subvariantNode.firstChild.data = newsubvariantNode.firstChild.data				
            print("The data of subvariant: %s of %s"%(subvariantNode.firstChild.data,subvariantNode.getAttribute("id")))
			
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[2]  
            subvariantNode.firstChild.data = newsubvariantNode.firstChild.data				
            print("The data of subvariant: %s of %s"%(subvariantNode.firstChild.data,subvariantNode.getAttribute("id")))
			
        if(valid):
            newvariantNode = downloadNode.getElementsByTagName("new_variant")[0]		
            newsubvariantNode = downloadNode.getElementsByTagName("new_subvariant")[0]  
			
            variantNode = downloadNode.getElementsByTagName("variant")[0]  
            variantNode.firstChild.data = newvariantNode.firstChild.data				
            print("The data of variant: %s of %s"%(variantNode.firstChild.data,variantNode.getAttribute("id")))
			
            variantNode = downloadNode.getElementsByTagName("variant")[2]  
            variantNode.firstChild.data = newvariantNode.firstChild.data				
            print("The data of variant: %s of %s"%(variantNode.firstChild.data,variantNode.getAttribute("id")))	

            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[0]  
            subvariantNode.firstChild.data = newsubvariantNode.firstChild.data				
            print("The data of subvariant: %s of %s"%(subvariantNode.firstChild.data,subvariantNode.getAttribute("id")))
			
            subvariantNode = downloadNode.getElementsByTagName("sub_variant")[2]  
            subvariantNode.firstChild.data = newsubvariantNode.firstChild.data				
            print("The data of subvariant: %s of %s"%(subvariantNode.firstChild.data,subvariantNode.getAttribute("id")))		

		
        impl = minidom.getDOMImplementation()
        newdoc = impl.createDocument('\n', "LOADER_V5_HIGHLEVEL_DVT_CONFIG", None)  
        rootNode = newdoc.documentElement
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)
        rootNode.appendChild(downloadNode)
        text = xmldoc.createTextNode('\n')
        rootNode.appendChild(text)	
		
		#Save this XML to file
        result_file = open(outfilename, 'wb+')
        writer = codecs.lookup('utf-8')[3](result_file)
        newdoc.writexml(writer,addindent='  ',encoding='utf-8')
        writer.close() 	

def XMLSanityCheck(inputfilename):
        result = True
        xmldoc = minidom.parse(inputfilename)
		
        OUINode = xmldoc.getElementsByTagName("OUI")[0]
        if OUINode.firstChild.data == "XXXX":
            print("the data of OUI is XXXX of %s"%(OUINode.getAttribute("id")))  		
            print("please configure the parameter OUI of manufacturer_info")
            result = False

        OUINode = xmldoc.getElementsByTagName("OUI")[1]
        if OUINode.firstChild.data == "XXXX":		
            print("the data of OUI is XXXX of %s"%(OUINode.getAttribute("id")))  		
            print("please configure the parameter OUI of linkage_descriptor")		
            result = False
			
        OUINode = xmldoc.getElementsByTagName("OUI")[2]
        if OUINode.firstChild.data == "XXXX":		
            print("the data of OUI is XXXX of %s"%(OUINode.getAttribute("id")))  		
            print("please configure the parameter OUI of multilinkage_descriptor")
            result = False			

        OUINode = xmldoc.getElementsByTagName("OUI")[3]
        if OUINode.firstChild.data == "XXXX":		
            print("the data of OUI is XXXX of %s"%(OUINode.getAttribute("id")))  		
            print("please configure the parameter OUI of data_broadcast_id_descriptor")	
            result = False	

        linkage_descriptor_locationNode = xmldoc.getElementsByTagName("linkage_descriptor_location")[0]
        if linkage_descriptor_locationNode.firstChild.data == "XXXX":		
            print("the data of linkage_descriptor_location in option is XXXX ")  		
            print("please configure the parameter linkage_descriptor_location of option")	
            result = False

        filter_numberNode = xmldoc.getElementsByTagName("filter_number")[0]
        if filter_numberNode.firstChild.data == "XXXX":		
            print("the data of filter_number in ird_emm is XXXX ")  		
            print("please configure the parameter filter_number in ird_emm")	
            result = False

        new_variantNode = xmldoc.getElementsByTagName("new_variant")[0]
        if new_variantNode.firstChild.data == "XXXX":		
            print("the data of new_variant in ird_emm is XXXX ")  		
            print("please configure the parameter new_variant in ird_emm")	
            result = False			
			
        new_subvariantNode = xmldoc.getElementsByTagName("new_subvariant")[0]
        if new_subvariantNode.firstChild.data == "XXXX":		
            print("the data of new_subvariant in ird_emm is XXXX ")  		
            print("please configure the parameter new_subvariant in ird_emm")	
            result = False	

        ca_system_idNode = xmldoc.getElementsByTagName("ca_system_id")[0]
        if ca_system_idNode.firstChild.data == "XXXX":		
            print("the data of ca_system_id in ird_emm is XXXX ")  		
            print("please configure the parameter ca_system_id in ird_emm")	
            result = False	

        manufacturer_idNode = xmldoc.getElementsByTagName("manufacturer_id")[0]
        if manufacturer_idNode.firstChild.data == "XXXX":
            print("the data of manufacturer_id is XXXX of %s"%(manufacturer_idNode.getAttribute("id")))  		
            print("please configure the parameter manufacturer_id")
            result = False

        manufacturer_idNode = xmldoc.getElementsByTagName("manufacturer_id")[1]
        if manufacturer_idNode.firstChild.data == "XXXX":
            print("the data of manufacturer_id is XXXX of %s"%(manufacturer_idNode.getAttribute("id")))  		
            print("please configure the parameter manufacturer_id")
            result = False

        manufacturer_idNode = xmldoc.getElementsByTagName("manufacturer_id")[2]
        if manufacturer_idNode.firstChild.data == "XXXX":
            print("the data of manufacturer_id is XXXX of %s"%(manufacturer_idNode.getAttribute("id")))  		
            print("please configure the parameter manufacturer_id")
            result = False
	
        hardware_versionNode = xmldoc.getElementsByTagName("hardware_version")[0]
        if hardware_versionNode.firstChild.data == "XXXX":
            print("the data of hardware_version is XXXX of %s"%(hardware_versionNode.getAttribute("id")))  		
            print("please configure the parameter hardware_version")
            result = False

        hardware_versionNode = xmldoc.getElementsByTagName("hardware_version")[1]
        if hardware_versionNode.firstChild.data == "XXXX":
            print("the data of hardware_version is XXXX of %s"%(hardware_versionNode.getAttribute("id")))  		
            print("please configure the parameter hardware_version")
            result = False			

        hardware_versionNode = xmldoc.getElementsByTagName("hardware_version")[2]
        if hardware_versionNode.firstChild.data == "XXXX":
            print("the data of hardware_version is XXXX of %s"%(hardware_versionNode.getAttribute("id")))  		
            print("please configure the parameter hardware_version")
            result = False			

        variantNode = xmldoc.getElementsByTagName("variant")[0]
        if variantNode.firstChild.data == "XXXX":
            print("the data of variant is XXXX of %s"%(variantNode.getAttribute("id")))  		
            print("please configure the parameter variant")
            result = False

        variantNode = xmldoc.getElementsByTagName("variant")[1]
        if variantNode.firstChild.data == "XXXX":
            print("the data of variant is XXXX of %s"%(variantNode.getAttribute("id")))  		
            print("please configure the parameter variant")
            result = False			

        variantNode = xmldoc.getElementsByTagName("variant")[2]
        if variantNode.firstChild.data == "XXXX":
            print("the data of variant is XXXX of %s"%(variantNode.getAttribute("id")))  		
            print("please configure the parameter variant")
            result = False	

        sub_variantNode = xmldoc.getElementsByTagName("sub_variant")[0]
        if sub_variantNode.firstChild.data == "XXXX":
            print("the data of sub_variant is XXXX of %s"%(sub_variantNode.getAttribute("id")))  		
            print("please configure the parameter sub_variant")
            result = False

        sub_variantNode = xmldoc.getElementsByTagName("sub_variant")[1]
        if sub_variantNode.firstChild.data == "XXXX":
            print("the data of sub_variant is XXXX of %s"%(sub_variantNode.getAttribute("id")))  		
            print("please configure the parameter sub_variant")
            result = False			

        sub_variantNode = xmldoc.getElementsByTagName("sub_variant")[2]
        if sub_variantNode.firstChild.data == "XXXX":
            print("the data of sub_variant is XXXX of %s"%(sub_variantNode.getAttribute("id")))  		
            print("please configure the parameter sub_variant")
            result = False					

        download_sequence_numberNode = xmldoc.getElementsByTagName("download_sequence_number")[0]
        if download_sequence_numberNode.firstChild.data == "XXXX":
            print("the data of download_sequence_number is XXXX of %s"%(download_sequence_numberNode.getAttribute("id")))  		
            print("please configure the parameter download_sequence_number")
            result = False

        download_sequence_numberNode = xmldoc.getElementsByTagName("download_sequence_number")[1]
        if download_sequence_numberNode.firstChild.data == "XXXX":
            print("the data of download_sequence_number is XXXX of %s"%(download_sequence_numberNode.getAttribute("id")))  		
            print("please configure the parameter download_sequence_number")
            result = False			

        download_sequence_numberNode = xmldoc.getElementsByTagName("download_sequence_number")[2]
        if download_sequence_numberNode.firstChild.data == "XXXX":
            print("the data of download_sequence_number is XXXX of %s"%(download_sequence_numberNode.getAttribute("id")))  		
            print("please configure the parameter download_sequence_number")
            result = False				
			
        network_typeNode = xmldoc.getElementsByTagName("network_type")[0]
        if network_typeNode.firstChild.data == "XXXX":
            print("the data of network_type is XXXX of %s"%("actual"))  		
            print("please configure the parameter network_type in delivery_system_descriptor of transport_stream")
            result = False	

        network_typeNode = xmldoc.getElementsByTagName("network_type")[1]
        if network_typeNode.firstChild.data == "XXXX":
            print("the data of network_type is XXXX of %s"%("other"))  		
            print("please configure the parameter network_type in delivery_system_descriptor of transport_stream")
            result = False				
			
        return result	
		
if __name__ == '__main__':
    result = True
    inputfilename = "dvt.xml"
	
    result = XMLSanityCheck(inputfilename)
	
    if result == True:
        print("-------------Step04_01xml------------------------------")		
        genStep04xmlFile(inputfilename,"input/Step04_01.xml","0x01","on")
        print("-------------Step04_02xml------------------------------")		
        genStep04xmlFile(inputfilename,"input/Step04_02.xml","0x02","on")
        print("-------------Step04_03xml------------------------------")			
        genStep04xmlFile(inputfilename,"input/Step04_03.xml","0x02","off")
        print("-------------Step04_04xml------------------------------")		
        genStep04xmlFile(inputfilename,"input/Step04_04.xml","0x01","off")

        print("-------------Step05_01xml------------------------------")		
        genStep05xmlFile(inputfilename,"input/Step05.xml","0x00","off")		

        print("-------------Step06_01xml------------------------------")				
        genStep06xmlFile(inputfilename,"input/Step06_01.xml",True,False,False,False,False,False,False,False,0,False,0,"off")		
        print("-------------Step06_02xml------------------------------")		
        genStep06xmlFile(inputfilename,"input/Step06_02.xml",False,True,False,False,False,False,False,False,0,False,0,"off")	
        print("-------------Step06_03xml------------------------------")
        genStep06xmlFile(inputfilename,"input/Step06_03.xml",False,False,True,False,False,False,False,False,0,False,0,"off")	
        print("-------------Step06_04xml------------------------------")
        genStep06xmlFile(inputfilename,"input/Step06_04.xml",False,False,False,True,False,False,False,False,0,False,0,"off")	
        print("-------------Step06_05xml------------------------------")
        genStep06xmlFile(inputfilename,"input/Step06_05.xml",False,False,False,False,True,False,False,False,0,False,0,"off")	
        print("-------------Step06_06xml------------------------------")
        genStep06xmlFile(inputfilename,"input/Step06_06.xml",False,False,False,False,False,True,False,False,0,False,0,"off")			
        print("-------------Step06_07xml------------------------------")
        genStep06xmlFile(inputfilename,"input/Step06_07.xml",False,False,False,False,False,False,True,False,0,False,0,"off")			
        print("-------------Step06_08.xml------------------------------")
        genStep06xmlFile(inputfilename,"input/Step06_08.xml",False,False,False,False,False,False,False,True,0,False,0,"off")			
        print("-------------Step06_09.xml------------------------------")
        genStep06xmlFile(inputfilename,"input/Step06_09.xml",False,False,False,False,False,False,False,True,-1,False,0,"off")				
        print("-------------Step06_10.xml------------------------------")
        genStep06xmlFile(inputfilename,"input/Step06_10.xml",False,False,False,False,False,False,False,True,100,False,0,"off")	
        print("-------------Step06_11.xml------------------------------")
        genStep06xmlFile(inputfilename,"input/Step06_11.xml",False,False,False,False,False,False,False,True,1,False,0,"off")			

        print("-------------Step07.xml------------------------------")		
        genStep07xmlFile(inputfilename,"input/Step07.xml")				

        print("-------------Step08_01xml------------------------------")				
        genStep06xmlFile(inputfilename,"input/Step08.xml",True,False,False,False,False,False,False,False,0,False,2,"off")		

        print("-------------Step09_ts01.xml------------------------------")
        genStep09xmlFile(inputfilename,"input/Step09_ts01.xml",False)	
        print("-------------Step09_ts02.xml------------------------------")
        genStep09xmlFile(inputfilename,"input/Step09_ts02.xml",True)	
		
