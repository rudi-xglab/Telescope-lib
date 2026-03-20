#pragma once

#include "SubModule.h"
#include "CommandDef.h"

typedef enum motor_speed_t {TRACKING, SLOW, MEDIUM, FAST};
typedef enum motor_direction_t {LEFT, RIGHT, UP, DOWN};

typedef enum { X = 0, x = 0, Y = 1, y = 1 } axis;				// BY NOW

class Motors : public SubModule
{

public:
	Motors();

	int enable_tracking(hid_device *handle);
	int disable_tracking(hid_device *handle);
	int get_tracking(hid_device *handle);
	int move_x(hid_device *handle, motor_speed_t speed, motor_direction_t direction, double degrees);
	int move_y(hid_device *handle, motor_speed_t speed, motor_direction_t direction, double hms);
	int stop(hid_device *handle);
	int set_x_speed(hid_device *handle, double speed);
	int set_y_speed(hid_device *handle, double speed);

	int set_speed_coefficient(hid_device *handle, axis ax, double *coeff);
	int get_speed_coefficient(hid_device *handle, axis ax, double *coeff);

};

