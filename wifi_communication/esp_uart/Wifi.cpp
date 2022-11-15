#include "Wifi.h"
WiFiClient client;

int ket_noi_wifi(const char * SSID, const char * passwd){
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, passwd);
  Serial.print("Connecting to WiFi ..");
  Serial.println(SSID);
  Serial.println(passwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  return WiFi.status();
}

int ket_noi_server(char * server_ip, unsigned int port){
  Serial.print("connect to ");
  Serial.print(server_ip);
  Serial.print(":");
  Serial.println(port);
  while (!client.connect(server_ip, port)) {
    Serial.println("connection failed .... retrying");
    delay(5000);
  }
  return client.status();
}
