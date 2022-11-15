#ifndef  _ESP2server_H
#define _ESP2server_H

#include <ESP8266WiFi.h>

extern WiFiClient client;
void send_data_to_server(char * data);
int receive_data_from_server(char * data);
#endif /* _ESP2server_H */
