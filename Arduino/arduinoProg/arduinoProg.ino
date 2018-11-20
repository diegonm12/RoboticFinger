#include <Stepper.h>

const int stepsPerRevolution = 400;  // change this to fit the number of steps per revolution
String instruction = ""; // this string is going to have the instruction sended from  the driver
int action = 0; // which action is going to do next
int resolution = 1; // to handle the resolution to use
int posX = 0; // to handle the positions in X0,0,
int posY = 0; // to handle the positions in Y
int laterPosY = 0; // the last position in the Y axis
int laterPosX = 0; // the last position in the X axis
int seconds = 0;  // the seconds in the push
const int inputMotorA1 = 2; // pin 1 motor A
const int inputMotorA2 = 3; // pin 2 motor A
const int inputMotorA3 = 4; // pin 3 motor A
const int inputMotorA4 = 5; // pin 4 motor A
const int inputMotorB1 = 6; // pin 1 motor B
const int inputMotorB2 = 7; // pin 2 motor B
const int inputMotorB3 = 8; // pin 3 motor B
const int inputMotorB4 = 9; // pin 4 motor B
const int inputMotorC1 = 10; // pin 1 motor C
const int inputMotorC2 = 11; // pin 2 motor C
const int inputMotorC3 = 12; // pin 3 motor C
const int inputMotorC4 = 13; // pin 4 motor C
Stepper myStepper(stepsPerRevolution, inputMotorA1,inputMotorA2,inputMotorA3,inputMotorA4); //define the stepper motor A
Stepper myStepper2(stepsPerRevolution, inputMotorB1,inputMotorB2,inputMotorB3,inputMotorB4); //define the stepper motor B
Stepper myStepper3(stepsPerRevolution, inputMotorC1,inputMotorC2,inputMotorC3,inputMotorC4); //define the stepper motor C

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(30); // define the revolution per minutes from the stepper 1
  myStepper2.setSpeed(30); // define the revolution per minutes from the stepper 2
  myStepper3.setSpeed(30); // define the revolution per minutes from the stepper 3
  pinMode(inputMotorA1, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorA2, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorA3, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorA4, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorB1, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorB2, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorB3, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorB4, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorC1, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorC2, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorC3, OUTPUT);// set the pin of the motor as an output
  pinMode(inputMotorC4, OUTPUT);// set the pin of the motor as an output
  Serial.begin(9600); // initialize the serial port:
}



void stopMotor(int entry1,int entry2,int entry3,int entry4){ // this function turns down the motor because it sets everything in LOW
  digitalWrite(entry1, LOW); // the entry is set LOW
  digitalWrite(entry2, LOW);  // the entry is set LOW
  digitalWrite(entry3, LOW); // the entry is set LOW
  digitalWrite(entry4, LOW);  // the entry is set LOW
  }
void touch(){ // this method is going to be responsable for the touch of the finger to the board
  myStepper.step(stepsPerRevolution); // first the finger is going to get close to the board to touch it
  myStepper.step(-stepsPerRevolution); // and then the finger is going to get to the original position
  stopMotor(inputMotorA1,inputMotorA2,inputMotorA3,inputMotorA4); // the function to stop the motor is call after the movemnet of the finger
  }
void push(int seconds){ // this function handle the push of the finger and touch the screen the se
  seconds = seconds -1;
  myStepper.step(stepsPerRevolution);
  stopMotor(inputMotorA1,inputMotorA2,inputMotorA3,inputMotorA4);
  delay(seconds*1000);
  myStepper.step(-stepsPerRevolution);
  stopMotor(inputMotorA1,inputMotorA2,inputMotorA3,inputMotorA4);
  
  }
void moveFingerY(int resolutionBoard, int nextMoveY){
  int offset = laterPosY - nextMoveY;
  laterPosY = nextMoveY;
  if (offset > 0){ // means that the finger is going to go down
    for(int i = 0 ; i < offset; i++){
      if (nextMoveY == 0){
        myStepper2.step((-70*resolutionBoard) - 10);
        stopMotor(inputMotorB1,inputMotorB2,inputMotorB3,inputMotorB4); // to stop the motor
      }
      else{
      myStepper2.step(-70*resolutionBoard);
      stopMotor(inputMotorB1,inputMotorB2,inputMotorB3,inputMotorB4); // to stop the motor
      }
    }
    }
  else if (offset < 0){ // means that the finger is going to go up
    offset = offset * -1; // to turn positive the offset
    for(int i = 0 ; i < offset; i++){
      myStepper2.step(70*resolutionBoard);
      stopMotor(inputMotorB1,inputMotorB2,inputMotorB3,inputMotorB4); // to stop the motor
    }
   }  
}
void moveFingerX(int resolutionBoard, int nextMoveX){
  int offset = laterPosX - nextMoveX;
  laterPosX = nextMoveX;
  if (offset > 0){ // means that the finger is going to go down
    for(int i = 0 ; i < offset; i++){
      myStepper3.step(81*resolutionBoard);
      stopMotor(inputMotorC1,inputMotorC2,inputMotorC3,inputMotorC4); // to stop the motor
    }
  }
  else if (offset < 0){ // means that the finger is going to go up
    offset = offset * -1; // to turn positive the offset
    for(int i = 0 ; i < offset; i++){
      myStepper3.step(-81*resolutionBoard);
      stopMotor(inputMotorC1,inputMotorC2,inputMotorC3,inputMotorC4); // to stop the motor
    }
   }  
}
void loop() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    instruction += inChar; // recieve the instruction
    if(instruction.length() == 5 && instruction != "Board"){ // to set the board size
      action = instruction[0] - '0';  // action to do in the motor to move
      if(action == 0){  // action 0 just move
        posX = instruction[2] - '0';  // position x to 
        posY = instruction[4] - '0';  // position y to 
        moveFingerY(resolution,posY); // make the move in y 
        moveFingerX (resolution,posX); // make the move in x 
        Serial.write("L"); // letter use to say to the program is ready
        instruction = ""; // clear the instruction
        }      
      else if(action == 1){
        touch();  // make the touch just move the motor to the front
        Serial.write("L");  // is ready
        instruction = "";
        }
      else if (action == 2){ // action to do the push
        seconds = posY = instruction[2] - '0';  // seconds in the push of the finger
        push(seconds);  // makes the push with the seconds specified
        Serial.write("L"); // is ready
        instruction = ""; // clear the instruction
      }
      else if (action == 3){ // to make the move touch
        posX = instruction[2] - '0';// position in x
        posY = instruction[4] - '0';// position in y
        touch();
        moveFingerY(resolution,posY); // commits the movement
        moveFingerX(resolution,posX); // commits the movement
        Serial.write("L");
        instruction = "";
      }
      else{
        Serial.write("L");
        instruction = "";
      }
     }
     if(instruction.length() == 7){
      resolution = instruction[6] - '0'; // to assign the resolution of the board
      Serial.write("L");
      instruction = "";
     }
  }
}

