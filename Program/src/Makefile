CC = gcc
output = interpreter

main:			
		$(CC) -o Library.o -c Library.c 
		$(CC) -std=gnu99 -o $(output) interpreter.c ArduinoDriver.c Library.a  

clean:
		rm Library.o
		rm $(output)




