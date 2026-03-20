#include "TelescopeClass.h"

#define LOCK_ERROR -100

int Telescope::init()
{
	camera	= new SubModule(SET_CAMERA_EN, GET_CAMERA_EN);
	dc24	= new SubModule(SET_24V_EN, GET_24V_EN);
	pd		= new SubModule(SET_PD_EN, GET_PD_EN);
	usb		= new SubModule(SET_USB_EN, GET_USB_EN);
	wifi	= new SubModule(SET_WIFI_EN, GET_WIFI_EN);
	motors	= new Motors();


	hid_device_info *devs, *cur_dev;
	hid_device *handle;
	hid_init();

	devs = hid_enumerate(0, 0);
	if (!devs)
		return 1;

	cur_dev = devs;
	while (cur_dev) {
		if (cur_dev->product_id == 0x3F && cur_dev->vendor_id == 0x4d8)
		{
			hid_handle = hid_open_path(cur_dev->path);
			return startup();
		}
		cur_dev = cur_dev->next;
	}
	return 2;
}

int Telescope::close()
{
	delete camera;
	delete dc24;
	delete pd;
	delete usb;
	delete wifi;
	delete motors;

	status_tmr->stop();
	delete status_tmr;

	hid_close(hid_handle);

	return 0;
}

int Telescope::startup()
{
	dc24->enable(hid_handle);
	pd->disable(hid_handle);
	motors->enable(hid_handle);
	camera->enable(hid_handle);
	usb->enable(hid_handle);
	wifi->disable(hid_handle);

	status_tmr = new MyTimer(0.200);
	status_tmr->assign_callback([this] {read_status(); });
	status_tmr->set_timeout(0.200);
	status_tmr->start();

	return 0;
}

int Telescope::move_right(double degrees)
{
	std::unique_lock<std::timed_mutex> lck(mtx);
	if (!lck.try_lock_for(std::chrono::milliseconds(100)))
		return LOCK_ERROR;

	return motors->move_x(hid_handle, SLOW, RIGHT, degrees);
}

int Telescope::move_left(double degrees)
{
	std::unique_lock<std::timed_mutex> lck(mtx);
	if (!lck.try_lock_for(std::chrono::milliseconds(100)))
		return LOCK_ERROR;

	return motors->move_x(hid_handle, SLOW, LEFT, degrees);
}

int Telescope::move_up(double hms)
{
	std::unique_lock<std::timed_mutex> lck(mtx);
	if (!lck.try_lock_for(std::chrono::milliseconds(100)))
		return LOCK_ERROR;

	return motors->move_y(hid_handle, SLOW, UP, hms);
}

int Telescope::move_down(double hms)
{
	std::unique_lock<std::timed_mutex> lck(mtx);
	if (!lck.try_lock_for(std::chrono::milliseconds(100)))
		return LOCK_ERROR;

	return motors->move_y(hid_handle, SLOW, DOWN, hms);
}

int Telescope::enable_tracking(void)
{
	std::unique_lock<std::timed_mutex> lck(mtx);
	if (!lck.try_lock_for(std::chrono::milliseconds(100)))
		return LOCK_ERROR;

	return motors->enable_tracking(hid_handle);
}

int Telescope::disable_tracking(void)
{
	std::unique_lock<std::timed_mutex> lck(mtx);
	if (!lck.try_lock_for(std::chrono::milliseconds(100)))
		return LOCK_ERROR;

	return motors->disable_tracking(hid_handle);
}

int Telescope::stop_now(void)
{
	std::unique_lock<std::timed_mutex> lck(mtx);
	if (!lck.try_lock_for(std::chrono::milliseconds(100)))
		return LOCK_ERROR;

	return motors->stop(hid_handle);
}

void Telescope::read_status(void)
{
	std::unique_lock<std::timed_mutex> lck(mtx);
	if (!lck.try_lock_for(std::chrono::milliseconds(100)))
		return;

	unsigned char data[100];
	data[0] = 0x00;
	data[1] = GET_STATUS;
	int ret = hid_write(hid_handle, data, 2);
	int len = hid_read_timeout(hid_handle, data, 24, 1000);


	if (false)
	{
		status.temperature = (double)(data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]) / 1048576.0 * 200.0 - 50.0;
		status.humidity = (double)(data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7]) / 1048576.0 * 100.0;
		status.pressure = NAN;
	}
	else
	{
		status.temperature = (double)(data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0]) / 100.0;
		status.humidity = (double)(0 << 24 | 0 << 16 | data[5] << 8 | data[4]) / 65536 * 125 - 6;
		status.pressure = (double)(data[11] << 24 | data[10] << 16 | data[9] << 8 | data[8]) / 100.0;
	}
	status.Vdc_in = (data[13] << 8 | data[12]) / 32768.0 * 2.048 * 12.0;
	status.motor_current = (data[15] << 8 | data[14]) / 32768.0 * 2.048 / 0.05 * 1.5e3 / 10 / 8;
	status.camera_current = (data[17] << 8 | data[16]) / 32768.0 * 2.048 / 0.05 * 1.5e3 / 10 / 8;
	status.USB_current = (data[19] << 8 | data[18]) / 32768.0 * 2.048 / 0.05 * 1.5e3 / 10 / 8;
	status.Uptime = (double)(data[23] << 24 | data[22] << 16 | data[21] << 8 | data[20]) / 100.0;

}

Status Telescope::get_status(void)
{
	return status;
}