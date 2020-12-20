#include "Sensor.h"

#define PIN_ECHO 15
#define PIN_TRIG 14
#define PIN_DES 16
#define PIN_PWM 9

#define Kp  0.66
#define Ki  0.43 
#define Kd  0.8

int previousTime = 0;
int input_priori = 0;
int i_priori = 0;
int bias = 150;

int PID(int inputPID, double deltaT){
  double p = inputPID;
  double i = i_priori + (inputPID + input_priori) * deltaT / 2.0;
  double d = (inputPID - input_priori)/deltaT;
  input_priori = inputPID;
  i_priori = i;
  double returnable = Kp*p+Ki*i+Kd*d+bias;
  if(returnable < 0 ) returnable = 0;
  else if(returnable > 255) returnable = 255;
  return returnable;
}


void setup(){
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    Serial.begin(9600);
}

double elapsed_time = 0;
int frame =0;
int deseada = 98;
int output = 0, dist = 0, inputPID =0;
void loop(){
  // Delta T  
  int currentTime = millis(); 
  double deltaT = (currentTime - previousTime) / 1000.0;
  previousTime = currentTime;
  elapsed_time += deltaT;
  
  if(elapsed_time > 9.0){
    frame += 1;

    if(frame == 0) deseada = 98;
    else if(frame == 1) deseada = 40;
    else if(frame == 2){
      deseada = 120;
      frame = -1;
    }
    elapsed_time = 0;
  }
  // PID
//  deseada = 90; //el final del tubo tiene dist ~= 168
  dist = sensorRead(PIN_ECHO, PIN_TRIG);
  inputPID = -deseada + dist;
  output = PID(inputPID, deltaT);

  // PWM
  analogWrite(PIN_PWM, output);
  Serial.print("frame: ");
  Serial.println(frame);
  Serial.print("Dist: ");
  Serial.print(dist);
  Serial.print(", ");
  Serial.print("Output: ");
  Serial.print(output);
  Serial.print("\n");
}
