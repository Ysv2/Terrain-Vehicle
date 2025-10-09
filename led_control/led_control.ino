#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     2

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 14

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t warm_white = strip.Color(255, 200, 80);
uint32_t very_warm_white = strip.Color(255, 180, 40);
uint32_t neutral_white = strip.Color(255, 240, 200);

uint32_t red = strip.Color(255, 0, 0);

void setup() {
  // put your setup code here, to run once:
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
  // strip.setPixelColor(n, red, green, blue, white);
  // put your main code here, to run repeatedly:
  // strip.setPixelColor(0, 0, 0, 0, 127);
  // strip.setPixelColor(1, 0, 0, 0, 127);
  // strip.setPixelColor(2, 0, 0, 0, 127);
  // strip.setPixelColor(3, 0, 0, 0, 127);
  // strip.setPixelColor(4, 0, 0, 0, 127);
  // strip.setPixelColor(5, 0, 0, 0, 127);
  // strip.setPixelColor(6, 0, 0, 0, 127);

  // for (int i = 0; i < LED_COUNT; i++) {
  //   strip.setPixelColor(i, 255, 200, 80);
  // }

  //! Set led to specific colour
  // strip.fill(red, 0, strip.numPixels() - 1);
  // strip.fill(red, 0, 7);
  // strip.fill(warm_white, 7, strip.numPixels() - 1);
  // strip.show();  

  strip.clear(); //! Off leds
}
