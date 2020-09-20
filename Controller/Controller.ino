#include "OTAServer.h"
#include "CommandController.h"
#include "MotorControl.h"
#include "Constants.h"

unsigned long previousMillis = 0; // will store last time LED was updated
const long interval = 1000;		  // interval at which to blink (milliseconds)


MotorControl motorController(StepperMotorPins(MOTOR_1_STEP,MOTOR_1_DIR),StepperMotorPins(MOTOR_2_STEP,MOTOR_2_DIR));
CommandController cmdController(&motorController);
OTAServer otaServer("esp32","gmhost2", "legokor12",&cmdController);

/* setup function */
void setup(void)
{
	pinMode(2, OUTPUT);
	motorController.begin(StepperModePins(MOTOR_MODE_0,MOTOR_MODE_1,MOTOR_MODE_2),ServoPins(SERVO_COLL),ServoPins(SERVO_DUMP));

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
		digitalWrite(2, not(digitalRead(2)));
	}
}