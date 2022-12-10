//lcd, cảm biến
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int a = 0 , b = 0, c = 0, d = 0;
int count = 0;
long err = 0;

void setupLCD() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
}

void loopLCD() {
  // put your main code here, to run repeatedly:
  if (millis() - err >= 3000) {
    hien_thi();
  }
}

void hien_thi() {
  if (digitalRead(A3) == 0) a = 1;
    else a = 0;

  if (digitalRead(A2) == 0) b = 1;
    else b = 0;

  if (digitalRead(A1) == 0) c = 1;
    else c = 0;

  if (digitalRead(A0) == 0) d = 1;
    else d = 0;

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
