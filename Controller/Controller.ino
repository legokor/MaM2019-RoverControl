#include "OTAServer.h"
#include "CommandController.h"
#include "MotorControl.h"

//variabls for blinking an LED with Millis
const int led = 2;				  // ESP32 Pin to which onboard LED is connected
unsigned long previousMillis = 0; // will store last time LED was updated
const long interval = 1000;		  // interval at which to blink (milliseconds)
int ledState = LOW;				  // ledState used to set the LED

MotorControl motorController;
CommandController cmdController(&motorController);
OTAServer otaServer("esp32","gmhost2", "legokor12",&cmdController);

/* setup function */
void setup(void)
{
	pinMode(led, OUTPUT);
	Serial.begin(115200);

	// Connect to WiFi network
	otaServer.begin();
	otaServer.addRoutes();
	otaServer.startWebServer();
}

void loop(void)
{
	otaServer.handleClient();
	delay(1);

	//loop to blink without delay
	unsigned long currentMillis = millis();
	if (currentMillis - previousMillis >= interval)
	{
		// save the last time you blinked the LED
		previousMillis = currentMillis;
		// if the LED is off turn it on and vice-versa:
		ledState = not(ledState);
		// set the LED with the ledState of the variable:
		digitalWrite(led, ledState);
	}
}