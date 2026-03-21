#include "telescopelib.h"

#include "../inc/hidapi.h"
#include "CommandDef.h"
#include "Motors.h"
#include "SubModule.h"
#include "TelescopeClass.h"


Telescope t;



int init()
{
	return t.init();
}



int close(void *handle)
{
	return t.close();
}


int move_right(double degrees)
{
	return t.move_right(degrees);
}

int move_left(double degrees)
{
	return t.move_left(degrees);
}

int move_up(double hms)
{
	return t.move_up(hms);
}

int move_down(double hms)
{
	return t.move_down(hms);
}

int enable_tracking(void)
{
	return t.enable_tracking();
}

int disable_tracking(void)
{
	return t.disable_tracking();
}

int stop_now(void)
{
	return t.stop_now();
}

int get_speed_coeff(char ax, double *coeff)
{
	return t.get_speed_coeff(ax, coeff);
}

int set_speed_coeff(char ax, double *coeff)
{
	return t.set_speed_coeff(ax, coeff);
}

int get_weather(double *temperature, double *humidity, double *pressure)
{
	*temperature	= t.get_status().temperature;
	*humidity		= t.get_status().humidity;
	*pressure		= t.get_status().pressure;
	return 0;
}

int get_power_status(double *Vdc_in, double *camera_current, double *motor_current, double *USB_current)
{
	*Vdc_in			= t.get_status().Vdc_in;
	*camera_current = t.get_status().camera_current;
	*motor_current	= t.get_status().motor_current;
	*USB_current	= t.get_status().USB_current;
	return 0;
}

int get_wifi_status(unsigned short *ip)
{
	t.get_wifi_status(ip);
	return 0;
}

int set_wifi_ssid(const char *ssid)
{
	t.set_wifi_ssid(ssid);
	return 0;
}

int set_wifi_password(const char *passw)
{
	t.set_wifi_password(passw);
	return 0;
}

int set_rtcc(void)
{
	return t.set_rtcc();
}

