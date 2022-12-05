//wifi & esp2server
#include <ESP8266WiFi.h>
#define STASSID "Khanh Hai 2.4G"
#define STAPSK  "66666666"
#define SERVER_IP "192.168.1.8"
#define SERVER_PORT 3000
WiFiClient client;

//esp2arduino
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
SoftwareSerial ESP2Adruino_Serial;

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

}

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
