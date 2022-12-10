//softserial
#include <SoftwareSerial.h>
const byte RX = 2;
const byte TX = 3;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);

void setup()
{
  // initialize the LCD
  Serial.begin(115200);
  mySerial.begin(115200);

  // initialize the RFID
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  while (!mySerial);

  setupRFID();
  setupLCD();
  setupSERVO();
}

void loop()
{
  loopRFID();
  loopLCD();
  loopSERVO();
}
