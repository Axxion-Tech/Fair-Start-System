#include<SoftwareSerial.h>
#include <VarSpeedServo.h>

VarSpeedServo l;
VarSpeedServo r;
int bttx=0; //tx of bluetooth module is connected to pin 0 of arduino
int btrx=1; //rx of bluetooth module is connected to pin 1 of arduino
int pos = 0; // variable to store the servo position
int lStartPosition = 180;
int lEndPosition = 90;
int rStartPosition = 0;
int rEndPosition = 90;

SoftwareSerial bluetooth(bttx,btrx);
void setup()
{
  l.attach(10); // Left servo is connected to pin 10 of arduino
  l.write(lStartPosition); // Set left inital servo position to 90
  r.attach(9); // Right servo is connected to pin 10 of arduino
  r.write(rStartPosition); // Set left inital servo position to 180
  Serial.begin(115200);
  bluetooth.begin(115200);
}
void loop()
{
  if(bluetooth.available()>0) //if bluetooth module is transmitting data
  {
    int command=bluetooth.read(); // store the data in pos variable
    if(command==49){
      Serial.println("Firing");
      l.write(lEndPosition);
      r.write(rEndPosition);
      delay(100);
    //   for (pos = 90; pos <= 190; pos += 5) { // goes from 0 degrees to 180 degrees
    //     // in steps of 1 degree
    //     l.write(pos);              // tell servo to go to position in variable 'pos'
    //     delay(1);                       // waits 1ms for the servo to reach the position
    //   }
    }
    else if (command==48) {
      Serial.println("Resetting");
      l.write(lStartPosition, 30, false);
      // for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
      //   // in steps of 1 degree
      //   l.write(pos);              // tell servo to go to position in variable 'pos'
      //   delay(20);                  // waits 20ms for the servo to reach the position
      // }
      r.write(rStartPosition, 30, false);
      // for (pos = 90; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
      //   // in steps of 1 degree
      //   r.write(pos);              // tell servo to go to position in variable 'pos'
      //   delay(20);                  // waits 20ms for the servo to reach the position
      // }
    }
  }
}