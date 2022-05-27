#include<SoftwareSerial.h>
#include<Servo.h>
Servo x;
int bttx=0;    //tx of bluetooth module is connected to pin 0 of arduino
int btrx=1;    //rx of bluetooth module is connected to pin 1 of arduino
int pos = 0;    // variable to store the servo position
SoftwareSerial bluetooth(bttx,btrx);
void setup()
{
  x.attach(10);        // Left servo is connected to pin 9 of arduino
  x.write(90); 
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
      for (pos = 90; pos <= 190; pos += 5) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        x.write(pos);              // tell servo to go to position in variable 'pos'
        delay(1);                       // waits 1ms for the servo to reach the position
      }
    }
    else if (command==48) {
      Serial.println("Resetting");
      for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
        // in steps of 1 degree
        x.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);                  // waits 1ms for the servo to reach the position
      }
    }
  }
}