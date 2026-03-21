#pragma once

#include "SubModule.h"
#include "CommandDef.h"

class Wifi : public SubModule
{

public:
	Wifi();

	int read_status(hid_device *handle, unsigned short *ip);
	int set_ssid(hid_device *handle, const char *str);
	int set_password(hid_device *handle, const char *str);
	int send_command(hid_device *handle, const char *str, char *outstr);

private:
	int send_data(hid_device *handle, const unsigned char *str);
	int receive_data(hid_device *handle, char *str);

};

