#!/bin/bash

PATH_ROOT=../../../../../
cd $PATH_ROOT
ROOTPATH=$(pwd)

echo LOCAL_BASE = $ROOTPATH
echo LOCAL_BASE = $ROOTPATH > path.def

echo " " >> path.def
echo BASE_DIR = \$\{LOCAL_BASE\} >> path.def
echo INC_DIR = \$\{BASE_DIR\}/inc >> path.def
echo LIB_DIR = \$\{BASE_DIR\}/obj >> path.def
echo REL_DIR = \$\{BASE_DIR\}/rel >> path.def

echo DDK_DIR = \$\{BASE_DIR\}/ddk >> path.def
echo SDK_DIR = \$\{BASE_DIR\}/sdk >> path.def
echo PLUGINDDK_DIR = \$\{BASE_DIR}/ddk/plugin >> path.def
echo PLUGINEXT_DIR = \$\{BASE_DIR}/ddk/plugin_ext >> path.def
echo BLSDK_DIR = \$\{BASE_DIR\}/sdk/blsdk >> path.def
echo DDK_BLSDK_DIR = \$\{BASE_DIR\}/ddk/blsdk >> path.def
echo MH5_INC_DIR = \$\{BASE_DIR\}/src/udi/lib_mheg5_v20/inc >> path.def

##############################
## ACCESS: 2013.01.21 for DLNA
##############################
echo DDK_DLNA_DIR = \$\{BASE_DIR\}/ddk/dlna >> path.def
echo INC_DLNA_DIR = \$\{BASE_DIR\}/inc/dlna >> path.def

cp path.def src/
rm -f path.def
