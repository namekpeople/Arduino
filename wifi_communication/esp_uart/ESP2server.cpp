#include "ESP2server.h"
#include <ESP8266WiFi.h>
void send_data_to_server(char * data){
  if (client.connected())
    client.println(data);
}
int receive_data_from_server(char * data){
  strncpy(data,"",strlen(data));
     while (client.available() > 0) {
      char character = client.read(); // Receive a single character from the software serial port
      strncat(data, &character, 1);
//      Serial.println(data);
    }
    return strlen(data);
}
