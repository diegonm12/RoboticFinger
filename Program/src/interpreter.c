#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include"Library.h"
int interpretMovement(char** tokens){ // this function get the information located inthe file to define the resolution of the screen used
	int checkerVariable=0; // this is going to be returned to check if the checkerVariable of the method is OK
	int posX = -1; // the position in x to move
	int posY = -1; // the position in y to move
	int sec = -1; // the seconds quantity for the push
	int nextMove = -1; // have the next move variable
	for (int i = 0; tokens[i]!=NULL; i++){  // read the file to do the movements in the motor		
		if (tokens[i+1]!=NULL){	// while the next is not null
			char *entry = tokens[i];
			if (strcmp( entry, "-x")==0){  		// the variable x to handle the position		  
			    posX = atoi(tokens[i + 1]);    	// assign the variable above according to the file information		
			}
			if (strcmp( entry, "-s")==0){  		// seconds flag		  
			    sec = atoi(tokens[i + 1]);    		// get the seconds number		
			}
			if (strcmp( entry, "-y")==0){  		// the variable y to handle the position		  
			    posY = atoi(tokens[i + 1]);    	// assign the variable above according to the file information			
			}
			if (strcmp( entry, "-t")==0){  			// t of type of the movement	  				 
			    char *action =tokens[i + 1];  		    
			    if (strncmp( action, "move",4)==0){ // just move the finger in x or y
					nextMove=0;
				} 
				if (strncmp( action, "touch",5)==0){ //next move is going to be make a touch
					nextMove=1;
				} 
				if (strncmp( action, "push",4)==0){	//next move is going to be make a push with some seconds				
					nextMove=2;
				} 
				if (strncmp( action, "touchMove",9)==0){		//next move is going to be make a touch	and then a move to other coordinates		
					nextMove=3;
				}
							
			}		
		}		
	}	
	if(posX>=0 && posX<=3 && posY>=0 && posY<=2 && nextMove!=-1){
		printf("Sending to the device a move action in axis: -x %d -y %d -t %d\n",posX,posY,nextMove);	// print the information to be send to the user	
		int informToTheDevice = moveDeviceFunction(posX, posY, nextMove);	// got to the library to make the move		
		if(!informToTheDevice){ 								// if something is wrong while checking the config file
			printf("ERROR you need to check your configuration file \n");
			exit(1);
		}		
		checkerVariable = 1;
	}	
	else if(sec >=1 && nextMove!=-1){
		printf("Sending to the device a push action, seconds to push: -s %d\n",sec);	// print the information to be send to the user		
		int informToTheDevice = moveDeviceFunction(sec,0, nextMove);		// got to the library to make the move
		if(!informToTheDevice){				                          // if something is wrong while checking the config file
			printf("ERROR you need to check your configuration file \n");
			exit(1);
		}		
		checkerVariable = 1;
	}
	else if(nextMove!=-1){
		printf("Sending to the device a touch action");		// print the information to be send to the user	
		int informToTheDevice = moveDeviceFunction(0,0, nextMove);		// got to the library to make the move
		if(!informToTheDevice){															// if something is wrong while checking the config file
			printf("ERROR you need to check your configuration file \n");
			exit(1);
		}		
		checkerVariable = 1;
	}
	return checkerVariable;
}
int interpretBoard(char** tokens){ // this function get the information located inthe file to define the resolution of the screen used
	int boardResolution = 0; // the definition if the resolution variable
	for (int i = 0; tokens[i]!=NULL; i++){
		if (tokens[i+1]!=NULL){
			if (strcmp( tokens[i], "-b")==0){ // b means board in the sintax of the language   
				char *entry = tokens[i+1];	// we need to add 1 to the pointer to check the next part
				if (strncmp( entry, "1x1",3)==0){ // the resolution is set as 1x1					
					boardResolution=1; // the buttons in the app will be 1cm x 1cm
				}  
				if (strncmp( entry, "2x2",3)==0){ // the resolution is set as 2x2
					boardResolution=2; // the buttons in the app will be 2cm x 2cm
				}  
				if (strncmp( entry, "3x3",3)==0){ // the resolution is set as 3x3
					boardResolution=3; // the buttons in the app will be 3cm x 3cm
				}			       				
			}			
		}		
	}
	if(boardResolution!=0){ // validate the above proccess
		printf("The resolution for the app: %d\n",boardResolution);		
		int informToTheDevice = boardDeviceFunction(boardResolution); // the method returns a number to check if the proccess call is OK
		if(!informToTheDevice){ // Error
			printf("ERROR you need to check your configuration file \n");
			exit(1);
		}		
	}	
	return boardResolution;
}

