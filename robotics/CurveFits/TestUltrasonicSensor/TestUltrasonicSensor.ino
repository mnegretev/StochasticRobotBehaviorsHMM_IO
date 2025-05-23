/*************************************************************************
* File Name          : TestUltrasonicSensor.ino
* Author             : Steve
* Updated            : Steve
* Version            : V1.0.0
* Date               : 2/22/2013
* Description        : Test for Makeblock Electronic modules of Me - 
                       Ultrasonic Sensor. The module can ONLY be connected 
                       to the PORT_3, PORT_4, PORT_5, PORT_6, PORT_7, 
                       PORT_8 of Me - Base Shield. 
* License            : CC-BY-SA 3.0
* Copyright (C) 2013 Maker Works Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

Me7SegmentDisplay disp(PORT_6);
int i=0;
float distance=0;


MeUltrasonicSensor ultraSensor(PORT_4); //Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield.
                                    
void setup()
{
	Serial.begin(9600);

}

void loop()
{
	//Serial.print("Distance : ");
        distance = ultraSensor.distanceCm();
        distance = distance * 10.;
        Serial.println(distance);
	//Serial.println(" cm");
	delay(100);// the minimal measure interval is 100 milliseconds
        disp.display(distance);
        //disp.display(i++);


}

