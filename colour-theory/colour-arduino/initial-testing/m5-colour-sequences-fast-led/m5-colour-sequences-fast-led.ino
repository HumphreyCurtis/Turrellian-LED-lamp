/*
    Please install FastLED library first.
    In arduino library manage search FastLED
 */
#include <M5Stack.h>
#include "FastLED.h"
#include <pixeltypes.h>

#define Neopixel_PIN    21
#define NUM_LEDS    600

CRGB leds[NUM_LEDS];
//uint8_t gHue = 0;
//static TaskHandle_t FastLEDshowTaskHandle = 0;
//static TaskHandle_t userTaskHandle = 0;

void setup() {
  M5.begin();
  M5.Power.begin();

  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(YELLOW); M5.Lcd.setTextSize(2); M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("Neopixel Example");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(0, 25);
  M5.Lcd.println("Display activation cycle");

  // Neopixel initialization
  FastLED.addLeds<WS2811,Neopixel_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(10);
}

void loop()
{
/*====BLUE_GREEN====*/
colourWipe(CRGB::Turquoise, 10); 
colourWipe(CRGB::Teal, 10);
colourWipe(CRGB::Cyan, 10); 
colourWipe(CRGB::LightSeaGreen, 10);
 
/*======GREEN=======*/
colourWipe(CRGB::Green, 10); 
colourWipe(CRGB::LimeGreen, 10); 
colourWipe(CRGB::ForestGreen, 10); 
colourWipe(CRGB::PaleGreen, 10); 

/*======PURPLE======*/
colourWipe(CRGB::Purple, 10);
colourWipe(CRGB::Plum, 10);
colourWipe(CRGB::Orchid, 10);
colourWipe(CRGB::Magenta, 10);

/*=======BLUE=======*/
colourWipe(CRGB::Aquamarine, 10);
colourWipe(CRGB::Blue, 10);
colourWipe(CRGB::CadetBlue, 10); 
colourWipe(CRGB::DarkBlue, 10); 
}

void colourWipe(CRGB value, int wait) {
  for (int i=0; i<NUM_LEDS; i++) {
        fill_solid(leds, i, value); 
        FastLED.show(); 
        FastLED.delay(wait); 
  }
}
