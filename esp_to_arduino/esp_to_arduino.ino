///softserial
#include <SoftwareSerial.h>
const byte RX = 12; //D6
const byte TX = 14; //D5
SoftwareSerial mySerial = SoftwareSerial(RX, TX);
String uid = "";
bool stringComplete = false;

//wifi
#include <ESP8266WiFi.h>
#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif
//
//const char* ssid = "Khanh Hai 2.4G";          //Tên mạng Wifi mà Socket server của bạn đang kết nối
//const char* password = "66666666";  //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.

const char* ssid = "Xuka family";          //Tên mạng Wifi mà Socket server của bạn đang kết nối
const char* password = "123123123";  //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.

char host[] = "192.168.1.28";  //Địa chỉ IP dịch vụ, hãy thay đổi nó theo địa chỉ IP Socket server của bạn.
int port = 8888;
WiFiClient client;

void setup() {
  //initialize rfid
  Serial.begin(115200);   // Initialize serial communications with the PC
  while (!Serial);      // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  mySerial.begin(115200);
  while (!mySerial);

  //initialize wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.connect(host, port);
}

void loop() {
    char data[80];
  memset(data,'\0',80); 
  int datalen = nhan_data_tu_adruino(data);
  if (datalen > 0) {
    send_data_to_server(data);
  }
//  read_ARDUINO();       // đọc từ arduino xong gửi lên server
  read_SERVER();        //đọc từ server rồi gửi về arduino
}

int nhan_data_tu_adruino(char * data){
      strncpy(data,"",strlen(data));
     while (mySerial.available() > 0) {
      char character = mySerial.read(); // Receive a single character from the software serial port
      strncat(data, &character, 1);
    }
    return strlen(data);
}

void send_data_to_server(char * data){
  if (client.connected())
    client.println(data);
}

//void read_ARDUINO() {
//  while (mySerial.available()) 
//  {
//    String ch = mySerial.readStringUntil('\n');
////    if (ch != '\n' && ch != '\r') {
//      uid += ch;
////    }
////    else {
//      stringComplete = true;
//      break;
////    }
//  }
//  Serial.println(uid);
// if (stringComplete) {
////    Serial.print("UID nhận từ Uno: ");
////    Serial.println(uid);
////    client.println(uid);
//    send_server(uid);
//    uid = "";
//    stringComplete = false;
//  }
//}

void send_server(String get_uid){
  get_uid = uid;
  Serial.print("UID nhận từ Uno: ");
  Serial.println(get_uid);
  while (client.connected())
    client.println(get_uid);
   client.stop();
}

void read_SERVER() {
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    client.connect(host, port);
    delay(10000);
    return;
  }
  while (client.connected()) {
    while (client.available()) {
      char ch = (char)client.read();
      if (ch != '\r' && ch != '\n')
      {
        mySerial.println(ch, HEX);
        // thêm hex thì serial không hiện 1, 2 mà ô vuông, 
        //arduino thì bình thường. nói chung là chạy ổn. khi gửi từ VS thì arduino chỉ hiện 1,2. 
        //từ hercual thêm ký tự 3?????
        Serial.println(ch,HEX);
//        client.stop();
      }
    }
  }
//  client.stop();
}
