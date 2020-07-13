
#!/bin/sh

echo "Please seletct the platform:"
echo "1) msd5029   2)msd5s37 3)msd7s35 4)msd7xxx_linux"
read -p "Enter select: " sel 
case ${sel} in
	1)
	PLATFORM=msd5029
	ARCH=mips
	CHIP_DIR=Mstar
	ARTPAL_CROSS_COMPILE=/opt/ecos/mipsisa32-elf-3.4.4/bin/mipsisa32-elf-
	TOOLCHAINS=/opt/mips-4.3/bin/:/opt/ecos/mipsisa32-elf-3.4.4/bin/
	echo "$PLATFORM"
	;;
	2)
	PLATFORM=msd5s37
	ARCH=mips
	CHIP_DIR=Mstar
	ARTPAL_CROSS_COMPILE=/opt/ecos/mipsisa32-elf-3.4.4/bin/mipsisa32-elf-
	TOOLCHAINS=/opt/mips-4.3/bin/:/opt/ecos/mipsisa32-elf-3.4.4/bin/
	echo "$PLATFORM"
	;;
	3)
	PLATFORM=msd7s35
	ARCH=mips
	CHIP_DIR=Mstar
	ARTPAL_CROSS_COMPILE=/opt/ecos/mipsisa32-elf-3.4.4/bin/mipsisa32-elf-
	TOOLCHAINS=/opt/mips-4.3/bin/:/opt/ecos/mipsisa32-elf-3.4.4/bin/
	echo "$PLATFORM"
	;;
	4)
	PLATFORM=msd7xxx_linux
	ARCH=mips
	CHIP_DIR=Mstar
	ARTPAL_CROSS_COMPILE=/opt/mips-4.3/bin/mips-linux-gnu-
	TOOLCHAINS=/opt/mips-4.3/bin/:/opt/ecos/mipsisa32-elf-3.4.4/bin/
	echo "$PLATFORM"
	;;
esac


TRUNK_HOME=`pwd | sed 's/Bin//g'`
PATH=${TOOLCHAINS}:${TRUNK_HOME}/Bin:$PATH
PLATFORM_DIR=${TRUNK_HOME}/Porting/${CHIP_DIR}/${PLATFORM}
BUILD_TYPE=debug
chmod u+x ${TRUNK_HOME}/Bin/exportSvnInfo

source ${PLATFORM_DIR}/setup.sh

export PATH
export TRUNK_HOME
export PLATFORM
export ARTPAL_CROSS_COMPILE
export ARCH
export CHIP_DIR
export PLATFORM_DIR
export BUILD_TYPE


	