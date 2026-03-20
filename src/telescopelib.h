#pragma once


#define EXPORT __declspec(dllexport)
#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

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

/* Status */
//EXTERN EXPORT Status get_status		(void);