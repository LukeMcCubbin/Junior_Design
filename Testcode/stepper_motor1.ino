#include <Stepper.h>

// C++ code
//
const int stepPerRevolution=200; 

Stepper Stepperx(stepPerRevolution, 5,11,2,8);
//Stepper Steppery(stepPerRevolution, 3,6,9,12);
//Stepper Stepperz(stepPerRevolution, 4,7,10,13);
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
//Stepperx.step(400);
//Steppery.step(1);
//Stepperz.step(1);  

//stepCount++;
//delay(10);
//Stepperx.step(-1);
//delay(10);

}
