onboard=533F6F063F3F494942290467
ext=343F76065250343837260643

led.ihx: led.c
	sdcc -mstm8 --std-c99 led.c

upload: led.ihx
	sudo stm8flash -S $(onboard) -c stlinkv2 -p stm8l152c6 -w led.ihx

