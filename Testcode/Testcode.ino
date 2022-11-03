//LCD Code
/* PROJECT BY MANISH KUMAR YADAV*/
#include<LiquidCrystal.h>
int rs=31;
int en=33;
int d4=23;
int d5=25;
int d6=27;
int d7=29;
int tm=1000;
int j;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
void setup() {
 lcd.begin(16,2);                
}
void loop() {
lcd.setCursor(0,0);
lcd.print("LOADING STATE");
lcd.setCursor(0,1);
lcd.print("BLOCKS - 7");
}
//#include <Stepper.h>

// C++ code
//
//const int stepPerRevolution=200; 
//
//Stepper Stepperx(stepPerRevolution, 5,11,2,8);
//int stepCount = 0; 
//void setup() {
//
//Serial.begin(9600);
//}
//void loop() {
//
//for(int i =0; i< 200; i++){
//  Stepperx.step(1);
//  delay(10);
//}
//
//delay(1000);
//
//}
