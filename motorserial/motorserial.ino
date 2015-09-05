/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo servo1;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
Servo servo2;
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object 
  servo2.attach(10);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
} 
 
void loop() 
{ 
  if (Serial.available()) {
    int pos = Serial.read();
    Serial.write(pos);
    servo1.write(pos);
  }
  
} 

