
#include "Sensor.h"
#include "Arduino.h"

#define maxHcm  50

int sensorRead(int pin_echo, int pin_trig){

  // Short Pulse
  digitalWrite(pin_trig, LOW);
  delayMicroseconds(5);
  digitalWrite(pin_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig, LOW);

  // Read
  int usDuration = pulseIn(pin_echo, HIGH);

  // Convert to cm
  // Speed of sound  340 m/s = 29 us/cm.
  // Ultrasonic sound travels to ball and back, so we divide distance in half.
  double cm = usDuration / 29.0 / 2.0;
  return (cm*255)/50.0;
}
//  Serial.print("Distance = ");
//  Serial.print(distance);
//  Serial.println(" cm");
