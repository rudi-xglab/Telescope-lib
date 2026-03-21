#include "Wifi.h"
#include <iostream>

Wifi::Wifi() : SubModule(SET_WIFI_EN, GET_WIFI_EN)
{
}


int Wifi::receive_data(hid_device *handle, char *str)
{
	unsigned char data[256];
	data[0] = 0x00;
	data[1] = RECEIVE_WIFI_DATA;

	unsigned int start_addr = 0;
	for (int repet = 0; repet < 1; ++repet)
	{
		int ret = hid_write(handle, data, 2);
		int len = hid_read_timeout(handle, &data[start_addr], 64, 1000);
	}
	//if (data[0])
	//	printf("\033[33m%s\033[0m", data);

	if (str)
		memcpy(str, data, strlen((const char *)data));

	return 0;
}

int Wifi::send_data(hid_device *handle, const unsigned char *str)
{
	// Send data
	unsigned char data[256], idx = 0;
	int ret;
	data[0] = 0x00;
	data[1] = APPEND_WIFI_DATA;

	if (0)
	{
		memcpy(&data[2], str, 63);
		ret |= hid_write(handle, data, 64);
	}
	else
	{
		do {
			memcpy(&data[2], &str[idx], 62);
			ret |= hid_write(handle, data, 64);
			idx += 62;
		} while (strlen((const char *)&str[idx - 62]) >= 62);
	}

	// Commit
	data[1] = SEND_WIFI_DATA;
	ret |= hid_write(handle, data, 64);

	return 0;
}


int Wifi::send_command(hid_device *handle, const char *str, char *outstr)
{
	send_data(handle, (const unsigned char *)str);
	//printf("\n > %s\n", str);
	for (int i = 0; i < 8; ++i)
		receive_data(handle, outstr);
	return 0;
}

int Wifi::set_ssid(hid_device *handle, const char *str)
{
	unsigned char data[100];
	data[0] = 0x00;
	data[1] = WRITE_WIFI_SSID;
	memcpy(&data[2], str, 63);
	int ret = hid_write(handle, data, 64);
	return 0;
}

int Wifi::set_password(hid_device *handle, const char *str)
{
	unsigned char data[100];
	data[0] = 0x00;
	data[1] = WRITE_WIFI_PASS;
	memcpy(&data[2], str, 63);
	int ret = hid_write(handle, data, 64);
	return 0;
}


int Wifi::read_status(hid_device *handle, unsigned short *ip)
{
	unsigned char data[100];
	data[0] = 0x00;
	data[1] = GET_WIFI_STATUS;
	int ret = hid_write(handle, data, 2);
	int len = hid_read_timeout(handle, data, 64, 1000);

	memcpy(ip, &data[0], 4 * sizeof(unsigned short));
	//if (ip[0])
	//	printf("\033[33mWifi connected with IP %d.%d.%d.%d\033[0m\n", ip[0], ip[1], ip[2], ip[3]);
	//else
	//	printf("\033[33mWifi disconnected.\033[0m\n", ip[0], ip[1], ip[2], ip[3]);

	return 0;
}