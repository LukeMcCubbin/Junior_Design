//Junior Design Project Code

//This code is for loading a single layer.
#include<LiquidCrystal.h>
#include <Stepper.h>

#define bt_start A1 // Start Button
#define bt_Stop A2 // Stop Button
#define SENSORPIN 40
#define SENSORPIN2 41

//stepper
const int stepPerRevolution=200; 
Stepper StepperLeft(stepPerRevolution, 2,3,4,5);
Stepper StepperRight(stepPerRevolution, 6,7,8,9);
Stepper StepperUp(stepPerRevolution, 10,11,12,13);
int stepCount = 0; 

//DC Motor
int speedPin=52;
int dir1 = 50;
//int dir2 = 48;
int mSpeed=500;
int steps = 250;

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
int count = 0;
int tempval = 0;

// variables will change:
int sensor = 0;
int buttonState = 0;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void printScreen(int val, LiquidCrystal lcd);
void printScreen2(int val, int* randNum, LiquidCrystal lcd);

//moving conveyor
void lower_level(int t);
void raise_level(int t);
void DC_run();
void DC_run_after();
void moveLeft(Stepper step1, Stepper step2);
void moveUp(Stepper step1, Stepper step2);
void moveRight(Stepper step1, Stepper step2);
void moveDown(Stepper step1, Stepper step2);
int zShift = 150;
//Setup
void setup() {
 lcd.begin(16,2); 
 Serial.begin(9600); 

 //DC motor
 pinMode(speedPin,OUTPUT);
 pinMode(dir1,OUTPUT);
 delay(10);

 pinMode(bt_start, INPUT);
 
 
 pinMode(SENSORPIN, INPUT);     
 digitalWrite(SENSORPIN, HIGH); // turn on the pullup
 digitalWrite(bt_start, HIGH);
 //StepperLeft.setSpeed(30);
 //StepperUp.setSpeed(30);
}


//Loop
void loop() {
  
    //LCD Init
    lcd.begin(16,2); 
    lcd.clear();

    //Starts a batch
    randomSeed(analogRead(A0));
    //randNum = random(1, 9);
    randNum = 8;
    delay(10);

    //sets values
    count = 0;
    tempval = randNum;
    buttonState = digitalRead(bt_start);
    
    for(int i=0; i<tempval; i++){
        printScreen2(tempval-i, randNum, lcd);
        DC_runConveyor();
        delay(100);
    }
    
    
    sensor = digitalRead(SENSORPIN);
    

    //travel -- maybe make this a function?
    //parameter sensor
    while(sensor != LOW){
      digitalWrite(dir1,HIGH);
      analogWrite(speedPin,mSpeed);
      sensor = digitalRead(SENSORPIN);
    }
    digitalWrite(dir1,HIGH);
    DC_run_after();
    

    //processing state
    while(count<=tempval-1){
        switch(expression) {
            case 0:
                lcd.clear();
                lcd.begin(16,2); 
                Serial.begin(9600);
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                lower_level(zShift);
                moveLeft(StepperLeft, StepperRight);
                raise_level(zShift);
                expression ++;
                count++;
                delay(50);
                break;
                
            case 1:
                lcd.clear();
                lcd.begin(16,2); 
                Serial.begin(9600);
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                //across
                lower_level(zShift);
                moveUp(StepperLeft, StepperRight);
                raise_level(zShift);
                expression++;
                count++;
                delay(50);
                break;
                
            case 2:
                lcd.clear();
                lcd.begin(16,2); 
                Serial.begin(9600);
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                lower_level(zShift);
                moveRight(StepperLeft, StepperRight);
                raise_level(zShift);
                expression++;
                count++;
                delay(50);
                break;
                
            case 3:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                lower_level(zShift+93);
                moveDown(StepperLeft, StepperRight);
                raise_level(zShift);
                //across
                expression++;
                count++;
                delay(50);
                break;
                
            case 4:
                lcd.clear();
                lcd.begin(16,2); 
                Serial.begin(9600);
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                lower_level(zShift);
                moveLeft(StepperLeft, StepperRight);
                raise_level(zShift);
                delay(50);
                expression++;
                count++;
                break;
                
            case 5:
                lcd.begin(16,2); 
                Serial.begin(9600);
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                lower_level(zShift);
                moveUp(StepperLeft, StepperRight);
                raise_level(zShift);
                //across
                expression++;
                count++;
                delay(50);
                break;
                
            case 6:
                lcd.clear();
                lcd.begin(16,2); 
                Serial.begin(9600);
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                lower_level(zShift);
                moveRight(StepperLeft, StepperRight);
                raise_level(zShift);
                delay(50);
                //across
                expression++;
                count++;
                break;
                
            case 7:
                lcd.clear();
                lcd.begin(16,2); 
                Serial.begin(9600);
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                lower_level(zShift);
                moveDown(StepperLeft, StepperRight);
                raise_level(zShift);
                expression ++;
                count;
                delay(50);
                break;
                //This one may be unnecessary

            default:
                lcd.clear();
                lcd.begin(16,2); 
                Serial.begin(9600);
                buttonState = digitalRead(bt_start);
                if(buttonState == LOW){
                delay(10);
                count++;
                //moveDown(StepperLeft, StepperRight);
                raise_level(zShift+80);
                expression = 0;
                buttonState = digitalRead(bt_start);
                }
                else{
                  delay(200);
                }

        }
    }

}

void printScreen(int val, LiquidCrystal lcd){
  //lcd.clear();
  delay(10);
  lcd.setCursor(0,0);
  lcd.print("Processing :    ");
  lcd.setCursor(0,1);
  lcd.print("State:         ");
  lcd.print(val);
}
void printScreen2(int val, int randNum, LiquidCrystal lcd){
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading :      ");
  lcd.print(randNum);
  lcd.setCursor(0,1);
  lcd.print("Remaining:     ");
  lcd.print(val-1);
}


void lower_level(int t){
  for(int i =0; i< t; i++){
   StepperUp.step(1);
   delay(10);
  }
}
void raise_level(int t){
  for(int i =0; i< t; i++){
   StepperUp.step(-1);
   delay(10);
  }
}

void DC_runConveyor(){
  for(int i =0; i< 260; i++){
   digitalWrite(dir1,HIGH);
   analogWrite(speedPin,mSpeed);
   delay(10);
  }
  digitalWrite(dir1,LOW);
}
void DC_run(){
  for(int i =0; i< 320; i++){
   digitalWrite(dir1,HIGH);
   analogWrite(speedPin,mSpeed);
   delay(10);
  }
  digitalWrite(dir1,LOW);
}
void DC_run_after(){
  for(int i =0; i< 350; i++){
   digitalWrite(dir1,HIGH);
   analogWrite(speedPin,mSpeed);
   delay(10);
  }
  digitalWrite(dir1,LOW);
}
void moveLeft(Stepper step1, Stepper step2){
  for(int i = 0; i < steps; i++){
    step1.step(1);
    step2.step(1);
    delay(10);
  }
}
void moveUp(Stepper step1, Stepper step2){
    for(int i = 0; i < steps-5; i++){
      step1.step(1);
      step2.step(-1);
      delay(10);
    }
}
void moveRight(Stepper step1, Stepper step2){
  for(int i = 0; i < steps; i++){
    step1.step(-1);
    step2.step(-1);
    delay(10);
  }
}
void moveDown(Stepper step1, Stepper step2){
    for(int i = 0; i < steps-5; i++){
      step1.step(-1);
      step2.step(1);
      delay(10);
    }
}
