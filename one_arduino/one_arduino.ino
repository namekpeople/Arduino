//lcd, button, servo
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int a=0 , b=0, c=0, d=0;
int count=0;

//rfid
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN         9       
#define SS_RA         8            Configurable, see typical pin layout above
#define SS_VAO         10           Configurable, see typical pin layout above
Servo sv_vao, sv_ra; 
int sv;
String tagID = "";

MFRC522 mfrc522_ra(SS_RA, RST_PIN);    Create mfrc522_ra instance.
MFRC522 mfrc522_vao(SS_VAO, RST_PIN);    Create mfrc522_ra instance.


void setup()
{
   initialize the LCD
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
   initialize the RFID
  while (!Serial);     Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();         Init SPI bus
  rfid_ra
  mfrc522_ra.PCD_Init();  Init mfrc522_ra card
  sv_ra.attach(6);
  sv_ra.write(0);
  rfid_vao
  mfrc522_vao.PCD_Init();  Init mfrc522_vao card
  sv_vao.attach(5);
  sv_vao.write(0);
}

void loop()
{
  button();
  hien_thi();
  the_vao();
  the_ra();
}

void button() {
  while (Serial.available()) 
  {
      sv = Serial.read();
      Serial.println(sv);
      delay(200);
  }
  if (sv == '1') 
  {
      sv_vao.write(100); 
      delay(3000);
      sv_vao.write(0);
      sv = ~sv;
  }

    if (sv == '2') 
  {
      sv_vao.write(100); 
      delay(3000);
      sv_vao.write(0);
      sv = ~sv;
  }
  
}

void the_vao() {
 Look for new cards
  if ( ! mfrc522_vao.PICC_IsNewCardPresent()) 
      return;
   Select one of the cards
  if ( ! mfrc522_vao.PICC_ReadCardSerial())
      return;
  if(digitalRead(A0)==0)
  {
          Serial.print("ci");
  } 
  if(digitalRead(A1)==0)
  {
          Serial.print("co");
  }   
  Serial.print("ci");
  Serial.print(mfrc522_vao.uid.uidByte[0], HEX);
  Serial.print(mfrc522_vao.uid.uidByte[1], HEX);
  Serial.print(mfrc522_vao.uid.uidByte[2], HEX);
  Serial.println(mfrc522_vao.uid.uidByte[3], HEX);

  mfrc522_vao.PICC_HaltA();
  mfrc522_vao.PCD_StopCrypto1(); 

  while (Serial.available()) 
  {
    sv = Serial.read();
    Serial.println(sv);
    delay(200);
  }
  if (sv == '1') 
  {
    sv_vao.write(100); 
    delay(3000);
    sv_vao.write(0);
  }
  Serial.flush();
}

void the_ra() {
 Look for new cards
  if ( ! mfrc522_ra.PICC_IsNewCardPresent())
      return;
   Select one of the cards
  if ( ! mfrc522_ra.PICC_ReadCardSerial())
      return;
  Serial.print("co");
  Serial.print(mfrc522_ra.uid.uidByte[0], HEX);
  Serial.print(mfrc522_ra.uid.uidByte[1], HEX);
  Serial.print(mfrc522_ra.uid.uidByte[2], HEX);
  Serial.println(mfrc522_ra.uid.uidByte[3], HEX);

  mfrc522_ra.PICC_HaltA();
  mfrc522_ra.PCD_StopCrypto1();
  Serial.flush();
  
  while (Serial.available()) 
  {
      sv = Serial.read();
      Serial.println(sv);
      delay(200);
  }
  if (sv == '2') 
  {
      sv_ra.write(100); 
      delay(3000);
      sv_ra.write(0);
  }
}

void hien_thi(){
  if(digitalRead(A3)==0)
  {
          a = 1;
  }
  else
  {
    a = 0;
   }

   if(digitalRead(A2)==0)
  {
          b = 1;
  }
  else
  {
    b = 0;
   }
   if(digitalRead(A1)==0)
  {
          c = 1;
  }
  else
  {
    c= 0;
   }

   if(digitalRead(A0)==0)
  {
          d = 1;
  }
  else
  {
    d = 0;
  }

   count = a+b+c+d;

  if (count == 4) 
  {
    lcd.setCursor(0,1);
    lcd.print("Full slot, Sorry");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print(4 - count);
    lcd.print(" Slot available");
  }

 lcd.setCursor(3,0);
 lcd.print("UTC Parking");
}
