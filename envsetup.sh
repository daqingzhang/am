#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$AM_DIR_TOP

export AM_DIR_TOP=$(pwd)
export AM_APP_PATH=$AM_DIR_TOP/app
export AM_DEV_PATH=$AM_DIR_TOP/device
export AM_DRV_PATH=$AM_DIR_TOP/drivers
export AM_SYS_PATH=$AM_DIR_TOP/system
export AM_OUT_PATH=$AM_DIR_TOP/out
export AM_ARC_PATH=$AM_DIR_TOP/arch/arm/armv7/st/stm32f10x

envprint()
{
	echo ""
	echo "AM_APP_PATH = $AM_APP_PATH"
	echo "AM_DEV_PATH = $AM_DEV_PATH"
	echo "AM_DRV_PATH = $AM_DRV_PATH"
	echo "AM_SYS_PATH = $AM_SYS_PATH"
	echo "AM_OUT_PATH = $AM_OUT_PATH"
	echo "AM_ARC_PATH = $AM_ARC_PATH"
	echo ""
}

cdarch()
{
	cd ${AM_ARC_PATH}
}

cdsys()
{
	cd ${AM_SYS_PATH}
}

cddrv()
{
	cd ${AM_DRV_PATH}
}

cddev()
{
	cd ${AM_DEV_PATH}
}

cdapp()
{
	cd ${AM_APP_PATH}
}

croot()
{
	cd ${AM_DIR_TOP}
}

cdout()
{
	cd ${AM_OUT_PATH}
}

ocdstart()
{
	openocd -f scripts/jlink.cfg -f scripts/stm32f1x.cfg
}

envprint
