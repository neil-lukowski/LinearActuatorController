/*
 * Linear Actuator Controller
 * Version 1
 * Created: 7/2/2021
 * Author: Neil Lukowski
 * 
 * Version  1.0 - 	Reads a sensor (potientometer) input for a user-selected speed.
 *					Sends a linear actuator in a direction at the selected speed 
 * 					until a limit switch is actuated and reverses the direction.
 */

 #include <Arduino.h>

void dirGoIn();
void dirGoOut();
void getVal();

int sensorValue = 0;
int outputValue = 0;
int fwdValue = 0;
int revValue = 0;
int dir = 0;
//int currSw = 0;
//int lastSw = 0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(38400);
  Serial.flush();
}

void loop()
{
  if (digitalRead(2) == HIGH && digitalRead(3) == LOW){
    dirGoIn();
    getVal();
  }
  if (digitalRead(3) == HIGH && digitalRead(2) == LOW){
    dirGoOut();
    getVal();
  }
  
  if (dir == 0)
  {
    Serial.write(fwdValue);
  }
  else
  {
    Serial.write(revValue);
  }
  delay(100);
}

void dirGoIn(){
  
    dir = 1;
}

void dirGoOut(){
  
    dir = 0;
}

void getVal(){
  sensorValue = analogRead(A0);
  outputValue = map(sensorValue, 1, 1023, 1, 63);
  fwdValue = 64 + outputValue;
  revValue = 64 - outputValue;

  //Serial.print(revValue);
}
