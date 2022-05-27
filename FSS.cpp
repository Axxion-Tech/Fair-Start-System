#include<SoftwareSerial.h>
#include<Servo.h>
Servo l;
Servo r;
int bttx=0;    //tx of bluetooth module is connected to pin 0 of arduino
int btrx=1;    //rx of bluetooth module is connected to pin 1 of arduino
int pos = 0;    // variable to store the servo position
SoftwareSerial bluetooth(bttx,btrx);
void setup()
{
  l.attach(10);        // Left servo is connected to pin 9 of arduino
  l.write(-83); 
  r.attach(9);        // Right servo is connected to pin 9 of arduino
  r.write(103);
  Serial.begin(115200);
  bluetooth.begin(115200);
}
void loop()
{
  if(bluetooth.available()>0)    //if bluetooth module is transmitting data
  {
    int command=bluetooth.read(); // store the data in pos variable
    if(command==49){
      Serial.println("Firing");
      for (pos = 103; pos <= 166; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        r.write(pos);              // tell servo to go to position in variable 'pos'
        delay(0.5);                       // waits 1ms for the servo to reach the position
      }
      for (pos = 160; pos <= 76; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        l.write(pos);              // tell servo to go to position in variable 'pos'
        delay(0.5);                       // waits 1ms for the servo to reach the position
      }
    }
    else if (command==48) {
      Serial.println("Resetting");
      for (pos = 166; pos >= 103; pos -= 1) { // goes from 180 degrees to 0 degrees
        // in steps of 1 degree
        r.write(pos);              // tell servo to go to position in variable 'pos'
        delay(5);                  // waits 1ms for the servo to reach the position
      }
      for (pos = 76; pos >= 13; pos -= 1) { // goes from 180 degrees to 0 degrees
        // in steps of 1 degree
        l.write(pos);              // tell servo to go to position in variable 'pos'
        delay(5);                  // waits 1ms for the servo to reach the position
      }
    }
  }
}