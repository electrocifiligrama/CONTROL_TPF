#include "Motor.h"
#include "Sensor.h"

#define MOTOR_NUM 4
#define PIN_TRIG 2
#define PIN_ECHO 3

#define Kp  0.1
#define Ki  0
#define Kd  0

int previousTime = 0;
int input_priori = 0;
int i_priori = 0;
int bias = 0;

AF_DCMotor motor(MOTOR_NUM);

int PID(int inputPID, double deltaT){
  double p = inputPID;
  double i = i_priori+(inputPID - input_priori)*deltaT;
  double d = (inputPID - input_priori)/deltaT;
  input_priori = inputPID;
  i_priori = i;
  return (Kp*p+Ki*i+Kd*d+bias);
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
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    Serial.begin(9600);
}

void loop(){
  
  // Delta T
  int currentTime = millis(); 
  int deltaT = currentTime - previousTime;
  previousTime = currentTime;

  // PID
  int deseada = 50;//analogRead(PIN_DES);
  int dist = sensorRead(PIN_ECHO, PIN_TRIG);
  int inputPID = deseada - dist;
  int output = PID(inputPID, deltaT);

  // PWM
  PWM(output);
}
