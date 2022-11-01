#include <Stepper.h>

// C++ code
//
const int stepPerRevolution=200; 

Stepper Stepperx(stepPerRevolution, 5,11,2,8);
int stepCount = 0; 
void setup() {

Serial.begin(9600);
}
void loop() {

for(int i =0; i< 200; i++){
  Stepperx.step(1);
  delay(10);
}

delay(1000);

}
