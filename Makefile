led.ihx: led.c
	sdcc -mstm8 --std-c99 led.c

upload: led.ihx
	sudo stm8flash -c stlinkv2 -p stm8l152c6 -w led.ihx

