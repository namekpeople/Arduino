#ifndef  _Wifi_H
#define _Wifi_H
#include <ESP8266WiFi.h>

#define STASSID "Khanh Hai 2.4G"
#define STAPSK  "66666666"
#define SERVER_IP "192.168.1.8"
//#define STASSID "test-mang"
//#define STAPSK  "mothaiba"
//#define SERVER_IP "192.168.222.203"
#define SERVER_PORT 3000

int ket_noi_wifi(const char * SSID, const char * passwd);
int ket_noi_server(char * server_ip, unsigned int port);

#endif /*_Wifi_H*/
