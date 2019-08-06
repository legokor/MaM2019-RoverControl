/*
 Name:		Controller.ino
 Created:	2019-05-09 00:46:25
 Author:	izsoandras
*/
#include <ESPmDNS.h>
#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>
#include "MotorControl.h"


#define LoRa_MISO 19
#define LoRa_MOSI 23
#define LoRa_SCK 18
#define LoRa_RST 14
#define LoRa_DIO0 2
#define LoRa_NSS 5

char cmd[4];
uint8_t angle;
MotorControl mc;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
//	LoRa.setPins(LoRa_NSS, LoRa_RST, LoRa_DIO0);
	cmd[3] = '\0';

	/*while(!LoRa.begin(866E6))
	{
		Serial.println("Couldn't find LoRa");
		delay(500);
	}
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa set up succesful");*/

}

// the loop function runs over and over again until power down or reset
void loop() {
	/*if (LoRa.parsePacket()) {
		for (int i = 0; i < 3; i++) {
			cmd[i] = (char)LoRa.read();
		}*/
	if(Serial.available()){
		Serial.readBytes(cmd,3);
		Serial.readBytes(&angle, 1);
		Serial.print("Command received: ");
		Serial.print(cmd);
		Serial.print(" with parameter: ");
		Serial.println(angle);
		
		if (strcmp(cmd, "MFH") == 0)
			mc.forwardHighSpeed(angle);
		else if (strcmp(cmd, "MFL") == 0)
			mc.forwardLowSpeed(angle);
		else if (strcmp(cmd, "MBH") == 0)
			mc.backwardHighSpeed(angle);
		else if (strcmp(cmd, "MBL") == 0)
			mc.backwardLowSpeed(angle);
		else if (strcmp(cmd, "COL") == 0)
			mc.collect(angle);
		else if (strcmp(cmd, "DMP") == 0)
			mc.dump(angle);
		else if (strcmp(cmd, "STO") == 0 && angle == 'P')
			mc.stop();
	}
}
