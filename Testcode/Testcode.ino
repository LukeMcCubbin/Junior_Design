//LCD Code
/* PROJECT BY MANISH KUMAR YADAV*/
#include<LiquidCrystal.h>
#include <Stepper.h>

#define bt_start A1 // Start Button
#define bt_Stop A2 // Stop Button

const int stepsPerRevolution=200; 

Stepper StepperUp(stepsPerRevolution, 2,3,4,5);
//Stepper Stepper1(stepsPerRevolution, 6, 7, 8, 9);
//Stepper Stepper2(stepsPerRevolution, 10, 11, 12, 13);

int stepCount = 0; 


int rs=31;
int en=33;
int d4=23;
int d5=25;
int d6=27;
int d7=29;
int tm=1000;
int j;
int state = 1;

int randNum = 0;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

int randGen(){
int randnum;
randnum = random(1, 9);
return randnum;
}

void StartBatch(int randNum, LiquidCrystal lcd){
  //randomSeed(analogRead(A0));

  lcd.clear();
  lcd.print("Please load: ");
  lcd.print(randNum);
  //*loadTrack = 0;
}

void lower_level(Stepper stepper){
 for(int i =0; i< 200; i++){
  stepper.step(1);
  delay(10);
}
}


//Setup
void setup() {
 lcd.begin(16,2); 
 Serial.begin(9600); 

 //pinMode(bt_P, INPUT_PULLUP);
 //pinMode(bt_L, INPUT_PULLUP);
 //StartBatch(randNum, lcd);
 
}

//Loop
void loop() {
  int randNum = randGen();
  StartBatch(randNum,lcd);
  switch (state){

    case 1:
      StartBatch(randNum,lcd);
      lower_level(StepperUp);
      delay(100);
      break;

      default: 
        break;
    
    
  }

  /*
StartBatch(&randNum, lcd);
delay(200);
lower_level(StepperUp);

delay(1000);
*/

}
