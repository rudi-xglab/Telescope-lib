/* Super simple timer class */
#include <iostream>
#include <mutex>
#include <future>
#include "MyTimer.h"


MyTimer::MyTimer()
{
	ft_valid = false;
	*res = std::chrono::milliseconds(200);
	resolution_s_ = 0.200;
	var1 = 0;
}
MyTimer::MyTimer(const uint16_t resolution_ms)
{
	ft_valid = false;
	*res = std::chrono::milliseconds(resolution_ms);
	resolution_s_ = (double)resolution_ms * 0.001;
	var1 = 0;
}
MyTimer::~MyTimer()
{
	if (isrunning)
		stop();
}
void MyTimer::assign_callback(const std::function<void(void)>& callback)
{
	callback_ = callback;
}
void MyTimer::start(void)
{
	reset_timeout();
	isrunning = true;
	ft_valid = true;
	ft = std::async(&MyTimer::timer_elapsed, this);
}
void MyTimer::stop(void)
{
	isrunning = false;
	std::chrono::system_clock::time_point wait_time = std::chrono::system_clock::now() + std::chrono::milliseconds(500);
	if (ft_valid)
		std::future_status ft_sts = ft.wait_until(wait_time);
}
bool MyTimer::running(void)
{
	return isrunning;
}
void MyTimer::set_timeout(double seconds)
{
	timeout = (uint32_t)(seconds / resolution_s_) - 1;
}
void MyTimer::reset_timeout(void)
{
	var1 = 0;
}
void MyTimer::assign_exception_dispatcher(const std::function<void()>& callback)
{
	exception_dispatcher_ = callback;
}
void MyTimer::timer_elapsed(void)
{
	// std::cout << "Timer invoked\n";
	while (isrunning)
	{
		if (*res != std::chrono::milliseconds(0))
			std::this_thread::sleep_for(*res);

		if (var1 >= timeout) // default: 5 seconds
		{
			try {
				callback_();
			}
			catch (std::exception &e)
			{
				stop();
				exception_dispatcher_();
				throw e;
			}
			reset_timeout();
		}
		else
			++var1;
	}
}
