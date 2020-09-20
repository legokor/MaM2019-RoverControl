#include "CommandController.h"

bool CommandController::handle(const char * query){
    if(sizeof(query) != 4) return false; //Parse error

    char cmd[3];
    char angle = query[4];
    strncpy(cmd, query, 3);

    Serial.print("Command received: ");
    Serial.print(cmd);
    Serial.print(" with parameter: ");
    Serial.println(angle);

    if (strcmp(cmd, "MFH") == 0)
        mController->forwardHighSpeed(angle);
    else if (strcmp(cmd, "MFL") == 0)
        mController->forwardLowSpeed(angle);
    else if (strcmp(cmd, "MBH") == 0)
        mController->backwardHighSpeed(angle);
    else if (strcmp(cmd, "MBL") == 0)
        mController->backwardLowSpeed(angle);
    else if (strcmp(cmd, "COL") == 0)
        mController->collect(angle);
    else if (strcmp(cmd, "DMP") == 0)
        mController->dump(angle);
    else if (strcmp(cmd, "STO") == 0 && angle == 'P')
        mController->stop();
    else 
        return false;

    return true;
}