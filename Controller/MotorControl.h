#ifndef MOTOR_CONTROL

#define MOTOR_CONTROL
#include <Arduino.h>
#include <AccelStepper.h>
#include <ESP32Servo.h>


//TODO: kiszedni define-okat
struct StepperMotorPins {
	int dirPin;
	int stepPin;
	StepperMotorPins(int stepPin,int dirPin) : stepPin(stepPin), dirPin(dirPin){}
};

struct ServoPins
{
	int signalPin;
	ServoPins(int signalPin): signalPin(signalPin){}
};

struct StepperModePins
{
	int m0;
	int m1;
	int m2;
	StepperModePins(int m0, int m1, int m2) : m0(m0), m1(m1), m2(m2) {}
};


class MotorControl {
	const int pwmChannelLeft = 0;
	const int pwmChannelRight = 1;
	const int pwmChannelDumper = 2;
	const int pwmChannelCollector = 3;
	//Kérdés: freq-ból állítsuk a sebességet, vagy a pin-es osztóval?
	const int pwmStepFastFreq = 2000;
	const int pwmStepSlowFreq = 1000;
	const int pwmServoFreq = 500;

	AccelStepper * leftStepper;
	AccelStepper * rightStepper;

	Servo * collectorServo;
	Servo * dumperServo;

	void go(uint8_t angle, uint8_t dir, int maxFreq);

public:
	//TODO: alapértelmezett pinek
	MotorControl(StepperMotorPins left, StepperMotorPins right);
	~MotorControl();

	void begin(StepperModePins modePins, ServoPins collector, ServoPins dumper);

	void forwardHighSpeed(uint8_t angle);
	void forwardLowSpeed(uint8_t angle);
	void backwardHighSpeed(uint8_t angle);
	void backwardLowSpeed(uint8_t angle);
	void collect(uint8_t angle);
	void dump(uint8_t angle);
	//Kérdés: stop-nál servo-k 0-ra, vagy tartsák meg a jelenlegi állapotot?
	void stop();
};

#endif // !MOTOR_CONTROL
