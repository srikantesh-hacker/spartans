#include <SoftwareSerial.h>

SoftwareSerial scaleSerial(10, 11); 
const int tp = 8;                    //tp=trig pin
const int ep = 9;                    //ep=echo pin

void setup()
{
	Serial.begin(9600);
  	scaleSerial.begin(9600);
  	pinMode(tp, OUTPUT);
  	pinMode(eP, INPUT);
}

void loop()
{
	if (Serial.available()) 
  	{
    		String cmd = Serial.readStringUntil('\n');
    		if (cmd.startsWith("GET")) 
		{
      			float dist = measureDistance();
      			float wt = readWeight().toFloat();  
      			Serial.print("DIST:");
      			Serial.print(dist);
      			Serial.print(",WT:");
      			Serial.println(wt);
    		}
  	}
}

float measureDistance() 
{
	digitalWrite(tp, LOW); 
	delayMicroseconds(2);
	digitalWrite(tp, HIGH); 
	delayMicroseconds(10);
	digitalWrite(tp, LOW);
	long duration = pulseIn(ep, HIGH);
	return duration * 0.034 / 2.0; 
}

String readWeight() 
{
  	String buffer = "";
  	unsigned long startTime = millis();
  	while (millis() - startTime < 3000) 
	{
    		while (scaleSerial.available())
		{
      			char c = scaleSerial.read();
      			if (c == '\n' || c == '\r')
			{
        			buffer.trim(); 
        			return buffer;
      			}
			else 
			{
        			buffer += c;
      			}
    		}
  	}
  	return "0"; 
}
