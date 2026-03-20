#pragma once

// Enables
#define SET_CAMERA_EN   0x10
#define GET_CAMERA_EN   0x11
#define SET_MOTOR_EN    0x12
#define GET_MOTOR_EN    0x13
#define SET_24V_EN      0x14
#define GET_24V_EN      0x15
#define SET_PD_EN       0x16
#define GET_PD_EN       0x17
#define SET_USB_EN      0x18
#define GET_USB_EN      0x19
#define SET_WIFI_EN     0x1A
#define GET_WIFI_EN     0x1B

// Movement commands
#define SET_TRACKING    0x30
#define GET_TRACKING    0x31
#define SET_MOVE_X      0x32
#define GET_MOVE_X      0x33
#define SET_MOVE_Y      0x34
#define GET_MOVE_Y      0x35
#define SET_STOPNOW     0x3F

// Movement settings
#define SET_SPEED_COEFF_X   0x40    // Fast, medium, slow, tracking. PWM frequency in Hz
#define GET_SPEED_COEFF_X   0x41
#define SET_SPEED_COEFF_Y   0x42    // Fast, medium, slow. PWM frequency in Hz
#define GET_SPEED_COEFF_Y   0x43

// WIFI tests
#define RECEIVE_WIFI_DATA   0x80
#define APPEND_WIFI_DATA    0x81
#define SEND_WIFI_DATA      0x82

#define WRITE_WIFI_SSID     0x85
#define WRITE_WIFI_PASS     0x86
#define WRITE_WIFI_INFO     0x87
#define CONNECT_WIFI        0x88
#define DISCONNECT_WIFI     0x89
#define GET_WIFI_STATUS     0x8F

// RTCC module
#define SET_RTCC            0xA0
#define GET_RTCC            0xA1

// Status
#define GET_STATUS      0xAB