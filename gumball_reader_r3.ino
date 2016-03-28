#include <Wiegand.h>
#include <Adafruit_NeoPixel.h>

// -------------
// Constants
// -------------


// -------------
// Variables
// -------------
volatile boolean DebounceTick = false;
boolean SecondTick = false;
int SecondTimerCount = 0;
int InactivityTimerCount = 0;

boolean  CardRead = false;
boolean  ValidCard = false;  // Only valid if CardRead is also true
int      NumCardBits;
unsigned long CardData;
uint16_t CardNumber;


// -------------
// Hardware Objects
// -------------
WIEGAND wg;

#define PIN 6
#define NUMPIXELS 12
#define BUTTON 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// -------------
// Arduino Entry points
// -------------
void setup () {
  Serial.begin(9600);
  // Configure the hardware
  wg.begin();
  pixels.begin(); // This initializes the NeoPixel library.

  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);
  
}

// Note: The Wiegand library must be polled constantly in order to find the start of a transmission
//       so we don't put any delaying activities in the main loop while we are polling for new card
//       activity.
void loop () {
  // Look for input from the card reader
  if (wg.available()) {
    NumCardBits = wg.getWiegandType();
    CardData = wg.getCode();

    Serial.print("Wiegand HEX = ");
    Serial.print(CardData, HEX);
    Serial.print(", DECIMAL = ");
    Serial.print(CardData);
    Serial.print(", Type W");
    Serial.println(NumCardBits);

    if (NumCardBits == 26) {
      SetLedOutput(true);
      digitalWrite(5, LOW);
      delay(100);
      digitalWrite(5, HIGH);
    } else {
      SetLedOutput(false);
    }
    delay(200);
    SetLedOutput(false);
  }
  if (digitalRead(BUTTON) == LOW) {
    delay(250);
    pixels.setBrightness(255);
    rainbowCycle(3);
    SetLedOutput(false);
  }
}

// -------------
// Subroutines
// -------------


void SetLedOutput(boolean b) {
  if (b) {
    pixels.setBrightness(255);
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 150, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  } else {
    pixels.setBrightness(30);
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 150)); // Moderately bright blue color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }
}

/**
   Color climb function
 **/
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256 * 10; j++) { // 10 cycles of all colors on wheel
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
