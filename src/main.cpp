//Created by Samson Hua, Version 1.0.0

//Import SpeedyStepper, Servo Library & Fast LED Library
#include <Arduino.h>
#include <SpeedyStepper.h>
#include <Servo.h>
#include <FastLED.h>


//Global Homing Variables
const float homingSpeedInSteps = 200;
const float maxHomingDistanceInSteps = 1550;
const int directionTowardHome = -1;

//Define numbers for LEDs
const int NUM_LEDS = 4;
const int LED_PIN = 10;
const int LED_PIN2 = 11;
const int brightness = 255;

//LED Assignments
CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS];

//Pin Assignments
const int MOTOR_STEP_PIN = 3;
const int MOTOR_DIRECTION_PIN = 2;
const int ARM_SERVO_PIN = 9;
const int UP_Position = 0;
const int DOWN_Position = 160;
const int LIMIT_SWITCH = 13;

void moveServoUp(Servo servo){
  servo.write(UP_Position);
}

void moveServoDown(Servo servo){
  servo.write(DOWN_Position);
}

void FlashLedsGreen(CRGB led[], CRGB led2[]){
  
  for(int i = 0; i < 2; i++){
  led[0] = CRGB(0, 255, 0);
  led[1] = CRGB(0, 255, 0);
  led[2] = CRGB(0, 255, 0);
  led[3] = CRGB(0, 255, 0);
  led2[0] = CRGB(0, 255, 0);
  led2[1] = CRGB(0, 255, 0);
  led2[2] = CRGB(0, 255, 0);
  led2[3] = CRGB(0, 255, 0);
  FastLED.show();
  delay(100);

  FastLED.clear();
  FastLED.show();
  delay(100);
  }


  led[0] = CRGB(255,0,0);
  led[1] = CRGB(255,0,0);
  led[2] = CRGB(255,0,0);
  led[3] = CRGB(255,0,0);
  led2[0] = CRGB(255,0,0);
  led2[1] = CRGB(255,0,0);
  led2[2] = CRGB(255,0,0);
  led2[3] = CRGB(255,0,0);
  FastLED.show();
}

void FlashLedsBlue(CRGB led[], CRGB led2[]){
  
  for(int i = 0; i < 2; i++){
  led[0] = CRGB(0, 128, 255);
  led[1] = CRGB(0, 128, 255);
  led[2] = CRGB(0, 128, 255);
  led[3] = CRGB(0, 128, 255);
  led2[0] = CRGB(0, 128, 255);
  led2[1] = CRGB(0, 128, 255);
  led2[2] = CRGB(0, 128, 255);
  led2[3] = CRGB(0, 128, 255);
  FastLED.show();
  delay(100);

  FastLED.clear();
  FastLED.show();
  delay(100);
  }


  led[0] = CRGB(255,0,0);
  led[1] = CRGB(255,0,0);
  led[2] = CRGB(255,0,0);
  led[3] = CRGB(255,0,0);
  led2[0] = CRGB(255,0,0);
  led2[1] = CRGB(255,0,0);
  led2[2] = CRGB(255,0,0);
  led2[3] = CRGB(255,0,0);
  FastLED.show();
}


//Booleans
//Manual Mode to debug certan commands
bool ManualModeEnabled = true;

//String
int ManualResponse;
int ManualResponse2;

//Creating Servo & Stepper Object
Servo arm_servo;
SpeedyStepper x_stepper;

//=====================================================//
void setup() {

//Declaring PinModes
pinMode(LIMIT_SWITCH, INPUT);

//Start LEDs
FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
FastLED.addLeds<WS2812B, LED_PIN2, GRB>(leds2, NUM_LEDS);

//Program Start LED Sequence
leds[0] = CRGB(255,0,0);
leds[1] = CRGB(255,0,0);
leds[2] = CRGB(255,0,0);
leds[3] = CRGB(255,0,0);
FastLED.setBrightness(brightness/5);
FastLED.show();
              

leds2[0] = CRGB(255,0,0);
leds2[1] = CRGB(255,0,0);
leds2[2] = CRGB(255,0,0);
leds2[3] = CRGB(255,0,0);

FastLED.show();
delay(500);




//Attach Servo
arm_servo.attach(ARM_SERVO_PIN);
moveServoUp(arm_servo);

//Select default Baud Raid
Serial.begin(9600);

//Connect Stepper Pins
x_stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);