int get_rtcc(struct tm *time)
{
	return t.get_rtcc(time);
}



		/*

	while (1)

		handle = hid_open_path(cur_dev->path);
		DC24.enable(handle);
		PD.enable(handle);
		Motors.enable(handle);
		Camera.enable(handle);
		USB.enable(handle);
		//		Wifi.enable(handle);
		read_status(handle, &status);
		read_wifi_status(handle);

		printf("\t > Temperature: %.2f C; humidity: %.2f %%; pressure: %.2f mbar; uptime: %.2f s.\n", status.temperature, status.humidity, status.pressure, status.Uptime);
		printf("Vdc_in: %.2f V; currents: %.2f mA %.2f mA %.2f mA\n", status.Vdc_in, status.motor_current, status.camera_current, status.USB_current);
		printf("Wifi enable: %d. USB enable: %d. 24V enable: %d. Motors enable: %d.\n", Wifi.get_enabled(handle), USB.get_enabled(handle), DC24.get_enabled(handle), Motors.get_enabled(handle));

		//receive_wifi_data(handle);

		bool WIFI_SECRETS = false;
		if (WIFI_SECRETS)
		{
			set_wifi_ssid(handle, "*****************");
			set_wifi_password(handle, "****************");
		}

		bool TEST_WIFI = false;
		if (TEST_WIFI)
		{
			do {
				read_status(handle, &status);
				printf("Wifi status: %d.\n", status.WifiDataAvail);
			} while (status.WifiDataAvail != 32);

			int sock = 0;
			char str_rd[4096], str_wr[4096];
			//			send_wifi_command(handle, "AT+WSTAC=3,\"123456789012345678901234567890123456789012345678901234567890\"", 0);
						//send_wifi_command(handle, "AT+RST", 0); Sleep(6000);
						//send_wifi_command(handle, "AT+GMI", 0);
						//send_wifi_command(handle, "AT+SNTPC=1,0", NULL);
						//send_wifi_command(handle, "AT+WIFIC=11", NULL);
						//send_wifi_command(handle, "AT+WAP=0", NULL);
						//send_wifi_command(handle, "AT+WSTA=0", NULL);
						//send_wifi_command(handle, "AT+WSTAC=1,\"*********************\"", NULL);
						//send_wifi_command(handle, "AT+WSTAC=3,\"***************************\"", NULL);
						//send_wifi_command(handle, "AT+WSTAC=2,2", NULL);
						//send_wifi_command(handle, "AT+WSTA=1", NULL);
						//Sleep(8000);
			send_wifi_command(handle, "...", NULL);
			send_wifi_command(handle, "AT+SOCKO=2,4", str_rd);
			sscanf_s(str_rd, "AT+SOCKO=2,4\r\n+SOCKO:%d", &sock, 128);
			printf("\nSocket opened: %d\n", sock);
			sprintf_s(str_wr, "AT+SOCKBR=%5d,\"5.9.139.206\",80", sock, 1024);
			send_wifi_command(handle, str_wr, NULL);
			sprintf_s(str_wr, "AT+SOCKWR=%5d,112,\"GET /TrainSummaryYQL.php?TrainNumber=2256 HTTP/1.1\\r\\nHost: misterpeemp.altervista.org\\r\\nConnection: Keep-Alive\\r\\n\\r\\n\"", sock, 1024);
			send_wifi_command(handle, str_wr, NULL);
			sprintf_s(str_wr, "AT+SOCKRD=%5d,1,200", sock, 1024);
			int i = 0;
			do {
				send_wifi_command(handle, str_wr, str_rd);
				//read_status(handle, &status);
			} while (++i < 25);


			//	"
			//	AT + SOCKRD = XXXXX, 1, 200



			unsigned char str[512];
			while (1)
			{

				printf("\nInput AT command: \n");
				fgets((char *)str, 512, stdin);
				str[strcspn((char *)str, "\n")] = 0;
				send_wifi_command(handle, (const char *)str, NULL);
				/*send_wifi_data(handle, str);
				Sleep(500);
				for (int i = 0; i < 8; ++i)
				{
					receive_wifi_data(handle);
					Sleep(50);
				}

			}
		}

		double speed_coeff[4] = { 15300, 200, 125, 80 };
		//Motors.set_speed_coefficient(handle, x, speed_coeff);
		//Motors.set_speed_coefficient(handle, y, speed_coeff);
//		Motors.get_speed_coefficient(handle, x, speed_coeff);
//		printf("Speed coefficient: x %f %f %f %f; ", speed_coeff[0], speed_coeff[1], speed_coeff[2], speed_coeff[3]);
		Motors.get_speed_coefficient(handle, y, speed_coeff);
		printf("y %f %f %f %f.\n", speed_coeff[0], speed_coeff[1], speed_coeff[2], speed_coeff[3]);

		current_timestamp = (unsigned long)time(NULL);
		if (current_timestamp - last_timestamp > 60)
		{
			//Wifi.enable(handle);
			printf(">>>>>>>>>> WRITE\n");
			last_timestamp = current_timestamp;
			FILE *fileid;
			fopen_s(&fileid, "E:\\temp.txt", "a+");
			fprintf(fileid, "%li, %.2f, %.2f, %.2f\n", current_timestamp, status.temperature, status.humidity, status.pressure);
			fclose(fileid);
			//	Motors.move_x(handle, SLOW, RIGHT, 59);
			//	Motors.move_y(handle, SLOW, RIGHT, 59);
				//Motors.enable_tracking(handle);

			if (status.Uptime < 10)
				set_rtcc(handle);


			//unsigned char str[64] = "AT+WIFIC";
			//send_wifi_data(handle, str);
		}
		else
		{
			//Wifi.disable(handle);
		}
		struct tm mytime;
		get_rtcc(handle, &mytime);
		printf("Device time: %02d:%02d:%02d, %02d-%02d-%04d.\n", mytime.tm_hour, mytime.tm_min, mytime.tm_sec, mytime.tm_mday, mytime.tm_mon, mytime.tm_year + 1900);

		/*printf("\t %d > %x %x %x %x\n", len, data[0], data[1], data[2], data[3]);
		printf("\t %f\n", temperature);
		printf("\t %d > %x %x %x %x\n", len, data[4], data[5], data[6], data[7]);
		printf("\t %f\n", humidity);
		hid_close(handle);
	return 0;
}
*/