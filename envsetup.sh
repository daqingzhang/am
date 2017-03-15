chip_name=stm32f10x
os=FreeRTOS

export AM_DIR_TOP=$(pwd)
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$AM_DIR_TOP
export AM_ARCH_CPU_PATH=$AM_DIR_TOP/arch/arm/$chip_name/cpu
export AM_ARCH_LIB_PATH=$AM_DIR_TOP/arch/arm/$chip_name/lib
export AM_APP_PATH=$AM_DIR_TOP/application
export AM_DEV_PATH=$AM_DIR_TOP/device/$chip_name
export AM_DRV_PATH=$AM_DIR_TOP/drivers/$chip_name
export AM_SYS_PATH=$AM_DIR_TOP/system/$os

envprint()
{
	echo ""
	echo "AM_DIR_TOP = $AM_DIR_TOP"
	echo "LD_LIBRARY_PATH = $LD_LIBRARY_PATH"
	echo "AM_ARCH_CPU_PATH = $AM_ARCH_CPU_PATH"
	echo "AM_ARCH_LIB_PATH = $AM_ARCH_LIB_PATH"
	echo "AM_APP_PATH = $AM_APP_PATH"
	echo "AM_DEV_PATH = $AM_DEV_PATH"
	echo "AM_DRV_PATH = $AM_DRV_PATH"
	echo "AM_SYS_PATH = $AM_SYS_PATH"
	echo ""
}

cdsys()
{
	cd $AM_SYS_PATH
}

cddrv()
{
	cd $AM_DRV_PATH
}

cddev()
{
	cd $AM_DEV_PATH
}

cdapp()
{
	cd $AM_APP_PATH
}

cdcpu()
{
	cd $AM_ARCH_CPU_PATH
}

cdlib()
{
	cd $AM_ARCH_LIB_PATH
}

croot()
{
	cd $AM_DIR_TOP
}

envprint
