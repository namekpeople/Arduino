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
String sv;
bool vao, ra;
MFRC522 mfrc522_vao(SS_VAO, RST_PIN);   // Create mfrc522_ra instance.
MFRC522 mfrc522_ra(SS_RA, RST_PIN);   // Create mfrc522_ra instance.
String UIDSend = "";

void the_vao();
void the_ra();
void hien_thi();
void read_ESP();

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
  the_vao();
  the_ra();
}
