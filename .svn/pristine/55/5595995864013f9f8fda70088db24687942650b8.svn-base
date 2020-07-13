#!/bin/bash
# How to use this script
#
# For Full source code, run
# ./<This_Script>.sh    
#
# For QT/Customer code(After merge packages)
# ./<This_Script>.sh released
#
if [ "$BASH_SOURCE"x = x ]; then
	FILENAME=$0
else
	FILENAME=$BASH_SOURCE
fi
echo "AUI_BUILD_STEP: $FILENAME"

SCRIPT_DIR=`dirname $FILENAME`
cd ${SCRIPT_DIR}

# Initialize the directory
PROJECT_APP=$(pwd)

cd ../sabbat_dual/
PROJECT_APP_SABBAT=$(pwd)

cd ../../../../..
PROJECT_ROOT=$(pwd)

cd ${PROJECT_APP}

# Set the compiler.def file name
COMPILER_DEF=${PROJECT_APP}/"compiler_3505.def"
COMPILER_DEF_SABBAT=${PROJECT_APP_SABBAT}/"compiler_3505.def"

# The help information
print_help()
{
	echo "How to run this script"
	echo "|"
	echo "|- For ALi internal, full source code:"
	echo "|    $0 full"
	echo "|"
	echo "|- For QT/Customer, after merge all packages:"
	echo "|    $0"
	echo ""
}

# This is helper function, to check previous command result.
# If the result is FAIL, it will exit the compilation.
check_previous_return_val()
{
	TMP_VAL=$?
	#echo "Previous return value is "$TMP_VAL
	if [ $TMP_VAL -eq 0 ] ;
	then
		echo "  OK! continue"
	else
		echo "  Previous command execute return FAIL, exit the compilation"
		exit 1
	fi
}

# Helper function, use to enable/disable options in compiler.def
option_select()
{
	operation=$1
	option=$2
	filename=$3

	if [ "$operation" == "enable" ]; then
		command_str="sed -i \"s/^#${option}/${option}/\" ${filename}"
	else
		command_str="sed -i \"s/^${option}/#${option}/\" ${filename}"
	fi

	echo "${command_str}"
	eval "${command_str}"

	check_previous_return_val
}

# This function use to configure the project, enable features etc.
build_main_config()
{
	echo "AUI_BUILD_STEP: build_main_config"
	# Go to the correct directory
	cd ${PROJECT_APP}

	# First select the correct demoboard
	option_select "enable" "_BOARD_M3712L_01V01_ = 1" ${COMPILER_DEF}
	#    Disable all other demoboards
	option_select "disable" "_BOARD_M3521_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_M3526_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_M3626_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_M3627_02V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_M3727_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_M3727_02V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_M3527_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_M3712_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_M3716L_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_M3216L_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_S3521_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_S3527_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_M3529_01V01_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BOARD_S3529_01V01_ = 1" ${COMPILER_DEF}


	# Then select the correct AS and enable it's options
	option_select "enable" "_GEN_CA_ENABLE_ = 1" ${COMPILER_DEF}

	# Now ensure all AS options are disabled
	option_select "disable" "_C0200A_CA_ENABLE_ = 1" ${COMPILER_DEF}
	option_select "disable" "_C0200A_CA_DAL_TEST_ = 1" ${COMPILER_DEF}
	option_select "disable" "_C0200A_SSD_VERIFY_DISABLE_ = 1" ${COMPILER_DEF}
	option_select "disable" "_CAS9_CA_ENABLE_ = 1" ${COMPILER_DEF}
	option_select "disable" "_CAS9_SMC_DEBUG_ = 1" ${COMPILER_DEF}
	option_select "disable" "_CAS9_VSC_ENABLE_ = 1" ${COMPILER_DEF}
	option_select "disable" "_CAS9_VSC_API_ENABLE_ = 1" ${COMPILER_DEF}
	option_select "disable" "_CAS9_VSC_RAP_ENABLE_ = 1" ${COMPILER_DEF}
	option_select "disable" "_CAS9_SC_UPG_ = 1" ${COMPILER_DEF}
	option_select "disable" "_CAS7_CA_ENABLE_ = 1" ${COMPILER_DEF}
	option_select "disable" "_CAS7_CA_ENABLE_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BC_CA_ENABLE_ = 1" ${COMPILER_DEF}
	option_select "disable" "_BC_CA_STD_ENABLE_ = 1" ${COMPILER_DEF}


	# If there are other option need enable/disable, do now
	option_select "enable" "_AUI_=1" ${COMPILER_DEF}
	option_select "enable" "_AUI_TEST_=1" ${COMPILER_DEF}

	# Default use encrypted bootloader
	option_select "disable" "_ENABLE_BL_ENCRYPTED_ = 1" ${COMPILER_DEF}
	option_select "enable" "_BOOT_LOGO_ENABLE_ = 1" ${COMPILER_DEF}
	option_select "enable" "_DD_SUPPORT = 1" ${COMPILER_DEF}

	# Now use the config
	make path config_3505
	check_previous_return_val

}

