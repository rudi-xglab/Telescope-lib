#pragma once
/* Super simple timer class */
#include <iostream>
#include <mutex>
#include <future>



class MyTimer
{
private:
	std::future<void> ft;
	bool ft_valid = false;
	std::function<void(void)> callback_;
	std::function<void(void)> exception_dispatcher_;
	int var1;
	std::atomic_bool isrunning = false;
	uint32_t timeout = 25 - 1; // default: 5 seconds
	std::chrono::milliseconds *res = new std::chrono::milliseconds;
	double resolution_s_;

	void timer_elapsed(void);
public:
	// Constructor
	MyTimer();
	MyTimer(uint16_t resolution_ms);
	// Destructor
	~MyTimer();
	// Assign a callback function
	void assign_callback(const std::function<void(void)>& callback);
	// Assign a function to be invoked whenever an error is detected
	void assign_exception_dispatcher(const std::function<void(void)>& callback);
	// Start the timer (timer is stopped by default)
	void start(void);
	// Stop the timer
	void stop(void);
	// Get current running status
	bool running(void);
	// Reset current timer
	void reset_timeout(void);
	// Set timeout in seconds (default is 5 seconds)
	void set_timeout(double seconds);
};
