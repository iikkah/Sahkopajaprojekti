#include <CommLib.h>
#include <Servo.h>
//This program uses DVR8825 chip to control the stepper motors, StepPin and DirPin are connected to the chip

// Define stepper motor connections and steps per revolution:
#define dirPin0 22
#define stepPin0 23
#define dirPin1 24
#define stepPin1 25
#define dirPin2 26
#define stepPin2 27
#define dirPin3 28
#define stepPin3 29
#define switch0 30
#define switch1 31
#define switch2 32
#define switch3 33
#define stepsPerRevolution 500
byte *info = calloc(4,1);
//NOA,    //No action
//CAL,    //Calibrate
//RES,    //Reset
//RSTK,   //Restock
//SRV_C,  //Serve can
//ADD_C   //Add can
Servo myservo;
//Connect switches 0,1,2,3 to a pin and the other end to a ground.


void setup() {
  // Declare pins as output:
  pinMode(stepPin0, OUTPUT);
  pinMode(dirPin0, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(switch0,INPUT_PULLUP);
  pinMode(switch1,INPUT_PULLUP);
  pinMode(switch2,INPUT_PULLUP);
  pinMode(switch3,INPUT_PULLUP);
  myservo.attach(30);
  Serial.begin(9600);
  char x=*info+48;

  
}

void loop() {

  act ret = commListen(info);
  
  if(ret==SRV_C){
    canserve();
  }
  if(ret==ADD_C){
    canadd();
  }
  if(ret==RSTK){
    restock();
  }
  
  
  
}
int canserve(){
    // Set the spinning direction clockwise:
    char x=*info+48;
    char dirPin="dirPin"+x;
    char stepPin="stepPin"+x;
    
    
  digitalWrite(dirPin, HIGH);
  

  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  int pos=0;
  //This part of the code is unclear, since we weren't able to test or even get the servo we ordered
  //There is a high chance that this part needs tweeking if we ever make the final product

  delay(1000);
  for (pos = 0; pos <= 80; pos += 1) { // goes from 0 degrees to 80 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1000);                       
  }
  for (pos = 80; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
}

int canadd(){
    char x=*info+48;
    // Set the spinning direction clockwise:
    char dirPin="dirPin"+x;
    char stepPin="stepPin"+x;
    
    
  digitalWrite(dirPin, HIGH);
  

  
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
  }

  delay(1000);
}

int restock(){
  //This function reverses the shelf plates to the end of the shelf and stops the stepper when it reaches the back of the shelf wall for each cell of the shelf
  int run0=digitalRead(switch0);
  while(run0==LOW){
    digitalWrite(dirPin0, HIGH);
    digitalWrite(stepPin0, LOW);
    delayMicroseconds(1000);
    digitalWrite(stepPin0, HIGH);
    delayMicroseconds(1000);
  }
  int run1=digitalRead(switch1);
  while(run1==LOW){
    digitalWrite(dirPin1, HIGH);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(1000);
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(1000);
  }
  int run2=digitalRead(switch2);
  while(run2==LOW){
    digitalWrite(dirPin2, HIGH);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(1000);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(1000);
  }
  int run3=digitalRead(switch3);
  while(run3==LOW){
    digitalWrite(dirPin3, HIGH);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(1000);
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(1000);
  }
  
}
