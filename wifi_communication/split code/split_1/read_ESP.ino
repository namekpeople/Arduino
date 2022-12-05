void read_ESP() {
  while (mySerial.available())
  {
    sv = mySerial.read();
    vao = sv.indexOf('1');
    ra = sv.indexOf('2');
  }
  if (vao>0)
  {
    sv_vao.write(100);
    delay(3000);
    sv_vao.write(0);
    vao = false;
  }
  else if (ra>0)
  {
    sv_ra.write(100);
    delay(3000);
    sv_ra.write(0);
    ra = false;
  }
}
