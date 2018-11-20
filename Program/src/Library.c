#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "Library.h"
#include "ArduinoDriverLibrary.h"
#define BUFFER_LENGTH 256
int boardDeviceFunction(int boardResolution) // this method is in charge of tell the device which resolution is going to be used
{
	char boardResChar[20]; //this is the resolution of the board
	char boardMessage[16];  // the message to the arduino is going to be in this variable
	char* arduinoResponseMesg; // the arduino is going to response, so there is going to be his message
	sprintf(boardResChar, "%d",boardResolution); // parsing the resolution to decimal
	strcpy(boardMessage, "Board:");
	strcat(boardMessage, boardResChar);// creating the message
	printf("-> Device response new board processed: -b %d\n",boardResolution); 
	sendMessageArduino (boardMessage); //Send this message to the arduino
	arduinoResponseMesg = readMessageArduino(); //Read the message send from the arduino
	if(strcmp(arduinoResponseMesg, "L") == 0){ // send a char saying it's done
    	printf("All right \n");
    	return 1; 
    }
    else{
    	printf("ERROR\n");
    	return 0; 
    }
}
int moveDeviceFunction(int posInit, int posFin, int nextMove) // the method's function is to communicate to the driver the movements to do
{
	printf("creating message to the device\n");
	char initPos[20];  // the init position number
	char endPos[20];  // the final position number
	char nextMovement[20];  // the next move to say to the driver
	char* arduinoResponseMesg; // the message response 
	sprintf(initPos, "%d",posInit); // casting to dec
	sprintf(endPos, "%d",posFin); // casting to dec
	sprintf(nextMovement, "%d",nextMove); // casting to dec
	char coma1[16]; // this part of the code is going to be for the creation of the message to the arduino
  	char coma2[16]; 
  	strcpy(coma1, ",");
  	strcpy(coma2, ",");
  	strcat(nextMovement, coma1);
  	strcat(nextMovement, initPos);
  	strcat(nextMovement, coma2);
  	strcat(nextMovement, endPos);
	sendMessageArduino (nextMovement); //Send this message to the arduino
	while(strcmp(readMessageArduino(), "L") != 0){ // here is waiting for the response of the arduino
	}
    arduinoResponseMesg = readMessageArduino(); //Read the message send from the arduino
    if(strcmp(arduinoResponseMesg, "L") == 0){ //the char is send if everything is all right
    	printf("All right\n");
    	return 1; 
    }
    else{
    	printf("ERROR\n");
    	return 0; 
    }
}