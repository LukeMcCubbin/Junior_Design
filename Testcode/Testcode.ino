
//LCD Code
/* PROJECT BY MANISH KUMAR YADAV*/
#include<LiquidCrystal.h>
#include <Stepper.h>

#define bt_start A1 // Start Button
#define bt_Stop A2 // Stop Button

//stepper
const int stepPerRevolution=200; 
Stepper StepperUp(stepPerRevolution, 2,3,4,5);
Stepper StepperLeft(stepPerRevolution, 6,7,8,9);
Stepper StepperRight(stepPerRevolution, 10,11,12,13);
int stepCount = 0; 

//DC Motor
int speedPin=52;
int dir1 = 50;
//int dir2 = 48;
int mSpeed=255;

//LCD
int rs=31;
int en=33;
int d4=23;
int d5=25;
int d6=27;
int d7=29;
int tm=1000;
int j;

//Everything else
int expression = 0;
int randNum = 0;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void StartBatch(int* randNum, LiquidCrystal lcd){
  randomSeed(analogRead(A0));
  *randNum = random(1, 9);
  delay(200);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Processing :");
  lcd.setCursor(0,1);
  lcd.print("Please load: ");
  lcd.print(*randNum);
  delay(100);
  //*loadTrack = 0;
}

void lower_level(){
  for(int i =0; i< 200; i++){
   StepperUp.step(1);
   //StepperLeft.step(-1);
   //StepperRight.step(-1);
   delay(10);
  }
}
void raise_level(){
  for(int i =0; i< 200; i++){
   StepperUp.step(-1);
   //StepperLeft.step(1);
   //StepperRight.step(1);
   delay(10);
  }
}
void DC_run(){
  for(int i =0; i< 200; i++){
   digitalWrite(dir1,HIGH);
   analogWrite(speedPin,mSpeed);
   delay(10);
  }
  digitalWrite(dir1,LOW);
}


//Setup
void setup() {
 lcd.begin(16,2); 
 Serial.begin(9600); 

 //DC motor
 pinMode(speedPin,OUTPUT);
 pinMode(dir1,OUTPUT);
 StartBatch(&randNum, lcd);
  delay(10);
 //StepperLeft.setSpeed(30);
 //StepperUp.setSpeed(30);
}


//Loop
void loop() {
  /*
  StartBatch(&randNum, lcd);
  delay(10);
  */
  
  //digitalWrite(dir1,HIGH);
  //analogWrite(speedPin,mSpeed);

 //StepperLeft.step(stepPerRevolution);
 /*
 for(int i =0; i< 200; i++){
  //StepperUp.step(1);
  StepperLeft.step(1);
  delay(10);
  */

 switch(expression) {
  case 0:
      lower_level();
      expression ++;
      break;
  case 1:
      raise_level();
      //across
      expression++;
      break;
  case 2:
      raise_level();
      //across
      expression++;
      break;
  case 3:
      raise_level();
      //across
      expression++;
      break;
  case 4:
      raise_level();
      //across
      expression++;
      break;
  case 5:
      raise_level();
      //across
      expression++;
      break;
  case 6:
      raise_level();
      //across
      expression++;
      break;
  case 7:
      lower_level();
      expression ++;
      break;
  //This one may be unnecessary
  case 8:
      raise_level();
      //across
      expression++;
      break;
  default:
      expression = 0;
      delay(20);
      StartBatch(&randNum, lcd);
      break;
 }
 

//delay(10);

}
