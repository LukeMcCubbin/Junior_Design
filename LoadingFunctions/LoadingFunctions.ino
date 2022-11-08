#include <LiquidCrystal.h>
#include <Stepper.h>
#define sensor1 51
#define sensor2 53
#define DCMotor 48
#define DCEnable 50
LiquidCrystal lcd(23, 25, 27 29, 31, 33);

int onPallet = 0; //the number of boxes on he pallet
long batchSize;
int stepsPerRevolution = 200;
Stepper upStepper(stepsPerRevolution, 2, 3, 4, 5);

//Function definitions
void StartBatch(long* randNum, LiquidCrystal lcd);
void LoadProcess(int sensor, int motor, int batchSize, LiquidCrystal lcd);
void ReadyBatch(int sensor, int motor);
void LoadBox(int sensor, int motor, int *numOnPallet);

void setup() {
  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor2, INPUT_PULLUP);
  pinMode(DCMotor, OUTPUT);
  pinMode(DCEnable, OUTPUT);
  digitalWrite(DCEnable, HIGH);
}

void loop() {
  StartBatch(&batchSize, lcd);
  LoadProcess(sensor1, DCMotor, batchSize, lcd);
  ReadyBatch(sensor2, DCMotor);
  delay(5000);
}
void StartBatch(long* randNum, LiquidCrystal lcd){
  randomSeed(analogRead(A0));
  *randNum = random(1, 9);
  delay(200);
  lcd.clear();
  lcd.print("Please load: ");
  lcd.println(*randNum);
}

void LoadProcess(int sensor, int motor, int batchSize, LiquidCrystal lcd){
  //Function goes through process to load batch onto conveyor
  int prevSensor = digitalRead(sensor);
  int numLoad = 0;
  delay(200);
  lcd.clear();
  lcd.print(numLoad);
  lcd.println(" boxes loaded");
  while(numLoad < batchSize){
    if(prevSensor == HIGH && digitalRead(sensor) == LOW){
      //On beam break
      digitalWrite(motor, HIGH);
    }
    if(prevSensor == LOW && digitalRead(sensor) == HIGH){
      //On beam-restore
      //delay here to create a greater gap between boxes 
      digitalWrite(motor, LOW);
      numLoad++;//Once beam is cleared the box is loaded and incremented
      lcd.clear();
      lcd.print(numLoad);
      lcd.println(" boxes loaded");
    }
    prevSensor = digitalRead(sensor);
    delay(100);
  }
  lcd.clear();
  lcd.println("Batch Loaded!");
  delay(1000);
}

void ReadyBatch(int sensor, int motor){
  //This function readies the batch for dropping onto pallet
  digitalWrite(motor, HIGH);
  while(digitalRead(sensor) == HIGH){
    //Move until beam breaks
    delay(100);
  }
  digitalWrite(motor, LOW);
}

void LoadBox(int sensor, int motor, int *numOnPallet){
  //Drop box through chute onto pallet
  int prev = digitalRead(sensor);
  digitalWrite(motor, HIGH);
  while( prev == LOW || digitalRead(sensor) == HIGH){
    //while the beam isn't broken 
    delay(10);
  }
  digitalWrite(motor, LOW);
  *numOnPallet++;
}