# Only Advance security projects need this step
build_signature_firmware()
{
	echo "AUI_BUILD_STEP: build_signature_firmware"
	# Go to the correct directory: 3505 only generate firmware at aui_demo, and signature
	cd ${PROJECT_APP}

	make bin
	check_previous_return_val
}

# Backup firmware to other name
backup_firmware()
{
	echo "AUI_BUILD_STEP: backup_firmware"
	# Go to the correct directory
	cd ${PROJECT_ROOT}

	mkdir -p ${PROJECT_ROOT}/images
	check_previous_return_val

	cp ${PROJECT_ROOT}/obj/product_sabbat_dual.abs ${PROJECT_ROOT}/images/product_sabbat_dual_aui_m3712L_gen.abs
	check_previous_return_val
}


# This function use to build SEE CPU code
build_see()
{
	echo "AUI_BUILD_STEP: build_see"
	# Go to the correct directory
	cd ${PROJECT_ROOT}/src/see/m36f

	make path config_3505
	check_previous_return_val

	make new
	check_previous_return_val

	make all
	check_previous_return_val
}

# Sync code from sabbat_dual for ALi internal.
# Before compilation main code
build_sync_code()
{
	echo "AUI_BUILD_STEP: build_sync_code"
	# Go to the correct directory
	cd ${PROJECT_APP}

	make path aui_sync_3505
	check_previous_return_val
}

# For ALi Internal, build driver and OS library
build_sdk()
{
	echo "AUI_BUILD_STEP: build_sdk"
	# Go to the correct directory
	cd ${PROJECT_APP}

	make sdk_clean	
	check_previous_return_val

	make sdk
	check_previous_return_val
}

# Build AUI library
build_aui()
{
	echo "AUI_BUILD_STEP: build_aui"
	# Go to the correct directory
	cd ${PROJECT_ROOT}/aui

	make clean
	check_previous_return_val

	make all
	check_previous_return_val
}

# Build HLD, middle layer, and application
build_middle_and_app()
{
	echo "AUI_BUILD_STEP: build_middle_and_app"
	# Go to the correct directory
	cd ${PROJECT_APP}
	
	make new
	check_previous_return_val

	make ddk
	check_previous_return_val
	
	make all
	check_previous_return_val
}




# The main function
main() 
{
	# Get the parameter first
	is_fullcode=$1
	
	if [ "$is_fullcode" == "no" ]; then
		echo "Released code, no need to build SEE"
	else
		echo "Full source code, build SEE first"
		build_see
		check_previous_return_val

		# Before compile MAIN code, we have to sync aui board setting and project setting from sabbat_dual
		build_sync_code
		check_previous_return_val
	fi

	# Now we have to configure MAIN code
	build_main_config
	check_previous_return_val

	# Build driver code
	if [ "$is_fullcode" == "no" ]; then
		echo "Released code, no need to build SDK"
	else
		echo "Full source code, build SDK"
		build_sdk
		check_previous_return_val
	fi

	# Build AUI code
	build_aui
	check_previous_return_val

	# Build Middle layer code and application code
	build_middle_and_app
	check_previous_return_val

	# If it is advance security project, need build the signature firmware
	build_signature_firmware
	check_previous_return_val

	# OK, backup firmware now
	backup_firmware
	check_previous_return_val

	echo "All finished"
}



# Get the input parameter
# maybe it is empty(released code case)
fullcode=$1
is_fullcode=""

if [ "$fullcode" == "full" ];
then
	is_fullcode="yes"
else
	is_fullcode="no"
	if [ "$fullcode" != "" ];
	then
		print_help
		exit 1
	fi
fi

# Start the compilation
main ${is_fullcode}
