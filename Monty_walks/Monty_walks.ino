#include <Servo.h> 
#include <US.h>
#include <Ultrasonic.h>

Ultrasonic ultrasonic(8, 9);

Servo leftFoot;
Servo rightFoot;
Servo leftLeg;
Servo rightLeg;

#define PIN_YL 2 //servo[2]
#define PIN_YR 3 //servo[3]
#define PIN_RL 4 //servo[4]
#define PIN_RR 5 //servo[5]

/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2 yaw left
         --------------- 
            ||     ||
RR 5==>   -----   ------  <== RL 4 roll left

*/

int mostRecent;
// 1- forward
// 2 - left
// 3 = right

void setup() {
  leftFoot.attach(PIN_RL);
  rightFoot.attach(PIN_RR);
  leftLeg.attach(PIN_YL);
  rightLeg.attach(PIN_YR);

  Serial.begin(9600);
}

void loop() {
   detect();
}

void detect() {
  int distance = ultrasonic.read();
  if(distance <= 10) {
    goBack();
    if(mostRecent == 2) {
      for(int i = 0; i < 2; i++){
        turnRight();
      }
    } else
      if(mostRecent == 3) {
        for(int i = 0; i < 2; i++){
          turnLeft();
        }
      } else {
        turnLeft();
      }
  } else {
    goForward();
  }
}

void goBack() {
  rightStepBack();
  leftStepBack();
  detect();
}

void goForward() {
  mostRecent = 1;
  rightStepForward();
  leftStepForward();
  Serial.println("detect: ");
}

void turnLeft() {
  mostRecent = 2;
  for(int i = 0; i < 3; i++){
    rightFoot.write(30);
    leftFoot.write(45);
    delay(1000);
    for(int i=90; i<135; i+=5){
      leftLeg.write(i);
      delay(100);
    }
    delay(1000);
    rightFoot.write(90);
    leftFoot.write(90);
    delay(1000);
  
  
    leftFoot.write(120);
    rightFoot.write(135);
    delay(1000);
    leftLeg.write(90);
    delay(1000);
    leftFoot.write(90);
    rightFoot.write(90);  
  }
}

void turnRight() {
  mostRecent = 3;
  for(int i = 0; i < 3; i++){
    leftFoot.write(120);
  
    delay(1000);
    rightFoot.write(100);
    delay(1000);
    for(int i=90; i>35; i-=5){
      rightLeg.write(i);
      delay(100);
    }
    delay(1000);
    rightFoot.write(90);
    leftFoot.write(90);
    delay(1000);
  
  
    rightFoot.write(30);
    leftFoot.write(45);
    delay(1000);
    rightLeg.write(90);
    delay(1000);
    leftFoot.write(90);
    rightFoot.write(90);  
  }
}

void rightStepBack() {
  rightFoot.write(25);
  delay(150);
  leftLeg.write(135);
  delay(150);
  rightFoot.write(90);
  delay(150);
  leftLeg.write(90);
  delay(150);
}

void leftStepBack() {
  leftFoot.write(115);
  delay(150);
  rightLeg.write(45);
  delay(150);
  leftFoot.write(90);
  delay(150);
  rightLeg.write(90);
  delay(150);
}


void rightStepForward() {
  rightFoot.write(25);
  delay(150);
  leftLeg.write(45);
  delay(150);
  rightFoot.write(90);
  delay(150);
  leftLeg.write(90);
  delay(150);
}


void leftStepForward() {
  leftFoot.write(115);
  delay(150);
  rightLeg.write(135);
  delay(150);
  leftFoot.write(90);
  delay(150);
  rightLeg.write(90);
  delay(150);
}