char** divideStringPattern(char* a_str, const char delimitador){ // the method will divide the string accordin to a pattern, in this case " "
    char** checkerVariable = 0; //check the method function               // taking the tokens in the line of the file
    size_t count = 0;
    char* tempString = a_str; // temporal string
    char* lastSpaceTook = 0;  // use to point to continue with the other tokens
    char delim[2];          
    delim[0] = delimitador;
    delim[1] = 0;
    while (*tempString){ //to get the size of the token
        if (delimitador == *tempString){
            count++;                    // add the blank space to save the position then
            lastSpaceTook = tempString; // save the position where got the last token
        }
        tempString++;
    }
    count += lastSpaceTook < (a_str + strlen(a_str) - 1); // Adding space
    count++;                      // continue counting
    checkerVariable = malloc(sizeof(char*) * count); // save the space to the  variable
    if (checkerVariable){ // if everything is ok gets into the if 
        size_t idx  = 0;  
        char* token = strtok(a_str, delim);
        while (token){ // if there are more letters
            assert(idx < count); // diagnotic
            *(checkerVariable + idx++) = strdup(token);
            token = strtok(0, delim); //assign the token pieces to the one to return
        }
        assert(idx == count - 1);
        *(checkerVariable + idx) = 0;
    }
    return checkerVariable; // return the token
}

int stringMatch(char *inputLineText, char *pattern){ // use to compare the string in the first parameter with the pattern
  int inplen = strlen(inputLineText);
  while(inputLineText != NULL) { // while there is a line of text available
    char *pointerText = inputLineText; // variable use to take the pointer of the text to compare later
    char *pointerPattern = pattern; // variable use to take the pointer of the pattern to compare later
    if(strlen(pointerText) < strlen(pointerPattern)) // in this case the pattern cant be larger than the text
    {     
      return -1; // return error
    }
    while (*pointerText++ == *pointerPattern++) {  // each pointer comparison    
      if(*pointerPattern == '\0' ) {  // this means the end of the pattern      
        return inplen - strlen(inputLineText+1) ; // the return
      }
      if(pointerText == NULL) {
        return -1;
      }
    }
    pointerPattern = pattern; // set the pointer again
    inputLineText ++; // to continue iteration
   }
}

