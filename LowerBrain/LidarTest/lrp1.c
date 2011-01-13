#include "hardware.h"
//#include "rprintf.h"

// Initialise the hardware
void appInitHardware(void) {
	initHardware();


}
// Initialise the software
TICK_COUNT appInitSoftware(TICK_COUNT loopStart){
	return 0;
}
// This is the main loop
TICK_COUNT appControl(LOOP_COUNT loopCount, TICK_COUNT loopStart) {

	// -------- Start Switch/Button-------
	// Switch/Button - see switch.h
	
	// To test if it is pressed then
	if(SWITCH_pressed(&button)){
		// pressed
	}
	
	// To test if it is released then
	if(SWITCH_released(&button)){
		// released
	}
	// -------- End   Switch/Button-------

	// -------- Start Actuators -------
	// To control your.motors/servos then see actuators.h in the manual	// To retrieve the required speed of wheel_right use:
	// DRIVE_SPEED speed=act_getSpeed(wheel_right);
	// To set the required speed of wheel_right use:
	// act_setSpeed(wheel_right,speed);
	// This example will move the motors back and forth using the loopStart time:
	TICK_COUNT ms = loopStart / 1000;		// Get current time in ms
	int16_t now = ms % (TICK_COUNT)10000; 	// 10 sec for a full swing
	if(now >= (int16_t)5000){				// Goes from 0ms...5000ms
		now = (int16_t)10000 - now;			// then 5000ms...0ms
	}
	// Map it into DRIVE_SPEED range
	DRIVE_SPEED speed = interpolate(now, 0, 5000, DRIVE_SPEED_MIN, DRIVE_SPEED_MAX);
	// Set speed for all motors/servos
	act_setSpeed(&wheel_right,DRIVE_SPEED_MAX/2);
	act_setSpeed(&wheel_left,DRIVE_SPEED_MAX/2);
	// -------- End   Actuators -------
	//if(lidarGetByte() == 0xFA) rprintf("SYNC\n");
	//else rprintf("not sync\n");
	rprintfu08(lidarGetByte());
	rprintf("HELLO");
	return 0;
}
