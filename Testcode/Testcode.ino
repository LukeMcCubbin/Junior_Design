
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

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

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



//Setup
void setup() {
 lcd.begin(16,2); 
 Serial.begin(9600); 

 //DC motor
 pinMode(speedPin,OUTPUT);
 pinMode(dir1,OUTPUT);
 delay(10);

 pinMode(SENSORPIN, INPUT_PULLUP);//Setting as pullup
 pinMode(SENSORPIN2, INPUT_PULLUP);   
 
 //pinMode(SENSORPIN, INPUT);     
 //digitalWrite(SENSORPIN, HIGH); // turn on the pullup
 //StepperLeft.setSpeed(30);
 //StepperUp.setSpeed(30);
}


//Loop
void loop() {
    //Starts a batch
    StartBatch(&randNum, lcd);
    delay(1000);

    //sets values
    count = 0;
    tempval = randNum;
  

    //loading state
    
    for(int i=0; i<tempval; i++){
        printScreen2(tempval-i, &randNum, lcd);
        DC_run();
        delay(100);
    }

/*
    tempval = digitalRead(SENSORPIN2);
        
    while(count < (int)randNum){
      sensor = digitalRead(SENSORPIN2);
      if(tempval == HIGH && sensor == LOW){
        digitalWrite(dir1, HIGH);
        //print
      }else if(tempval == LOW && sensor == HIGH){
        delay(100);//Spacing between boxes
        digitalWrite(dir1, LOW);
        count++;
        //print
      }
      tempval = sensor; //store current into previous
    }
    */
    
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
                delay(500);
                //lowers the lift 
                lower_level();
                expression ++;
                count++;
                break;
                
            case 1:
                //prints this case
                printScreen(expression+1,lcd);
                DC_run();
                delay(500);
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
                delay(50);
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
                delay(50);
                raise_level();
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
                delay(2000);
                count++;
                expression = 0;
        }
    }

//delay(10);

}
