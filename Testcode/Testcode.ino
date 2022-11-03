//LCD Code
/* PROJECT BY MANISH KUMAR YADAV*/
#include<LiquidCrystal.h>
int rs=7;
int en=8;
int d4=9;
int d5=10;
int d6=11;
int d7=12;
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