//Sequence to bring stepper to the beginnin g end of linear rail
//Initial Stepper Speed
x_stepper.setSpeedInStepsPerSecond(500);
x_stepper.setAccelerationInStepsPerSecondPerSecond(400);

//Homing Sequence
leds2[0] = CRGB(225,221,0);
leds2[1] = CRGB(225,221,0);
leds2[2] = CRGB(225,221,0);
leds2[3] = CRGB(225,221,0);
FastLED.show();
x_stepper.moveToHomeInSteps(directionTowardHome, homingSpeedInSteps, maxHomingDistanceInSteps, LIMIT_SWITCH);
Serial.print("[Homing.. Please Wait..] \n");
leds2[0] = CRGB(255,0,0);
leds2[1] = CRGB(255,0,0);
leds2[2] = CRGB(255,0,0);
leds2[3] = CRGB(255,0,0);
FastLED.show();
delay(300);


//Moving Stepper
leds[0] = CRGB(0,255,0);
leds[1] = CRGB(0,255,0);
leds[2] = CRGB(0,255,0);
leds[3] = CRGB(0,255,0);
FastLED.show();
x_stepper.moveRelativeInSteps(1550);
leds[0] = CRGB(255,0,0);
leds[1] = CRGB(255,0,0);
leds[2] = CRGB(255,0,0);
leds[3] = CRGB(255,0,0);
FastLED.show();



delay(100);
leds2[0] = CRGB(0,255,0);
leds2[1] = CRGB(0,255,0);
leds2[2] = CRGB(0,255,0);
leds2[3] = CRGB(0,255,0);
FastLED.show();
x_stepper.moveRelativeInSteps(-800);
leds2[0] = CRGB(255,0,0);
leds2[1] = CRGB(255,0,0);
leds2[2] = CRGB(255,0,0);
leds2[3] = CRGB(255,0,0);
FastLED.show();
delay(500);


//Test Servo Motor
moveServoDown(arm_servo);
//Flash LEDs Green to indicate down
FlashLedsGreen(leds, leds2);
delay(1000);
moveServoUp(arm_servo);
//Flash LEDs Blue to indicate down
FlashLedsBlue(leds, leds2);

//If manual mode is enabled, prompt a command
if(ManualModeEnabled){
  Serial.println("What command would you like to execute? \n[1] MOVE STEPPER\n[2]SERVO UP\n[3]SERVO DOWN]\n[4]HOMING SEQUENCE");
}


}




void loop() {


while(ManualModeEnabled){

      if (Serial.available()){
        ManualResponse = Serial.parseInt();

        switch(ManualResponse){

          case 1 :
                Serial.println("Moving Stepper, Please Select Relative Position");
                delay(1000);
                Serial.flush();
                while (Serial.available()==0) {
                }
                ManualResponse2 = Serial.parseInt();
                x_stepper.moveRelativeInSteps(ManualResponse2);
                break;
          

          case 2 :
                Serial.println("Moving Servo Up");
                moveServoUp(arm_servo);
                break;
          
          
                
          case 3 :
                Serial.println("Moving Servo Down");
                moveServoDown(arm_servo);
                break;
          case 4:

                //Set homing speed


                
                Serial.println("Homing..");
                leds2[0] = CRGB(225,221,0);
                leds2[1] = CRGB(225,221,0);
                leds2[2] = CRGB(225,221,0);
                leds2[3] = CRGB(225,221,0);
                FastLED.show();
                x_stepper.moveToHomeInSteps(directionTowardHome, homingSpeedInSteps, maxHomingDistanceInSteps, LIMIT_SWITCH);
                Serial.print("[Homing.. Please Wait..] \n");
                leds2[0] = CRGB(255,0,0);
                leds2[1] = CRGB(255,0,0);
                leds2[2] = CRGB(255,0,0);
                leds2[3] = CRGB(255,0,0);
                FastLED.show();
                delay(300);
                break;
        }
        Serial.println("What command would you like to execute? \n 1. [1] MOVE_STEPPER, [2]SERVO_UP, [3]SERVO_DOWN]");
      }
      
  }
  
  delay(1000);
}






