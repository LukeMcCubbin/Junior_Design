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
