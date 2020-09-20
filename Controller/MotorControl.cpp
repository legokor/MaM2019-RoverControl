#include "MotorControl.h"

#define FORWARD 1   //HIGH
#define BACKWARD -1  //LOW
#define motorInterfaceType 1

MotorControl::MotorControl(StepperMotorPins left, StepperMotorPins right){
    this->leftStepper = new AccelStepper(motorInterfaceType, left.stepPin, left.dirPin);
    this->rightStepper = new AccelStepper(motorInterfaceType, right.stepPin, right.dirPin);
    
    this->leftStepper->setMaxSpeed(this->pwmStepFastFreq);
    this->rightStepper->setMaxSpeed(this->pwmStepFastFreq);

    this->dumperServo = new Servo();
    this->collectorServo = new Servo();
    
}
MotorControl::~MotorControl(){
    delete this->leftStepper;
    delete this->rightStepper;
    delete this->dumperServo;
    delete this->collectorServo;
}

void MotorControl::begin(StepperModePins modePins, ServoPins collector, ServoPins dumper)
{
    this->dumperServo->attach(dumper.signalPin);
    this->collectorServo->attach(collector.signalPin);
    pinMode(modePins.m0, OUTPUT);
    pinMode(modePins.m1, OUTPUT);
    pinMode(modePins.m2, OUTPUT);
}

void MotorControl::go(uint8_t angle, uint8_t dir, int maxFreq){
	Serial.print("Going ");
	Serial.print(dir?"fordward":"backward");
	Serial.print(" with ");
	Serial.print(maxFreq == pwmStepFastFreq ? "high" : "low");
	Serial.print(" speed, with angle: ");
	Serial.println(angle);

    int leftSpeed = 0;
    int rightSpeed = 0;

    if(angle < 64){
       leftSpeed = maxFreq;
       rightSpeed = maxFreq * (64 - angle) / 64;
    }else if(angle < 128){
        leftSpeed = maxFreq;
        rightSpeed = maxFreq * (angle - 64) / 64;
    }else if(angle < 192){
        leftSpeed = maxFreq * (192 - angle) / 64;
        rightSpeed = maxFreq;
    }else{
        leftSpeed = maxFreq * (angle - 192) / 64;
        rightSpeed = maxFreq;
    }

    this->leftStepper->setSpeed(leftSpeed*dir);
    this->rightStepper->setSpeed(rightSpeed*dir*-1);
    this->leftStepper->runSpeed();
    this->rightStepper->runSpeed();
}

void MotorControl::forwardHighSpeed(uint8_t angle){
    go(angle, FORWARD, pwmStepFastFreq);
}

void MotorControl::forwardLowSpeed(uint8_t angle){
    go(angle, FORWARD, pwmStepSlowFreq);
}

void MotorControl::backwardHighSpeed(uint8_t angle){
    go(angle, BACKWARD, pwmStepFastFreq);
}

void MotorControl::backwardLowSpeed(uint8_t angle){
    go(angle, BACKWARD, pwmStepSlowFreq);
}

void MotorControl::stop(){
  Serial.println("STOP");
  this->leftStepper->stop();
  this->rightStepper->stop();
}

void MotorControl::collect(uint8_t angle){
  Serial.print("Collector to: " );
  Serial.println(angle);
  this->collectorServo->write(angle);
}

void MotorControl::dump(uint8_t angle){
  Serial.print("Dumper to: ");
  Serial.println(angle);
  this->dumperServo->write(angle);
}
