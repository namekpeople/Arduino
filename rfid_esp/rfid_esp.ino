//rfid
#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_vao = 16;        // Configurable, see typical pin layout above
constexpr uint8_t SS_vao = 15;         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_vao, RST_vao);  // Create MFRC522 instance
String tagID = "";

//servo, cam bien
#include <Servo.h>
Servo myServo; 
int sv;

//wifi
#include <ESP8266WiFi.h>
#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const char* ssid = "Khanh Hai 2.4G";          //Tên mạng Wifi mà Socket server của bạn đang kết nối
const char* password = "66666666";  //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.
 
char host[] = "192.168.1.7";  //Địa chỉ IP dịch vụ, hãy thay đổi nó theo địa chỉ IP Socket server của bạn.
int port = 8888;  

void setup() {
  //initialize rfid
  Serial.begin(115200);   // Initialize serial communications with the PC
  while (!Serial);      // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522

  //init servo
  myServo.attach(10);
  myServo.write(0);

  //initialize wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
}

void loop() {
  _rfid();
  _wifi();
}

void _rfid(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) {   //If a new tag is placed close to the RFID reader, continue
    return ;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {     //When a tag is placed, get UID and continue
    return ;
  }
  if(digitalRead(4)==0)
  {
    tagID = "ci"; 
  }
  if(digitalRead(5)==0)
  {
    tagID = "co"; 
  }
  for ( uint8_t i = 0; i < 4; i++) {                  // The MIFARE tag in use has a 4 byte UID
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX));  // Adds the 4 bytes in a single string variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  Serial.println(tagID);
}

void _wifi(){ 
  WiFiClient client; 
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(10000);
    return;
  }
  while (client.connected()) {
    while (mfrc522.PICC_IsNewCardPresent()||mfrc522.PICC_ReadCardSerial()) {
      client.println(tagID);
      client.stop();
    }
    while (client.available()) {  
      sv = client.read();
      Serial.println(sv);
      if (sv == '1' || sv == '2') 
      {
        myServo.write(100); 
        delay(3000);
        myServo.write(0);
        sv = 0;
      }
      client.stop();
    }
  }
  client.stop();  
}
