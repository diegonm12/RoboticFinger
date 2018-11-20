#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "ArduinoDriverLibrary.h"
#define BUFFER_LENGTH 256  //The buffer length

int writeConfirm, fd;   
ssize_t rd; //size read message send from the arduino
char stringReceived[BUFFER_LENGTH]; //Buffer of the message received

char* readMessageArduino() // thisfunction is going to send the instructions for the arduino
{
	fd = open("/dev/RoboticFinger0", O_RDWR); // the file created  by the driver is in that directory, and is where we are going to read the messages form arduino
	printf("Reading message send from the Arduino.\n"); // a print to user to show whats is read to the device
	rd = read(fd,stringReceived,50); 	// the message is read in the file
	while(rd = read(fd,stringReceived,50)){
		if(strcmp(stringReceived, "L") == 0){
			break;
		}
	}
	close(fd);
	printf("The message received from the Arduino is: [%s].\n", stringReceived);
	return stringReceived;
}

int sendMessageArduino (char stringToSend[BUFFER_LENGTH]) // thisfunction is going to send the instructions for the arduino
{
	fd = open("/dev/RoboticFinger0", O_RDWR); // the file created  by the driver is in that directory, and is where we are going to write the messages
	printf("Writing message to the device [%s].\n", stringToSend);	// a print to user to show whats is sended to the device
	writeConfirm = write(fd, stringToSend, strlen(stringToSend));	// the message is write in the file
	if (writeConfirm < 0){	// an error in we have no response
		perror("Failed to write the message to the device.");
		return errno;
	}
	close(fd);
	return 0;
}
