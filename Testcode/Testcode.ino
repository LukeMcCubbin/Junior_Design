
//LCD Code
/* PROJECT BY MANISH KUMAR YADAV*/
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
int buttonState = 0;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void StartBatch(int* randNum, LiquidCrystal lcd);
void printScreen(int val, LiquidCrystal lcd);
void printScreen2(int val, int* randNum, LiquidCrystal lcd);

//moving conveyor
void lower_level();
void raise_level();
void DC_run();


//Setup
void setup() {
 lcd.begin(16,2); 
 Serial.begin(9600); 

 //DC motor
 pinMode(speedPin,OUTPUT);
 pinMode(dir1,OUTPUT);
 delay(10);

 pinMode(bt_start, INPUT_PULLUP);
 
 pinMode(SENSORPIN, INPUT);     
 digitalWrite(SENSORPIN, HIGH); // turn on the pullup
 //StepperLeft.setSpeed(30);
 //StepperUp.setSpeed(30);
}


//Loop
void loop() {
    //Starts a batch
    StartBatch(&randNum, lcd);
    delay(10);

    //sets values
    count = 0;
    tempval = randNum;
    buttonState = digitalRead(bt_start);

    //loading state
    
    for(int i=0; i<tempval; i++){
        printScreen2(tempval-i, &randNum, lcd);
        DC_run();
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
    

    //processing state
    while(count!=tempval){
        switch(expression) {
            case 0:
                //prints this case
                printScreen(expression+1,lcd);
                //runsDC motor
                DC_run();
                //falls
                delay(1000);
                //lowers the lift 
                lower_level();
                expression ++;
                count++;
                break;
                
            case 1:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(1000);
                //across
                for(int i =0; i< 100; i++){
                  StepperLeft.step(1);
                  StepperRight.step(1);
                  delay(10);
                }
                raise_level();
                expression++;
                count++;
                break;
                
            case 2:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(1000);
                lower_level();
                expression++;
                count++;
                break;
                
            case 3:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                raise_level();
                //across
                for(int i =0; i< 100; i++){
                  StepperLeft.step(1);
                  StepperRight.step(1);
                  delay(10);
                }
                expression++;
                count++;
                break;
                
            case 4:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                lower_level();
                //across
                expression++;
                count++;
                break;
                
            case 5:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                raise_level();
                //across
                expression++;
                count++;
                break;
                
            case 6:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(50);
                lower_level();
                //across
                expression++;
                count++;
                break;
                
            case 7:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(1000);
                expression ++;
                count++;
                break;
                //This one may be unnecessary
                /*
                case 8:
                     DC_run();
                    delay(50);
                    lower_level();
                    //across
                    expression++;
                    break;
                    */
                    
            default:

                if(buttonState == HIGH){
                delay(1000);
                count++;
                raise_level();
                expression = 0;
                buttonState = digitalRead(bt_start);
                }
                else{
                  delay(2000);
                }

        }
    }

//delay(10);

}
void StartBatch(int* randNum, LiquidCrystal lcd){
  randomSeed(analogRead(A0));
  *randNum = random(1, 9);
  lcd.clear();
  delay(10);
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
  delay(10);
  lcd.setCursor(0,0);
  lcd.print("Processing :");
  lcd.setCursor(0,1);
  lcd.print("value: ");
  lcd.print(val);
}
void printScreen2(int val, int* randNum, LiquidCrystal lcd){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading :");
  lcd.print(*randNum);
  lcd.setCursor(0,1);
  lcd.print("Load: ");
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
void DC_run(){
  for(int i =0; i< 200; i++){
   digitalWrite(dir1,HIGH);
   analogWrite(speedPin,mSpeed);
   delay(10);
  }
  digitalWrite(dir1,LOW);
}
