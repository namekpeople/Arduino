//softserial
#include <SoftwareSerial.h>
const byte RX = 2;
const byte TX = 3;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);

//lcd, button, servo
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int a = 0 , b = 0, c = 0, d = 0;
int count = 0;

//rfid
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN         9
//#define SS_RA         8           // Configurable, see typical pin layout above
#define SS_VAO         10          // Configurable, see typical pin layout above
Servo sv_vao, sv_ra;
String sv;
bool vao, ra;
MFRC522 mfrc522_vao(SS_VAO, RST_PIN);   // Create mfrc522_ra instance.
String UIDSend = "";

void setup()
{
  // initialize the LCD
  Serial.begin(115200);
  mySerial.begin(115200);
  lcd.init();
  lcd.backlight();

  // initialize the RFID
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  while (!mySerial);
  SPI.begin();        // Init SPI bus

  //rfid_vao
  mfrc522_vao.PCD_Init(); // Init mfrc522_vao card
  sv_vao.attach(5);
  sv_vao.write(0);
}

void loop()
{
  read_ESP();
  //  hien_thi();
  send_ESP();
}

void read_ESP() {
  while (mySerial.available())
  {
    sv = mySerial.read();
//    if (sv == '\n') 
//      break;
//    else if (sv == 1 || sv == 2){
//      Serial.println(sv);
//      break;
//    }
    vao = sv.indexOf('1');
    ra = sv.indexOf('2');
  }
//  if (sv == '1' || sv == '2')
  if (vao>0 || ra>0)
  {
    sv_vao.write(100);
    delay(3000);
    sv_vao.write(0);
    vao = false;
    ra = false;
//    sv = "";
  }
}

void send_ESP() {
  // Look for new cards
  if ( ! mfrc522_vao.PICC_IsNewCardPresent())
    return;
  // Select one of the cards
  if ( ! mfrc522_vao.PICC_ReadCardSerial())
    return;
  String content = "";
  for (int i = 0; i < mfrc522_vao.uid.size; i++)
  {
    content.concat(String(mfrc522_vao.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
//  Serial.println(content);
  sendUID(content);
  mfrc522_vao.PICC_HaltA();
  mfrc522_vao.PCD_StopCrypto1();
}

void sendUID(String content) {
  UIDSend = "";
  String pre = "";
  //Đóng gói UID
//  if(digitalRead(A0)==0)
//    {
//            pre = "ci";
//    }
//  if(digitalRead(A1)==0)
//    {
//            pre = "co";
//    }
  UIDSend = pre + content;
  Serial.print("Send to ESP: ");
  Serial.println(UIDSend);
  Serial.flush();
  mySerial.println(UIDSend);
  mySerial.flush();
}
