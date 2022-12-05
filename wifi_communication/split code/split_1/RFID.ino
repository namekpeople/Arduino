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
