#!/bin/sh

PLATFORM=ali3721_tds

#ARTPAL_UI [HD SD]
UIStyleMode=HD

#ARTPAL_CA [VerimatrixCA  IrdetoCA CastpalCA ConaxCA]
ARTPAL_CA=IrdetoCA

ARCH=mips
CHIP_DIR=Ali
ARTPAL_CROSS_COMPILE=/opt/mips-sde-elf-4.7.3/bin/mips-sde-elf-
TOOLCHAINS=/opt/mips-sde-elf-4.7.3/bin/

ARTPAL_PROJECT=${PWD##*/}
PRODUCT_HOME=`pwd | sed 's/Bin//g'`

cp ./makefile ../../ -rf

cd ../../
chmod -R 777 *
TRUNK_HOME=`pwd | sed 's/Bin//g'`
PATH=${TOOLCHAINS}:${TRUNK_HOME}/Bin:$PATH
PLATFORM_DIR=${TRUNK_HOME}/Porting/${CHIP_DIR}/${PLATFORM}
PLUGIN_PATH=${PRODUCT_HOME}/lib/linux/${BUILD_TYPE}/plugin_ext
BUILD_TYPE=debug
#BUILD_TYPE=release

chmod -Rf 777 ${TRUNK_HOME}/Bin
chmod u+x ${TRUNK_HOME}/Bin/exportSvnInfo

PRO_INCLUDE=${PRODUCT_HOME}

export PATH
export PRO_INCLUDE
export PRODUCT_HOME
export TRUNK_HOME
export PLATFORM
export ARTPAL_CROSS_COMPILE
export ARCH
export CHIP_DIR
export PLATFORM_DIR
export BUILD_TYPE
export ARTPAL_CA
export ARTPAL_UI=${UIStyleMode}

echo "---------------------- code config ----------------------------"
echo "$PRODUCT_HOME"
echo "$ARTPAL_CROSS_COMPILE"
echo "$TOOLCHAINS"
echo "$TRUNK_HOME"
echo "Platform     $PLATFORM"
echo "Project:     $ARTPAL_PROJECT"
echo "CA Type:     $ARTPAL_CA"
echo "UI Type:     $ARTPAL_UI"
echo "---------------------------------------------------------------"
