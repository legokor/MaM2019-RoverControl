#include "MotorControl.h"

#define FORWARD 1   //HIGH
#define BACKWARD 0  //LOW

MotorControl::MotorControl(StepperMotor leftFront, StepperMotor leftBack, StepperMotor rightFront, StepperMotor rightBack, ServoMotor collector, ServoMotor dumper):leftFront(leftFront),leftBack(leftBack),rightFront(rightBack){
    pinMode(leftFront.dirPin, OUTPUT);
    pinMode(leftFront.stepPin, OUTPUT);
    pinMode(leftBack.dirPin, OUTPUT);
    pinMode(leftBack.stepPin, OUTPUT);

    pinMode(rightFront.dirPin, OUTPUT);
    pinMode(rightFront.stepPin, OUTPUT);
    pinMode(rightBack.dirPin, OUTPUT);
    pinMode(rightBack.stepPin, OUTPUT);

    pinMode(collector.signalPin, OUTPUT);
    pinMode(dumper.signalPin, OUTPUT);

    ledcSetup(pwmChannelLeft, pwmStepFastFreq, 8);
    ledcAttachPin(leftFront.stepPin, pwmChannelLeft);
    ledcAttachPin(leftBack.stepPin, pwmChannelLeft);

    ledcSetup(pwmChannelRight, pwmStepFastFreq, 8);
    ledcAttachPin(rightFront.stepPin, pwmChannelRight);
    ledcAttachPin(rightBack.stepPin, pwmChannelRight);

    ledcSetup(pwmChannelDumper, pwmServoFreq, 8);
    ledcAttachPin(dumper.signalPin, pwmChannelDumper);

    ledcSetup(pwmChannelCollector, pwmServoFreq, 8);
    ledcAttachPin(collector.signalPin, pwmChannelCollector);
}

void MotorControl::go(uint8_t angle, uint8_t dir, int maxFreq){
	Serial.print("Going ");
	Serial.print(dir?"fordward":"backward");
	Serial.print(" with ");
	Serial.print(maxFreq == pwmStepFastFreq ? "high" : "low");
	Serial.print(" speed, with angle: ");
	Serial.println(angle);

    if(angle < 64){
        digitalWrite(rightFront.dirPin, FORWARD != !dir);
        digitalWrite(rightBack.dirPin, FORWARD != !dir);
        digitalWrite(leftFront.dirPin, BACKWARD != !dir);
        digitalWrite(leftBack.dirPin, BACKWARD != !dir);

        ledcSetup(pwmChannelRight, maxFreq, 8);    
        ledcSetup(pwmChannelLeft, maxFreq * (64- angle) / 64, 8);
    }else if(angle < 128){
        digitalWrite(rightFront.dirPin, FORWARD != !dir);
        digitalWrite(rightBack.dirPin, FORWARD != !dir);
        digitalWrite(leftFront.dirPin, FORWARD != !dir);
        digitalWrite(leftBack.dirPin, FORWARD != !dir);

        ledcSetup(pwmChannelRight, maxFreq, 8);   
        ledcSetup(pwmChannelLeft, maxFreq * (angle - 64) / 64, 8);
    }else if(angle < 192){
        digitalWrite(rightFront.dirPin, FORWARD != !dir);
        digitalWrite(rightBack.dirPin, FORWARD != !dir);
        digitalWrite(leftFront.dirPin, FORWARD != !dir);
        digitalWrite(leftBack.dirPin, FORWARD != !dir);

        ledcSetup(pwmChannelRight, maxFreq * (192 - angle) / 64, 8);   
        ledcSetup(pwmChannelLeft, maxFreq, 8);
    }else{
        digitalWrite(rightFront.dirPin, BACKWARD != !dir);
        digitalWrite(rightBack.dirPin, BACKWARD != !dir);
        digitalWrite(leftFront.dirPin, FORWARD != !dir);
        digitalWrite(leftBack.dirPin, FORWARD != !dir);

        ledcSetup(pwmChannelRight, maxFreq * (angle - 192) / 64, 8);   
        ledcSetup(pwmChannelLeft, maxFreq, 8);
    }

    ledcWrite(pwmChannelLeft, 127);
    ledcWrite(pwmChannelRight, 127);
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
    ledcWrite(pwmChannelLeft, 0);
    ledcWrite(pwmChannelRight, 0);
}

void MotorControl::collect(uint8_t angle){
  Serial.print("Collector to: " );
  Serial.println(angle);
    ledcWrite(pwmChannelCollector, angle);
}

void MotorControl::dump(uint8_t angle){
  Serial.print("Dumper to: ");
  Serial.println(angle);
    ledcWrite(pwmChannelDumper, angle);
}
