
#include "Sensor.h"
#include "Arduino.h"

#define maxHcm  50

int sensorRead(int pin){
  pinMode(pin, OUTPUT);

  // Short Pulse
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);

  // Read
  pinMode(pin, INPUT);
  int usDuration = pulseIn(pin, HIGH);

  // Convert to cm
  // Speed of sound  340 m/s = 29 us/cm.
  // Ultrasonic sound travels to ball and back, so we divide distance in half.
  double cm = usDuration / 29.0 / 2.0;
  return (cm*255)/50.0;
}
