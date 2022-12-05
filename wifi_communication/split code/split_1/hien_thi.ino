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
