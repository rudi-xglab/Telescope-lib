#include "RTCC.h"
#include "CommandDef.h"
#include <time.h>

int RTCC::set(hid_device *handle)
{
	unsigned char data[100];
	data[0] = 0x00;
	data[1] = SET_RTCC;
	time_t now = time(NULL);
	struct tm mytime;
	localtime_s(&mytime, &now);
	memcpy(&data[2], &mytime.tm_sec, 2);
	memcpy(&data[4], &mytime.tm_min, 2);
	memcpy(&data[6], &mytime.tm_hour, 2);
	memcpy(&data[8], &mytime.tm_mday, 2);
	memcpy(&data[10], &mytime.tm_mon, 2);
	memcpy(&data[12], &mytime.tm_year, 2);
	memcpy(&data[14], &mytime.tm_wday, 2);
	memcpy(&data[16], &mytime.tm_yday, 2);
	memcpy(&data[18], &mytime.tm_isdst, 2);

	int ret = hid_write(handle, data, 20);

	return 0;
}

int RTCC::get(hid_device *handle, struct tm *mytime)
{
	unsigned char data[100];
	data[0] = 0x00;
	data[1] = GET_RTCC;
	int ret = hid_write(handle, data, 2);
	int len = hid_read_timeout(handle, data, 64, 1000);
	mytime->tm_sec = 0;
	mytime->tm_min = 0;
	mytime->tm_hour = 0;
	mytime->tm_mday = 0;
	mytime->tm_mon = 0;
	mytime->tm_year = 0;
	mytime->tm_wday = 0;
	mytime->tm_yday = 0;
	mytime->tm_isdst = 0;

	memcpy(&mytime->tm_sec, &data[1], 2);
	memcpy(&mytime->tm_min, &data[3], 2);
	memcpy(&mytime->tm_hour, &data[5], 2);
	memcpy(&mytime->tm_mday, &data[7], 2);
	memcpy(&mytime->tm_mon, &data[9], 2);
	memcpy(&mytime->tm_year, &data[11], 2);
	memcpy(&mytime->tm_wday, &data[13], 2);
	memcpy(&mytime->tm_yday, &data[15], 2);
	memcpy(&mytime->tm_isdst, &data[17], 2);

	return 0;
}