//softserial
#include <SoftwareSerial.h>
const byte RX = 2;
const byte TX = 3;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);

//lcd, cảm biến
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
#define SS_RA         8           // Configurable, see typical pin layout above
#define SS_VAO         10          // Configurable, see typical pin layout above

//servo
Servo sv_vao, sv_ra;
int temp;
int dem = 0;
String sv;
MFRC522 mfrc522_vao(SS_VAO, RST_PIN);   // Create mfrc522_ra instance.
MFRC522 mfrc522_ra(SS_RA, RST_PIN);   // Create mfrc522_ra instance.
String UIDSend = "";

long prevTime = 0;

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
  //rfid_ra
  mfrc522_ra.PCD_Init(); // Init mfrc522_vao card
  sv_ra.attach(6);
  sv_ra.write(0);
}

void loop()
{
  hien_thi();
  read_ESP();
  stop_servo();
  the_vao();
  the_ra();
}

void read_ESP() {
  if (mySerial.available() > 0)
  {
    temp = mySerial.read();
    if (temp < 3 && temp > 0) sv.concat(temp);
    if (sv != "") Serial.println(sv);
  }
  if (sv.startsWith((String)'1'))
  {
    sv_vao.write(100);
    sv = "";
    prevTime = millis();
  }
  if (sv.startsWith((String)'2'))
  {
    sv_ra.write(100);
    sv = "";
    prevTime = millis();
  }
}

void stop_servo() {
  if (millis() - prevTime >= 3000 && sv_vao.read() == 100) {
    sv_vao.write(0);
  }
  if (millis() - prevTime >= 3000 && sv_ra.read() == 100) {
    sv_ra.write(0);
  }
}

void the_vao() {
  // Look for new cards
  if ( ! mfrc522_vao.PICC_IsNewCardPresent())
    return;
  // Select one of the cards
  if ( ! mfrc522_vao.PICC_ReadCardSerial())
    return;
  String content = "ci";
  for (int i = 0; i < mfrc522_vao.uid.size; i++)
  {
    content.concat(String(mfrc522_vao.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  sendUID(content);
  mfrc522_vao.PICC_HaltA();
  mfrc522_vao.PCD_StopCrypto1();
}

void the_ra() {
  // Look for new cards
  if ( ! mfrc522_ra.PICC_IsNewCardPresent())
    return;
  // Select one of the cards
  if ( ! mfrc522_ra.PICC_ReadCardSerial())
    return;
  String content = "co";
  for (int i = 0; i < mfrc522_ra.uid.size; i++)
  {
    content.concat(String(mfrc522_ra.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  sendUID(content);
  mfrc522_ra.PICC_HaltA();
  mfrc522_ra.PCD_StopCrypto1();
}

void sendUID(String content) {
  UIDSend = "";
  UIDSend = content;
  Serial.print("Send to ESP: ");
  Serial.println(UIDSend);
  Serial.flush();
  mySerial.println(UIDSend);
  mySerial.flush();
}

void hien_thi() {
  if (digitalRead(A3) == 0)
  {
    a = 1;
  }
  else
  {
    a = 0;
  }

  if (digitalRead(A2) == 0)
  {
    b = 1;
  }
  else
  {
    b = 0;
  }
  if (digitalRead(A1) == 0)
  {
    c = 1;
  }
  else
  {
    c = 0;
  }

  if (digitalRead(A0) == 0)
  {
    d = 1;
  }
  else
  {
    d = 0;
  }

  count = a + b + c + d;

  if (count == 4)
  {
    lcd.setCursor(0, 1);
    lcd.print("Full slot, Sorry");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print(4 - count);
    lcd.print(" Slot available");
  }

  lcd.setCursor(3, 0);
  lcd.print("UTC Parking");
}
