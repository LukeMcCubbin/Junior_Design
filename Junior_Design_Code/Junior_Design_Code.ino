// Junior Design Code

//Comments 
/*
 * Sections to write are 1. overall code, 2. Conveyor belt, 3. sensors, 4. XY  coordinate
 * 
 */

//Define 
#include <LiquidCrystal.h>
#include <Stepper.h>
#define bt_P A1 // Start Button
#define bt_L A2 // Stop Button

//LCD pins
int rs=31;
int en=33;
int d4=23;
int d5=25;
int d6=27;
int d7=29;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7); // define lcd

//DC
const int IN1 = 48;
const int IN2 = 50;
const int ENA = 52;

//Steppers
Stepper upStepper(stepsPerRevolution, 2, 3, 4, 5);
Stepper Stepper1(stepsPerRevolution, 6, 7, 8, 9);
Stepper Stepper2(stepsPerRevolution, 10, 11, 12, 13);

//Sensors
const int S = 33;

//Other
long duration; // variable for the duration of sound wave travel
int distance; 
int x = 0;
int read_ADC = 0;
int duty_cycle; // PWM
int duty_cycle_lcd;
int set = 1;
long randNumber;

//First Setup - On start
void setup(){
  Serial.begin(9600);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);
  
  pinMode(bt_P, INPUT_PULLUP);
  pinMode(bt_L, INPUT_PULLUP);
    
  //pinMode(trigPin, OUTPUT); 
  //pinMode(echoPin, INPUT);
    
// Guli -- lcd  
  lcd.begin(16,2);  
  lcd.setCursor(0,0);
  lcd.print("   Generating    ");
  lcd.setCursor(0,1);
  lcd.print("  Random Number   ");
  
// Guli -- Random Number Generator
//luke note: can we make this into a function?
  randomSeed(analogRead(0));
  randNumber = random(1, 9); // print a random number from 1 to 8
  delay(2000); 
  lcd.clear();
  lcd.print(randNumber);
  delay(2000); 
  lcd.clear();
}


void loop(){ 
  // Guli -- Control Buttons
  if(digitalRead (bt_P) == 0){set = 1;}
  if(digitalRead (bt_L) == 0){set = 0;}
  
  if(set==0){
    lcd.setCursor(0,0);
    lcd.print("     STOP      ");
    lcd.setCursor(0,1);
    digitalWrite(IN2, LOW);
  }
  
  if(set==1){ lcd.print("    START   ");
    digitalWrite(IN2, HIGH);           
  }
  delay(50);
//  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  analogWrite(ENA, 255); //control speed
  
    
    for(int i =0; i< 200; i++){
      Stepperx.step(1);
    delay(10);
    }

    delay(1000);

    //////////////Section for Luke
    //object oriented
    //Section 4 - XY cooridinate
    // control of one stepper motor

    /*
     * 
     * 

     * 
     * 
     * 
  for(int i =0; i< 200; i++){
    Stepperx.step(1);
    delay(10);
  }

delay(1000);

  
#include <Stepper.h>

// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 12, 11, 10, 9);


void setup()
{
 // set the speed at 20 rpm:
  myStepper.setSpeed(20);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() 
{
  // step one revolution in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
}
     */

    
   
}
