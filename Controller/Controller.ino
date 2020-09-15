#include <AccelStepper.h>
#include "Constants.h"

#define motorInterfaceType 1

AccelStepper stepperA = AccelStepper(motorInterfaceType, MOTOR_1_STEP, MOTOR_1_DIR);
AccelStepper stepperB = AccelStepper(motorInterfaceType, MOTOR_2_STEP, MOTOR_2_DIR);

void setup()
{
	pinMode(TIMEOUT_LED, OUTPUT);
	pinMode(LORA_LED, OUTPUT);
	pinMode(WS_LED, OUTPUT);

	pinMode(SERVO_DUMP, OUTPUT);
	pinMode(SERVO_COLL, OUTPUT);

	pinMode(MOTOR_1_STEP, OUTPUT);
	pinMode(MOTOR_1_DIR, OUTPUT);
	pinMode(MOTOR_2_STEP, OUTPUT);
	pinMode(MOTOR_2_DIR, OUTPUT);
	pinMode(MOTOR_MODE_0, OUTPUT);
	pinMode(MOTOR_MODE_1, OUTPUT);
	pinMode(MOTOR_MODE_2, OUTPUT);

	stepperA.setMaxSpeed(1000);
	stepperB.setMaxSpeed(1000);

	digitalWrite(TIMEOUT_LED, HIGH);
	digitalWrite(LORA_LED, HIGH);
	digitalWrite(WS_LED, HIGH);
	delay(500);
	digitalWrite(TIMEOUT_LED, LOW);
	digitalWrite(LORA_LED, LOW);
	digitalWrite(WS_LED, LOW);
	delay(500);
	digitalWrite(TIMEOUT_LED, HIGH);
	digitalWrite(LORA_LED, HIGH);
	digitalWrite(WS_LED, HIGH);
	delay(500);
}

void loop()
{
	stepperA.setSpeed(-1000);
	stepperB.setSpeed(1000);
	stepperA.runSpeed();
	stepperB.runSpeed();
}