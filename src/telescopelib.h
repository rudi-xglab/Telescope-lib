#pragma once


#define EXPORT __declspec(dllexport)
#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

//typedef enum { X = 0, x = 0, Y = 1, y = 1 } axis;				// TODO: fix redefinition


/* Low level communication */
EXTERN EXPORT int init();
EXTERN EXPORT int close(void *handle);

/* Motor movement */
EXTERN EXPORT int move_right		(double degrees);
EXTERN EXPORT int move_left			(double degrees);
EXTERN EXPORT int move_up			(double hms);
EXTERN EXPORT int move_down			(double hms);
EXTERN EXPORT int enable_tracking	(void);
EXTERN EXPORT int disable_tracking	(void);
EXTERN EXPORT int stop_now			(void);
EXTERN EXPORT int get_speed_coeff	(char ax, double *coeff);
EXTERN EXPORT int set_speed_coeff	(char ax, double *coeff);

/* Status */
EXTERN EXPORT int get_weather		(double *temperature, double *humidity, double *pressure);
EXTERN EXPORT int get_power_status	(double *Vdc_in, double *camera_current, double *motor_current, double *USB_current);

/* Wifi */
EXTERN EXPORT int get_wifi_status	(unsigned short *ip);
EXTERN EXPORT int set_wifi_ssid		(const char *ssid);
EXTERN EXPORT int set_wifi_password	(const char *passw);

/* RTCC */
EXTERN EXPORT int set_rtcc			(void);
EXTERN EXPORT int get_rtcc			(struct tm *time);