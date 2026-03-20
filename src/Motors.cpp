#include "Motors.h"

Motors::Motors() : SubModule(SET_MOTOR_EN, GET_MOTOR_EN)
{
}


int Motors::enable_tracking(hid_device *handle)
{
	return set_value(handle, SET_TRACKING, 0x01);
}

int Motors::disable_tracking(hid_device *handle)
{
	return set_value(handle, SET_TRACKING, 0x00);
}

int Motors::get_tracking(hid_device *handle)
{
	return get_value(handle, GET_TRACKING);
}

int Motors::stop(hid_device *handle)
{
	return set_value(handle, SET_STOPNOW, 0x01);
}

int Motors::move_x(hid_device *handle, motor_speed_t speed, motor_direction_t direction, double degrees)
{
	unsigned char data[100];
	data[0] = 0x00;
	data[1] = SET_MOVE_X;
	data[2] = 0x1; // Move
	data[3] = (direction == RIGHT);
	data[4] = (unsigned int)(degrees * 100) & 0xFF;
	data[5] = ((unsigned int)(degrees * 100) & 0xFF00) >> 8;
	data[6] = speed;
	int ret = hid_write(handle, data, 7);

	return 0;
}

int Motors::move_y(hid_device *handle, motor_speed_t speed, motor_direction_t direction, double hms)
{
	unsigned char data[100];
	data[0] = 0x00;
	data[1] = SET_MOVE_Y;
	data[2] = 0x1; // Move
	data[3] = (direction == UP);
	data[4] = (unsigned int)(hms * 100) & 0xFF;
	data[5] = ((unsigned int)(hms * 100) & 0xFF00) >> 8;
	data[6] = speed;
	int ret = hid_write(handle, data, 7);

	return 0;
}

int Motors::set_x_speed(hid_device *handle, double speed)
{
	return 0;
}

int Motors::set_y_speed(hid_device *handle, double speed)
{
	return 0;
}

// Coeff represent half the PWM period, in us
int Motors::set_speed_coefficient(hid_device *handle, axis ax, double *coeff)
{
	unsigned char data[100];
	data[0] = 0x00;
	data[1] = (ax == x) ? SET_SPEED_COEFF_X : SET_SPEED_COEFF_Y;
	memcpy(&data[2], coeff, 4 * 8);
	hid_write(handle, data, 2 + 4 * 8);
	return 0;
}

// Coeff represent half the PWM period, in us
int Motors::get_speed_coefficient(hid_device *handle, axis ax, double *coeff)
{
	unsigned char data[100];
	data[0] = 0x00;
	data[1] = (ax == x) ? GET_SPEED_COEFF_X : GET_SPEED_COEFF_Y;
	hid_write(handle, data, 2);
	int ret = hid_read_timeout(handle, &data[1], 4 * 8, 1000);
	memcpy(coeff, &data[1], 4 * 8);
	return 0;
}