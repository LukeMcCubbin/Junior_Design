#include <LiquidCrystal.h>
void StartBatch(long* randNum, LiquidCrystal lcd){
  randomSeed(analogRead(A0));
  *randNum = random(1, 9);
  delay(200);
  lcd.clear();
  lcd.print("Please load: ");
  lcd.println(randNum);
  *loadTrack = 0;
}

int LoadProcess(int sensor, int motor, int batchSize){
  int prevSensor = digitalRead(sensor);
  int numLoad = 0;
  delay(200);
  lcd.clear();
  lcd.print(numLoad);
  lcd.println(" boxes loaded");
  while(numLoad < batchSize){
    if(prevSensor == HIGH && digitalRead(sensor) == LOW){
      //On beam-break
      digitalWrite(motor, HIGH);
    }
    if(prevSensor == LOW && digitalRead(sensor) == HIGH){
      //On beam-restore
      digitalWrite(motor, LOW);
      numLoad++;//Once beam is cleared the box is loaded and incremented
      lcd.clear();
      lcd.print(numLoad);
      lcd.println(" boxes loaded");
    }
    delay(100);
  }
  lcd.clear();
  lcd.println("Batch Loaded!");
  delay(1000);
}
