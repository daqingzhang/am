
start_ocd_server_stm()
{
	echo "Start ocd server for STM ..."
	openocd -f ./scripts/ocd/jlink.cfg -f ./scripts/ocd/stm32f1x.cfg -d -l ocd.log
}

start_ocd_server_stm
