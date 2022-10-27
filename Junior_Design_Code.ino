// Junior Design Code

//Comments 
/*
 * Sections to write are 1. overall code, 2. Conveyor belt, 3. sensors, 4. XY  coordinate
 * 
 */

#include <LiquidCrystal.h>
#define bt_P A1 // Start Button
#define bt_L A2 // Stop Button
#define echoPin 12 // Sensor Pins
#define trigPin 13

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // define lcd
const int IN1 = 10;// DC Motor Control
const int IN2 = 11;
const int ENA = 9; // DC Motor Speed Control
long duration; // variable for the duration of sound wave travel
int distance; 
int x = 0;

int read_ADC = 0;
int duty_cycle; // PWM
int duty_cycle_lcd;
int set = 1;
long randNumber;


void setup(){
  Serial.begin(9600);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);
  
  pinMode(bt_P, INPUT_PULLUP);
  pinMode(bt_L, INPUT_PULLUP);
    
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
    
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
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  analogWrite(ENA, 255); //control speed
  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.println(" cm");
  
  // Guli -- Sensor (For ultrasonic sensor, please ignore)
    if(distance < 30){
      analogWrite(ENA, 100);
      x = x + 1;
      delay(50);
      if(x == randNumber){
        lcd.clear();
        randNumber = random(1, 9);
        lcd.print("  New Number   ");
        lcd.print(randNumber);
        delay(2000); 
        lcd.clear();
        x = 0;
        delay(2000);
      }
    }

    //////////////Section for Luke
    //object oriented
    //Section 4 - XY cooridinate
    // control of one stepper motor

    /*
     * 
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
