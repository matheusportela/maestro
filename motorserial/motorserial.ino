/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 

#define FIST_COMMAND 1
#define WAVE_IN_COMMAND 2
#define WAVE_OUT_COMMAND 3

Servo servo1; // horizontal (bottom) motor
Servo servo2; // vertical (upper) motor
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object 
//  servo2.attach(10);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
} 
 
void loop() 
{ 
  if (Serial.available()) {
    int pos = Serial.read();
    
    switch (pos)
    {
      case FIST_COMMAND:
        Serial.println("Fist");
        break;
      
      case WAVE_IN_COMMAND:
        Serial.println("Wave in");
        servo1.write(0);
        break;
        
      case WAVE_OUT_COMMAND:
        Serial.println("Wave out");
        servo1.write(90);
        break;
      
      default:
        Serial.write("Received other: ");
        Serial.println(pos);
        break;
    }
  }
  
} 

