// Junior Design Code
//[Arum] Replaced code with Luke's test code with expanded loading process and edits to DC run
//Comments 
/*
 * Sections to write are 1. overall code, 2. Conveyor belt, 3. sensors, 4. XY  coordinate
 * 
 */

//Define 
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
int count = 0;
int tempval = 0;

// variables will change:
int sensor = 0;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void StartBatch(int* randNum, LiquidCrystal lcd);
void printScreen(int val, LiquidCrystal lcd);
void printScreen2(int val, LiquidCrystal lcd);
void lower_level();
void raise_level();
void DC_run(int t);
void moveInY(int dir, int steps, Stepper step1, Stepper step2);// moves across belt
void moveInX(int dir, int steps, Stepper step1, Stepper step2);// moves along belt
//dir should be 1 or -1


//Setup
void setup() {
 lcd.begin(16,2); 
 Serial.begin(9600); 

 //DC motor
 pinMode(speedPin,OUTPUT);
 pinMode(dir1,OUTPUT);
 delay(10);
 
 pinMode(SENSORPIN, INPUT);
 pinMode(SENSORPIN2, INPUT_PULLUP);     
 digitalWrite(SENSORPIN, HIGH); // turn on the pullup
 pinMode(bt_start, INPUT);
 //StepperLeft.setSpeed(30);
 //StepperUp.setSpeed(30);
}


//Loop
void loop() {
    //Starts a batch
    StartBatch(&randNum, lcd);
    delay(1000);

    //sets values
    count = 0;//using count to record the boxes loaded
    //using tempVal to record previous reading
    tempval = 0;
  

    //loading state
    //Read to get starting "previous" state
    //Could be function with two parameters
    //int randNum; int SENSORPIN2
    tempval = digitalRead(SENSORPIN2);
        
    while(count < randNum){
      sensor = digitalRead(SENSORPIN2);
      if(tempval == HIGH && sensor == LOW){
        //run on beam-break
        digitalWrite(dir1, HIGH);
        delay(100);
        digitalWrite(dir1, LOW);
      }
      tempval = sensor; //store current into previous
    }
    
    sensor = digitalRead(SENSORPIN);
    count = 0; //reset count

    //travel -- maybe make this a function?
    //parameter sensor
    
    while(sensor != LOW){
      digitalWrite(dir1,HIGH);
      analogWrite(speedPin,mSpeed);
      sensor = digitalRead(SENSORPIN);
    }
    digitalWrite(dir1,HIGH);
    
    //processing state
    while(count <= (int)randNum){
        switch(expression) {
            case 0:
                //prints this case
                printScreen(expression+1,lcd);
                //runsDC motor
                DC_run(200);
                //falls
                delay(50);
                //lowers the lift 
                lower_level();
                expression ++;
                count++;
                break;
                
            case 1:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run(200);
                delay(50);
                raise_level();
                //across
                expression++;
                count++;
                break;
                
            case 2:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run(200);
                delay(50);
                lower_level();
                //across
                expression++;
                count++;
                break;
                
            case 3:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run(200);
                delay(50);
                raise_level();
                //across
                expression++;
                count++;
                break;
                
            case 4:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run(200);
                delay(50);
                lower_level();
                //across
                expression++;
                count++;
                break;
                
            case 5:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run(200);
                delay(50);
                raise_level();
                //across
                expression++;
                count++;
                break;
                
            case 6:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run(200);
                delay(50);
                lower_level();
                //across
                expression++;
                count++;
                break;
                
            case 7:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run(200);
                delay(50);
                expression ++;
                count++;
                break;
            default:
            //Could be a rest state for replacing the pallet
                delay(10);
                if(digitalRead(bt_start) == HIGH){
                  expression = 0;
                  raise_level();
                }
        }
    }
}

void StartBatch(int* randNum, LiquidCrystal lcd){
  randomSeed(analogRead(A0));
  *randNum = random(1, 9);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading :");
  lcd.setCursor(0,1);
  lcd.print("Random number: ");
  lcd.print(*randNum);
  delay(1000);
  //*loadTrack = 0;
}

void printScreen(int val, LiquidCrystal lcd){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Processing :");
  lcd.setCursor(0,1);
  lcd.print("value: ");
  lcd.print(val);
}
void printScreen2(int val, LiquidCrystal lcd){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading :");
  lcd.setCursor(0,1);
  lcd.print("remaining: ");
  lcd.print(val-1);
}
void lower_level(){
  for(int i =0; i< 100; i++){
   StepperUp.step(1);
   //StepperLeft.step(-1);
   //StepperRight.step(-1);
   delay(10);
  }
}
void raise_level(){
  for(int i =0; i< 100; i++){
   StepperUp.step(-1);
   //StepperLeft.step(1);
   //StepperRight.step(1);
   delay(10);
  }
}
void DC_run(int t){
   analogWrite(speedPin,mSpeed);
   digitalWrite(dir1,HIGH);
   delay(t * 10);
   digitalWrite(dir1,LOW);
}
void moveInY(int dir, int steps, Stepper step1, Stepper step2){
  for(int i = 0; i < steps; i++){
    step1.step(dir);
    step2.step(-dir);
  }
}
void moveInX(int dir, int steps, Stepper step1, Stepper step2){
  for(int i = 0; i < steps; i++){
    step1.step(dir);
    step2.step(dir);
  }
}
