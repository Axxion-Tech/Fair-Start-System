#include <FastLED.h>
#include <VarSpeedServo.h>

#define LED_PIN 8
#define NUM_LEDS 25

VarSpeedServo l;
VarSpeedServo r;
int lStartPosition = 180; // Left servo start position (angle)
int lEndPosition = 90; // Left servo end position (angle)
int rStartPosition = 0; // Right servo start position (angle)
int rEndPosition = 90; // Right servo end position (angle)

CRGB leds[NUM_LEDS]; // Setup LEDs

void rainbow_wave(uint8_t thisSpeed, uint8_t deltaHue) {      // The fill_rainbow call doesn't support brightness levels.
  uint8_t thisHue = beatsin8(thisSpeed,0,255);                // A simple rainbow wave.
  fill_rainbow(leds, NUM_LEDS, thisHue, deltaHue);            // Use FastLED's fill_rainbow routine.
}
void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); // Arrange LED Strip
  fill_solid( leds, NUM_LEDS, CRGB(255, 0, 0) ); // Set all LEDs to red
  FastLED.show();
  l.attach(3); // Left servo is connected to pin 10 of arduino
  l.write(lStartPosition); // Set left inital servo position to 90
  r.attach(2); // Right servo is connected to pin 10 of arduino
  r.write(rStartPosition); // Set left inital servo position to 180
  Serial.begin(9600); // Begin serial at 9600 baud rate
}
void loop()
{
  if(Serial.available()>0) // If bluetooth module is transmitting data
  {
    int command = Serial.read(); // Store the command in a variable
    Serial.println("Received command: " + String(command)); // Print command out
    if (command==48) { // When the command is utf-8 "0"
      Serial.println("Resetting");
      r.write(rStartPosition, 20);
      l.write(lStartPosition, 20); // Move servos closed
      fill_solid( leds, NUM_LEDS, CRGB(255, 0, 0) ); // Turn all LEDs red
      FastLED.show();
      delay(100);
    }
    else if (command==49){ // When the command is utf-8 "1"
      Serial.println("Firing");
      l.write(lEndPosition); // Move servos open
      r.write(rEndPosition);
      fill_solid( leds, NUM_LEDS, CRGB(0, 255, 0) ); // Turn all LED's green
      FastLED.show();
      delay(100);
    }
    else if(command==50){ // When the command is utf-8 "2"
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
    else if (command==51){ // When the command is utf-8 "3"
      Serial.println("Red LEDs");
      fill_solid( leds, NUM_LEDS, CRGB(255, 0, 0) ); // Set all LEDs to red
      FastLED.show();
      delay(100);
    }
    else if (command==52){ // When the command is utf-8 "4"
      Serial.println("Rainbow Wave LEDs");
      while (command!=53) { // Send utf-8 "5" to stop rainbow and reset to red
        command = Serial.read();
        Serial.println("Rainbow loop: " + String(command));
        rainbow_wave(20, 15);                                      // Speed, delta hue values.
        FastLED.show();
        delay(70);
      }
      delay(100);
      fill_solid( leds, NUM_LEDS, CRGB(255, 0, 0) ); // Turn off all LEDs
      FastLED.show();
    }
  }
}