void interpretBurst(char* configFileAddres){
  FILE *ptr_file;
  FILE *ptr_file1;	
  char message[255];
  int c;
  char line[1000];  
  ptr_file =fopen(configFileAddres,"r");   // the file is going to be read  
  ptr_file1 =fopen("config.txt","w");   // the file is going to be read
  if (!ptr_file && !ptr_file1){ // the file null, error doesnt exist
    printf("The file does not exist\n"); // message file does not exist         
  }	
  while (fgets(line,1000, ptr_file)!=NULL){ // line is goinf to point to every line in the code, the number is going to be the max number lines to read and the ptr_file  is going to be the file opened
	    char** tokens;  // here is going to be divide in tokens to interpret the language wrote in the congif file
		tokens = divideStringPattern(line, ' '); // the lines are going to be divided by the delimiter " ".
		int asking_IsMove = stringMatch(line, "Board"); // looking for the word action in this case
	    if(asking_IsMove > -1) {
			for (int i = 0; tokens[i]!=NULL; i++){
				if (tokens[i+1]!=NULL){
					char *entry = tokens[i+1];	// we need to add 1 to the pointer to check the next part
					if (strncmp( entry, "1x1",3)==0){ // the resolution is set as 1x1	
						strcpy(message, " echo board -b 1x1 >> config.txt");	// to send the message by system
						system(message);
					}  
					if (strncmp( entry, "2x2",3)==0){ // the resolution is set as 2x2
						strcpy(message, " echo board -b 2x2 >> config.txt");	// to send the message by system
						system(message);
					}  
					if (strncmp( entry, "3x3",3)==0){ // the resolution is set as 3x3
						strcpy(message, " echo board -b 3x3 >> config.txt");	// to send the message by system
						system(message);
					}			       				
							
				}			
			}
		}
	    asking_IsMove = stringMatch(line, "Burst"); // looking for the word action in this case
	    if(asking_IsMove > -1) {
			for (int i = 0; tokens[i]!=NULL; i++){
				if (tokens[i+1]!=NULL){
					char *entry = tokens[i+1];	// we need to add 1 to the pointer to check the next part
					if (strncmp( entry, "0",1)==0){ //number 0	
						if (i == 0){
							strcpy(message, " echo action -t move -x 0 -y 0 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						
						}
						else{
							strcpy(message, " echo action -t touchMove -x 0 -y 0 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						}
					}  
					if (strncmp( entry, "1",1)==0){ //number 1	
						if (i == 0){
							strcpy(message, " echo action -t move -x 1 -y 0 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						
						}
						else{
						strcpy(message, " echo action -t touchMove -x 1 -y 0 >> config.txt");	// to send the message by system to write in the config file
						system(message);
						}
					}  
					if (strncmp( entry, "2",1)==0){ //number 2
						if (i == 0){
							strcpy(message, " echo action -t move -x 2 -y 0 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						
						}
						else{
						strcpy(message, " echo action -t touchMove -x 2 -y 0 >> config.txt");	// to send the message by system to write in the config file
						system(message);
						}
					}  
					if (strncmp( entry, "3",1)==0){ //number 3	
						if (i == 0){
							strcpy(message, " echo action -t move -x 3 -y 0 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						
						}
						else{
						strcpy(message, " echo action -t touchMove -x 3 -y 0 >> config.txt");	// to send the message by system to write in the config file
						system(message);
						}
					}
					if (strncmp( entry, "4",1)==0){ //number 4
						if (i == 0){
							strcpy(message, " echo action -t move -x 0 -y 1 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						
						}
						else{
						strcpy(message, " echo action -t touchMove -x 0 -y 1 >> config.txt");	// to send the message by system to write in the config file
						system(message);
						}
					}  
					if (strncmp( entry, "5",1)==0){ //number 5	
						if (i == 0){
							strcpy(message, " echo action -t move -x 1 -y 1 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						
						}
						else{
						strcpy(message, " echo action -t touchMove -x 1 -y 1 >> config.txt");	// to send the message by system to write in the config file
						system(message);
						}
					}  
					if (strncmp( entry, "6",1)==0){ //number 6	
						if (i == 0){
							strcpy(message, " echo action -t move -x 2 -y 1 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						
						}
						else{
						strcpy(message, " echo action -t touchMove -x 2 -y 1 >> config.txt");	// to send the message by system to write in the config file
						system(message);
						}
					}  
					if (strncmp( entry, "7",1)==0){ //number 7
						if (i == 0){
							strcpy(message, " echo action -t move -x 3 -y 1 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						
						}
						else{
						strcpy(message, " echo action -t touchMove -x 3 -y 1 >> config.txt");	// to send the message by system to write in the config file
						system(message);
						}
					}  
					if (strncmp( entry, "8",1)==0){ //number 8	
						if (i == 0){
							strcpy(message, " echo action -t move -x 0 -y 2 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						
						}
						else{
						strcpy(message, " echo action -t touchMove -x 0 -y 2 >> config.txt");	// to send the message by system to write in the config file
						system(message);
						}
					}  
					if (strncmp( entry, "9",1)==0){ //number 9
						if (i == 0){
							strcpy(message, " echo action -t move -x 1 -y 2 >> config.txt");	// to send the message by system to write in the config file
							system(message);
						
						}
						else{
						strcpy(message, " echo action -t touchMove -x 1 -y 2 >> config.txt");	// to send the message by system to write in the config file
						system(message);
						}
					}  
							
				}
				else{
					strcpy(message, " echo action -t touch >> config.txt");	// to send the message by system to write in the config file
					system(message);
					strcpy(message, " echo action -t move -x 0 -y 0 >> config.txt");	// to send the message by system to write in the config file
					system(message);
				}
			}
		}
  }


}

//
//Here important thing:
//we are going to have a language and the configuration in the same file, ask to the prof
//
int main(int argc, char **argv){  // main function
  char * configFileAddres;	// this going to be the address of the config file
  if(argv[1]!=NULL){ // in the case the user want to use another file 
  
	  configFileAddres = argv[1]; // the parameter to other file
	  printf("you change the file\n");
	  interpretBurst(configFileAddres);
	  configFileAddres ="config.txt";
  } 
  else{
    printf("***************************************************************************\n");
	  printf("You are going to use the file config.txt\n"); // the default file is going to be use
	  configFileAddres ="config.txt";	  //the default file is assign
  }  
  
  FILE *ptr_file;
  char line[1000];  
  ptr_file =fopen(configFileAddres,"r");   // the file is going to be read 
  if (!ptr_file){ // the file null, error doesnt exist
    printf("The file does not exist\n"); // message file does not exist
    return 0;          
  }	
  while (fgets(line,1000, ptr_file)!=NULL){ // line is goinf to point to every line in the code, the number is going to be the max number lines to read and the ptr_file  is going to be the file opened
	    char** tokens;  // here is going to be divide in tokens to interpret the language wrote in the congif file
		tokens = divideStringPattern(line, ' '); // the lines are going to be divided by the delimiter " ".
		int asking_IsMove = stringMatch(line, "action"); // looking for the word action in this case
	    if(asking_IsMove > -1) {		
        	if (tokens) // as the lines were divided in tokens, while the line still has tokens
        	{		
         	 int checkerVariable = interpretMovement(tokens);		
         	 if(checkerVariable==0)
         	 {
         	   printf("**ERROR_IN_MOVE: detected in the line: %s\n",line); //there was an error 
          	  return 0;
          	}	
        	}            
	    }	    
	  	int asking_IsBoard = stringMatch(line, "board"); // looking for the word board, to check the configuration of the matrix in the app
	  	if( asking_IsBoard > -1) {		
      	if (tokens){ // still the line has tokens 
          int checkerVariable = interpretBoard(tokens);		
          if(checkerVariable==0){
            printf("**ERROR_IN_BOARD: detected in line: %s\n",line);//there was an error 
            return 0;
          }	
        }            
	    }	    
	    free(tokens);
  }  
  fclose(ptr_file); // the file is going to be closed 
  return 0;
}