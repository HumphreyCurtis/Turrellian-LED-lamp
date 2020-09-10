#include <FastLED.h>
#include <pixeltypes.h>

#define LED_PIN     5
#define NUM_LEDS    600
#define BRIGHTNESS  100
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
}


void loop() {

    relaxationSequence(); 

}

void relaxationSequence() {
  /*=======RED========*/
colourWipe(CRGB::Red, 10); 
colourWipe(CRGB::Tomato, 10);
colourWipe(CRGB::FireBrick, 10); 
colourWipe(CRGB::Crimson, 10);
  
  /*====PURPLE_BLUE===*/
colourWipe(CRGB::BlueViolet, 10); 
colourWipe(CRGB::Indigo, 10);
colourWipe(CRGB::MidnightBlue, 10); 
colourWipe(CRGB::Violet, 10);
  
  /*====YELLOW_RED====*/
colourWipe(CRGB::OrangeRed, 10); 
colourWipe(CRGB::Orange, 10);
colourWipe(CRGB::Tomato, 10); 
colourWipe(CRGB::PaleVioletRed, 10);

  /*====RED_PURPLE====*/
colourWipe(CRGB::Maroon, 10); 
colourWipe(CRGB::DarkRed, 10);
colourWipe(CRGB::Crimson, 10); 
colourWipe(CRGB::MediumVioletRed, 10);

}

void activationSequence() {
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
