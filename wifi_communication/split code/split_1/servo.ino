//servo
Servo sv_vao, sv_ra;
int temp;
int dem = 0;
String sv;
long prevTime = 0;

void setupSERVO() {
  // put your setup code here, to run once:
  sv_vao.attach(5);
  sv_vao.write(0);

  sv_ra.attach(6);
  sv_ra.write(0);
}

void loopSERVO() {
  // put your main code here, to run repeatedly:
  read_ESP();
  stop_servo();
}

void read_ESP() {
  if (mySerial.available() > 0)
  {
    temp = mySerial.read();
    if (temp < 5 && temp > 0) sv.concat(temp);
    if (sv != "") Serial.println(sv);
  }
  if (sv.startsWith((String)'1'))
  {
    sv_vao.write(100);
    sv = "";
    prevTime = millis();
  }
  else if (sv.startsWith((String)'2'))
  {
    sv_ra.write(100);
    sv = "";
    prevTime = millis();
  }
  else if (sv.startsWith((String)'3'))
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Unavailable UID");
    sv = "";
    err = millis();
  }
  else if (sv.startsWith((String)'4'))
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Unavaible car");
    sv = "";
    err = millis();
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
