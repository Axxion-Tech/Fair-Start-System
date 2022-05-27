#include<SoftwareSerial.h>
#include<Servo.h>
Servo x;
int bttx=0;    //tx of bluetooth module is connected to pin 9 of arduino
int btrx=1;    //rx of bluetooth module is connected to pin 10 of arduino
SoftwareSerial bluetooth(bttx,btrx);
void setup()
{
  x.attach(10);        // servo is connected to pin 11 of arduino
  Serial.begin(115200);
  bluetooth.begin(115200);
}
void loop()
{
  if(bluetooth.available()>0)    //if bluetooth module is transmitting data
  {
    int pos=bluetooth.read(); // store the data in pos variable
    Serial.println(pos);
    x.write(pos);             //move servo head to the given position
  }
}