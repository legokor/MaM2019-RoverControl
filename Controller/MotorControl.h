#ifndef MOTOR_CONTROL

#define MOTOR_CONTROL
#include <Arduino.h>


//typedef unsigned char uint8_t


//TODO: kiszedni define-okat
struct StepperMotor {
	int dirPin;
	int stepPin;
};

struct ServoMotor
{
	int signalPin;
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

	StepperMotor leftFront;
	StepperMotor rightFront;
	StepperMotor leftBack;
	StepperMotor rightBack;

	ServoMotor collector;
	ServoMotor dumper;

	void go(uint8_t angle, uint8_t dir, int maxFreq);

public:
	//TODO: alapértelmezett pinek
	MotorControl(StepperMotor leftFront = { 8,9 }, StepperMotor leftBack = { 8,9 }, StepperMotor rightFront = { 8,9 }, StepperMotor rightBack = { 8,9 }, ServoMotor collector = { 10 }, ServoMotor dumper = { 10 });

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
