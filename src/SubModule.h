#pragma once

#include "../inc/hidapi.h"


typedef struct {
	double temperature;
	double humidity;
	double pressure;

	double Vdc_in;
	double motor_current;
	double camera_current;
	double USB_current;

	double Uptime;
	unsigned char WifiDataAvail;

} Status;


class SubModule
{

public:
	SubModule(unsigned char SET_ENABLE, unsigned char GET_ENABLE);
	int enable(hid_device *handle);
	int disable(hid_device *handle);
	int get_enabled(hid_device *handle);

protected:

	int set_value(hid_device *handle, unsigned char address, unsigned char data);
	int get_value(hid_device *handle, unsigned char address);

private:
	unsigned char _SET_ENABLE;
	unsigned char _GET_ENABLE;
};

