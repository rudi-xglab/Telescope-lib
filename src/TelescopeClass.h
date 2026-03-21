#pragma once

#include "SubModule.h"
#include "Motors.h"
#include "Wifi.h"
#include "RTCC.h"
#include "CommandDef.h"
#include "../inc/hidapi.h"
#include "MyTimer.h"
#include <mutex>


class Telescope
{

private:
	SubModule	*camera;
	SubModule	*dc24;
	SubModule	*pd;
	SubModule	*usb;
	Wifi		*wifi;
	Motors		*motors;
	RTCC		*rtcc;
	Status		status;

	hid_device	*hid_handle;

	std::timed_mutex mtx;
	MyTimer *status_tmr;
	bool		initialized = false;

public:
	int init				(void);
	int close				(void);
	int startup				(void);
	int move_right			(double degrees);
	int move_left			(double degrees);
	int move_up				(double hms);
	int move_down			(double hms);
	int enable_tracking		(void);
	int disable_tracking	(void);
	int stop_now			(void);

	int get_speed_coeff		(char ax, double *coeff);
	int set_speed_coeff		(char ax, double *coeff);

	int read_status			(void);
	Status get_status		(void);

	int get_wifi_status		(unsigned short *ip);
	int set_wifi_ssid		(const char *str);
	int set_wifi_password	(const char *str);

	int set_rtcc			(void);
	int get_rtcc			(struct tm *time);



};

