#pragma once

#include "SubModule.h"
#include "Motors.h"
#include "CommandDef.h"
#include "../inc/hidapi.h"
#include "MyTimer.h"
#include <mutex>


class Telescope
{

private:
	SubModule *camera;
	SubModule *dc24;
	SubModule *pd;
	SubModule *usb;
	SubModule *wifi;
	Motors *motors;
	Status status;

	hid_device *hid_handle;

	std::timed_mutex mtx;
	MyTimer *status_tmr;

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

	void read_status		(void);
	Status get_status		(void);

};

