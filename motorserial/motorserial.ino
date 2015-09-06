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

#define CAMERA_0_SERVO_1_PIN 9  // horizontal (bottom) motor [0, 180]
#define CAMERA_0_SERVO_2_PIN 10 // vertical (upper) motor [0, 30]
#define CAMERA_1_SERVO_1_PIN 11  // horizontal (bottom) motor [0, 180]
#define CAMERA_1_SERVO_2_PIN 12 // vertical (upper) motor [0, 30]

#define SERVO_1_STEP 45
#define SERVO_2_STEP 15

#define NUM_CAMERAS 2

Servo servo1[NUM_CAMERAS];
Servo servo2[NUM_CAMERAS];

int controlled_camera = 1;
int controlled_motor = 2;
int servo_1_deg[NUM_CAMERAS] = {0, 0};
int servo_2_deg[NUM_CAMERAS] = {0, 0};
int servo_1_min[NUM_CAMERAS] = {0, 0};
int servo_2_min[NUM_CAMERAS] = {0, 70};
int servo_1_max[NUM_CAMERAS] = {180, 180};
int servo_2_max[NUM_CAMERAS] = {30, 100};
 
void setup() 
{ 
  Serial.begin(9600);
  
  servo1[0].attach(CAMERA_0_SERVO_1_PIN);
  servo2[0].attach(CAMERA_0_SERVO_2_PIN);
  servo1[1].attach(CAMERA_1_SERVO_1_PIN);
  servo2[1].attach(CAMERA_1_SERVO_2_PIN);
  
  int i;
  for (i = 0; i < NUM_CAMERAS; i++)
  {
    controlled_camera = 0;
    moveMotor1(0);
    moveMotor2(0);
  }
} 

void moveMotor1(int deg)
{
  servo_1_deg[controlled_camera] += deg;
  
  if (servo_1_deg[controlled_camera] < servo_1_min[controlled_camera])
    servo_1_deg[controlled_camera] = servo_1_min[controlled_camera];
  else if (servo_1_deg[controlled_camera] > servo_1_max[controlled_camera])
    servo_1_deg[controlled_camera] = servo_1_max[controlled_camera];
  
  servo1[controlled_camera].write(servo_1_deg[controlled_camera]);
}

void moveMotor2(int deg)
{
  servo_2_deg[controlled_camera] += deg;
  
  if (servo_2_deg[controlled_camera] < servo_2_min[controlled_camera])
    servo_2_deg[controlled_camera] = servo_2_min[controlled_camera];
  else if (servo_2_deg[controlled_camera] > servo_2_max[controlled_camera])
    servo_2_deg[controlled_camera] = servo_2_max[controlled_camera];
  
  servo2[controlled_camera].write(servo_2_deg[controlled_camera]);
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
          moveMotor1(SERVO_1_STEP);
        else if (controlled_motor == 2)
          moveMotor2(SERVO_2_STEP);

        break;
      
      case FINGERS_SPREAD_COMMAND:
        if (controlled_camera == 0)
        {
          controlled_camera = 1;
          Serial.println("Controlled camera: 1");
        }
        else if (controlled_camera == 1)
        {
          controlled_camera = 0;
          Serial.println("Controlled camera: 0");
        }
        
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

