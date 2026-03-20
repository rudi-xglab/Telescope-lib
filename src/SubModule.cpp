#include "SubModule.h"


SubModule::SubModule(unsigned char SET_ENABLE, unsigned char GET_ENABLE)
{
	_SET_ENABLE = SET_ENABLE;
	_GET_ENABLE = GET_ENABLE;
}

int SubModule::set_value(hid_device *handle, unsigned char address, unsigned char data)

{
	unsigned char _data[3];
	_data[0] = 0x00;
	_data[1] = address;
	_data[2] = data;
	if (!hid_write(handle, _data, 3))
		return -1;

	return 0;
}

int SubModule::get_value(hid_device *handle, unsigned char address)
{
	unsigned char _data[2];
	_data[0] = 0x00;
	_data[1] = address;

	if (!hid_write(handle, _data, 2))
		return -1;
	if (1 != hid_read_timeout(handle, _data, 1, 1000))
		return -2;
	return _data[0];
}


int SubModule::enable(hid_device *handle)
{
	return set_value(handle, _SET_ENABLE, 0x01);
}

int SubModule::disable(hid_device *handle)
{
	return set_value(handle, _SET_ENABLE, 0x00);
}

int SubModule::get_enabled(hid_device *handle)
{
	return get_value(handle, _GET_ENABLE);
}