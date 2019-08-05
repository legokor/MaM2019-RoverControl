# Onboard robot controller
This module is responsible for receiving the commands through LoRa and interpreting them. This controller takes care of controlling the 4 stepper and 2 servo motor of the robot. A debug interface will be implemented aswell, with WebSocket interface to the UGND module. Through this, the latest received command and the status of the PWM signals will be accessable.
During further developement it may be migrated to RTOS platform.
