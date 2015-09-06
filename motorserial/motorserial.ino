/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 

#define REST_COMMAND 0
#define FIST_COMMAND 1
#define WAVE_IN_COMMAND 2
#define WAVE_OUT_COMMAND 3
#define FINGERS_SPREAD_COMMAND 4
#define DOUBLE_TAP_COMMAND 5
#define UNKNOWN_COMMAND 6

#define SERVO_1_PIN 9  // horizontal (bottom) motor [0, 180]
#define SERVO_1_MIN 0
#define SERVO_1_MAX 180
#define SERVO_1_STEP 20

#define SERVO_2_PIN 10 // vertical (upper) motor [0, 30]
#define SERVO_2_MIN 0
#define SERVO_2_MAX 30
#define SERVO_2_STEP 10

Servo servo1;
Servo servo2;

int controlled_motor = 1;
int servo_1_deg = 0;
int servo_2_deg = 0;
 
void setup() 
{ 
  Serial.begin(9600);
  
  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);
  
  moveMotor1(0);
  moveMotor2(0);
} 

void moveMotor1(int deg)
{
  servo_1_deg += deg;
  
  if (servo_1_deg < SERVO_1_MIN)
    servo_1_deg = SERVO_1_MIN;
  else if (servo_1_deg > SERVO_1_MAX)
    servo_1_deg = SERVO_1_MAX;
  
  servo1.write(servo_1_deg);
}

void moveMotor2(int deg)
{
  servo_2_deg += deg;
  
  if (servo_2_deg < SERVO_2_MIN)
    servo_2_deg = SERVO_2_MIN;
  else if (servo_2_deg > SERVO_2_MAX)
    servo_2_deg = SERVO_2_MAX;
  
  servo2.write(servo_2_deg);
}

void loop() 
{ 
  if (Serial.available()) {
    int command = Serial.read();
    
    switch (command)
    {
      case REST_COMMAND:
        break;
      
      case FIST_COMMAND:
        Serial.println("Fist");
        
        if (controlled_motor == 1)
        {
          controlled_motor = 2;
          Serial.println("Controlled motor: 2");
        }
        else if (controlled_motor == 2)
        {
          controlled_motor = 1;
          Serial.println("Controlled motor: 1");
        }
        
        break;
      
      case WAVE_IN_COMMAND:
        Serial.println("Wave in");
        
        if (controlled_motor == 1)
          moveMotor1(-SERVO_1_STEP);
        else if (controlled_motor == 2)
          moveMotor2(-SERVO_2_STEP);
          
        break;
        
      case WAVE_OUT_COMMAND:
        Serial.println("Wave out");

        if (controlled_motor == 1)
          moveMotor1(SERVO_2_STEP);
        else if (controlled_motor == 2)
          moveMotor2(SERVO_2_STEP);

        break;
      
      case FINGERS_SPREAD_COMMAND:
        break;
        
      case DOUBLE_TAP_COMMAND:
        break; 
       
      case UNKNOWN_COMMAND:
        Serial.write("Unknown command");
        break;
      
      default:
        Serial.write("Received other: ");
        Serial.println(command);
        break;
    }
  }
  
} 

