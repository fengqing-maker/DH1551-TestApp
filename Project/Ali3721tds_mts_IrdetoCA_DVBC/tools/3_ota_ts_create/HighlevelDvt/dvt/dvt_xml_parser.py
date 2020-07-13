#!/usr/bin/env python

#
# Created on Oct 27, 2011
#
# @author: ethan.li
#

import xml.dom.minidom

from dvt_base import *


class DvtXmlParser(object):
    
    def __init__(self, fullpath = ''):
        """Load XML source file and parse with xml.dom.minidom"""
        self.__result = {}    # a dictionary containing the parse result
        self.__fullpath = fullpath
        self.setSource(fullpath)
        
    def setSource(self, fullpath):
        dvtdbg("Load XML file: \"%s\" started..." % self.__fullpath)
        try:
            xmldoc = xml.dom.minidom.parse(fullpath)  # "input/dvt.xml"
            self.__root = xmldoc.getElementsByTagName('LOADER_V5_HIGHLEVEL_DVT_CONFIG')[0] # only the 1st item is allowed
        except:
            raise dvtError("file \"%s\" is not a valid XML file!" %fullpath)
        dvtdbg("Load XML file: \"%s\" finished."  %self.__fullpath)
        
    def __getNodes(self, root, tag):
        if root is None:
            elem = self.__root
        else:
            elem = root
        nodes = elem.getElementsByTagName(tag)
        # dvtdbg(nodes.toxml())
        return nodes
    
    def getTagElements(self, root, tag, attrn = None, attrv = None):
        """Get the elements named 'tag' within XML DOM element 'root'"""
        elements = []
        nodes = self.__getNodes(root, tag)
        if nodes is None:
            dvtError("Cannot get the target node from the XML!!!")
        else:
            for node in nodes:
                if node.nodeType == node.ELEMENT_NODE:
                    if node.hasChildNodes():    # if the node is empty, dismiss it.
                        if ((attrn is None) or 
                            (attrn is not None and node.getAttribute(attrn) == attrv)):
                            elements.append(node)
                dvtdbg("[element] (root -> %s, tag -> %s %s=\"%s\", elem -> %s)" 
                       % (node, tag, attrn, attrv, elements))    
        return elements
    
    def getTagText(self, root, tag, attrn = None, attrv = None):
        """Get the text from XML DOM element 'elem'"""
        rc = []
        nodes = self.__getNodes(root, tag)
        if nodes is None:
            dvtError("Cannot get the target node from the XML!!!")
        else:
            for node in nodes[0].childNodes:
                dvtdbg("node = %s, node_type: %s, node_data: %s" 
                       % (node, node.nodeType, node.nodeValue))
                if node.nodeType == node.TEXT_NODE:
                    if ((attrn is None) 
                        or (attrn is not None and node.getAttribute(attrn) == attrv)):
                        rc.append(node.data)
            dvtdbg("[text] (root -> %s, tag -> %s %s=\"%s\", value -> %s)" 
                   % (node, tag, attrn, attrv, rc))
        return ''.join(rc)
    
    def getParsedResult(self):
        return self.__result


