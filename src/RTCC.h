#pragma once
#include "../inc/hidapi.h"


class RTCC
{

public:
	int set(hid_device *handle);
	int get(hid_device *handle, struct tm *mytime);

};