//rfid
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define RST_PIN         9
#define SS_RA         8           // Configurable, see typical pin layout above
#define SS_VAO         10          // Configurable, see typical pin layout above

MFRC522 mfrc522_vao(SS_VAO, RST_PIN);   // Create mfrc522_ra instance.
MFRC522 mfrc522_ra(SS_RA, RST_PIN);   // Create mfrc522_ra instance.
String UIDSend = "";

void setupRFID() {
  SPI.begin();        // Init SPI bus
  //rfid_vao
  mfrc522_vao.PCD_Init(); // Init mfrc522_vao card
  //rfid_ra
  mfrc522_ra.PCD_Init(); // Init mfrc522_vao card
}

void loopRFID() {
  the_vao();
  the_ra();
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
