#ifndef COMMAND_CONTROLLER
#define COMMAND_CONTROLLER

#include "MotorControl.h"

class CommandController{
    private:
        MotorControl * mController;

    public:
        CommandController(MotorControl * motorControl) : mController(motorControl){}
        bool handle(const char* query);
};

#endif