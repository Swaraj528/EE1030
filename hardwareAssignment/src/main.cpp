#include "Arduino.h"

void setup() { 
	Serial.begin(9600);
}

void loop() { 
	int sensorValue = analogRead(A0);
	float voltage = (5.0000*sensorValue/1023.0000);
	Serial.print(voltage,4);
	Serial.print(" ");
	Serial.print(sensorValue);
	Serial.print("\n");
	delay(1000);
}
