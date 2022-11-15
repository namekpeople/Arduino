#include "ESP2Adruino.h"
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
SoftwareSerial ESP2Adruino_Serial;
void khoi_tao_ketnoi_arduino(const byte RX, const byte TX) {
   ESP2Adruino_Serial.begin(115200, SWSERIAL_8N1, RX, TX);
}

void gui_data_sang_adruino(char * data){
  ESP2Adruino_Serial.println(data);
}

int nhan_data_tu_adruino(char * data){
      strncpy(data,"",strlen(data));
     while (ESP2Adruino_Serial.available() > 0) {
      char character = ESP2Adruino_Serial.read(); // Receive a single character from the software serial port
      strncat(data, &character, 1);
    }
    return strlen(data);
}
