//wifi
#include "Wifi.h"
#include "ESP2server.h"
#include "ESP2Adruino.h"

char host[] = SERVER_IP;
int port = SERVER_PORT;
const char* ssid = STASSID;
const char* password = STAPSK;
const byte RX = 12; //D6
const byte TX = 14; //D5

void setup() {
  //initialize rfid
  Serial.begin(115200);   // Initialize serial communications with the PC
  while (!Serial);      // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  //initialize wifi
  ket_noi_wifi(ssid, password);
  ket_noi_server(host, port);
  khoi_tao_ketnoi_arduino(RX, TX);
}

void loop() {
  //send_data_to_server("Hello server");
  char data[80];
  memset(data,'\0',80); 
  int datalen = nhan_data_tu_adruino(data);
  if (datalen > 0) {
    send_data_to_server(data);
  }
  int datalen2 = receive_data_from_server(data);
  if (datalen2 > 0) {
    Serial.println(data);
    gui_data_sang_adruino(data);
  }
  //Serial.println(data);
  //delay(5000);
}
