#include <FastLED.h>
#include<SoftwareSerial.h>
#include <Servo.h>

#define LED_PIN    8
#define NUM_LEDS    25

Servo l;
Servo r;
int bttx=0; // tx of bluetooth module is connected to pin 0 of arduino
int btrx=1; // rx of bluetooth module is connected to pin 1 of arduino
int lStartPosition = 180; // Left servo start position (angle)
int lEndPosition = 90; // Left servo end position (angle)
int rStartPosition = 0; // Right servo start position (angle)
int rEndPosition = 90; // Right servo end position (angle)

SoftwareSerial bluetooth(bttx,btrx); // Setup bluetooth
CRGB leds[NUM_LEDS]; // Setup LEDs

void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); // Arrange LED Strip
  fill_solid( leds, NUM_LEDS, CRGB(255, 0, 0) ); // Set all LEDs to red
  FastLED.show();
  l.attach(10); // Left servo is connected to pin 10 of arduino
  l.write(lStartPosition); // Set left inital servo position to 90
  r.attach(9); // Right servo is connected to pin 10 of arduino
  r.write(rStartPosition); // Set left inital servo position to 180
  Serial.begin(115200); // Begin serial at 115200 baud rate
  bluetooth.begin(115200); // Begin bluetooth at 115200 baud rate
}
void loop()
{
  if(bluetooth.available()>0) // If bluetooth module is transmitting data
  {
    int command=bluetooth.read(); // Store the command in a variable
    Serial.println(command); // Print command out
    if(command==50){ // When the command is utf-8 "2"
      Serial.println("Countdown");
      fill_solid( leds, NUM_LEDS, CRGB(0, 0, 0) ); // Turn off all LEDs
      FastLED.show();
      delay(1);
      leds[0] = CRGB(255, 140, 0); // Show yellow LEDs in a sequence of five at a time
      leds[1] = CRGB(255, 140, 0);
      leds[2] = CRGB(255, 140, 0);
      leds[3] = CRGB(255, 140, 0);
      leds[4] = CRGB(255, 140, 0);
      leds[20] = CRGB(255, 140, 0);
      leds[21] = CRGB(255, 140, 0);
      leds[22] = CRGB(255, 140, 0);
      leds[23] = CRGB(255, 140, 0);
      leds[24] = CRGB(255, 140, 0);
      FastLED.show();
      delay(1000);
      leds[5] = CRGB(255, 140, 0); 
      leds[6] = CRGB(255, 140, 0);
      leds[7] = CRGB(255, 140, 0);
      leds[8] = CRGB(255, 140, 0);
      leds[9] = CRGB(255, 140, 0);
      leds[15] = CRGB(255, 140, 0);
      leds[16] = CRGB(255, 140, 0);
      leds[17] = CRGB(255, 140, 0);
      leds[18] = CRGB(255, 140, 0);
      leds[19] = CRGB(255, 140, 0);
      FastLED.show();
      delay(1000);
      leds[10] = CRGB(255, 140, 0);
      leds[11] = CRGB(255, 140, 0);
      leds[12] = CRGB(255, 140, 0);
      leds[13] = CRGB(255, 140, 0);
      leds[14] = CRGB(255, 140, 0);
      FastLED.show();
    }
    if(command==49){ // When the command is utf-8 "1"
      Serial.println("Firing");
      l.write(lEndPosition); // Move servos open
      r.write(rEndPosition);
      fill_solid( leds, NUM_LEDS, CRGB(0, 255, 0) ); // Turn all LED's green
      FastLED.show();
      delay(100);
    }
    else if (command==48) { // When the command is utf-8 "0"
      Serial.println("Resetting");
      l.write(lStartPosition); // Move servos closed
      r.write(rStartPosition);
      fill_solid( leds, NUM_LEDS, CRGB(255, 0, 0) ); // Turn all LEDs red
      FastLED.show();
      delay(100);
    }
  }
}