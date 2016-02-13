all:
	gcc -o ev3 main.c ev3_motor.c serial.c
	./ev3
