#include "Motor.h"
#include "Sensor.h"

#define PIN_DES 10
#define PIN_SENS 9
#define MOTOR_NUM 4

#define Kp  0.1
#define Ki  0.1
#define Kd  0.1

int previousTime = 0;
int previousInput = 0;

AF_DCMotor motor(MOTOR_NUM);

int PID(int inputPID, double deltaT){
  double p = inputPID;
  double i = (inputPID - previousInput)*deltaT;
  double d = (inputPID - previousInput)/deltaT;
  previousInput = inputPID;
  return (Kp*p+Ki*i+Kd*d);
}

void PWM(int s){
  if(s>255){
    s=255;
  }else if(s<-255){
    s=-255;
  }
  
  if(s<0){
    motor.setSpeed(0);  
  }else{
    motor.setSpeed(s);
    motor.run(FORWARD);    
  }
}

void setup(){
    Serial.begin(9600);
}

void loop(){
  
  // Delta T
  int currentTime = millis(); 
  int deltaT = currentTime - previousTime;
  previousTime = currentTime;

  // PID
  int deseada = analogRead(PIN_DES);
  int dist = sensorRead(PIN_SENS);
  int inputPID = deseada - dist;
  int output = PID(inputPID, deltaT);

  // PWM
  PWM(output);
}
