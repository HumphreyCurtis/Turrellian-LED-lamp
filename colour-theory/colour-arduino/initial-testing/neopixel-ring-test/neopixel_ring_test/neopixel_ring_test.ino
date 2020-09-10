// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED. 
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    26

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 12

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

//void loop() {
//  // Fill along the length of the strip in various colors...
//  colorWipe(strip.Color(255,   0,   0), 50); // Red
//  colorWipe(strip.Color(  0, 255,   0), 50); // Green
//  colorWipe(strip.Color(  0,   0, 255), 50); // Blue
//
//  // Do a theater marquee effect in various colors...
//  theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
//  theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
//  theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness
//
//  rainbow(10);             // Flowing rainbow cycle along the whole strip
//  theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
//}

void loop() {

  activationSequence(); 
  
}

void relaxationSequence() {
  /*======================RED====================*/
  colorWipe(strip.Color(255, 160, 122), 0); // Light_salmon
  colorWipe(strip.Color(250, 128, 114), 0); // Salmon
  colorWipe(strip.Color(233, 150, 122), 0); // Dark_salmon
  colorWipe(strip.Color(240, 128, 128), 0); // Light_coral
  /*=====================PURPLE_BLUE==================*/
  colorWipe(strip.Color(25, 25, 112), 0); // Midnight_blue
  colorWipe(strip.Color(138, 43, 226), 0); // Blue_violet
  colorWipe(strip.Color(75, 0, 130), 0); // Indigo
  colorWipe(strip.Color(123, 104, 238), 0); // Medium_slate_blue
  /*======================YELLOW_RED==================*/
  colorWipe(strip.Color(255, 79, 0), 0); // International_orange
  colorWipe(strip.Color(249, 77, 0), 0); // Tangelo
  colorWipe(strip.Color(236, 88, 0), 0); // Persimmon
  colorWipe(strip.Color(203, 65, 11), 0); // Sinopia
  /*======================RED_PURPLE====================*/ 
  colorWipe(strip.Color(219, 112, 147), 0); // Pale_violet_red
  colorWipe(strip.Color(128, 0, 0), 0); // Maroon 
  colorWipe(strip.Color(220, 20, 60), 0); // Crimson
  colorWipe(strip.Color(141, 78, 133), 0); // Razzmic_berry
  
  /*======================RED_2====================*/
  colorWipe(strip.Color(205, 92, 92), 0); // Indian_red
  colorWipe(strip.Color(178, 34, 34), 0); // Fire_brick
  colorWipe(strip.Color(255, 0, 0), 0); // Red
  colorWipe(strip.Color(200, 0, 0), 0); // Strong_red
  /*=====================PURPLE_BLUE_2==================*/
  colorWipe(strip.Color(106, 90, 205), 0); // Slate_blue
  colorWipe(strip.Color(72, 61, 139), 0); // Dark_slate_blue
  colorWipe(strip.Color(90, 79, 207), 0); // Iris
  colorWipe(strip.Color(82, 24, 250), 0); // Han_purple
  /*======================YELLOW_RED_2==================*/
  colorWipe(strip.Color(251, 79, 20), 0); // Orioles_orange
  colorWipe(strip.Color(226, 88, 0), 0); // Willpower_orange
  colorWipe(strip.Color(226, 114, 91), 0); // Terra_cotta
  colorWipe(strip.Color(255, 117, 24), 0); // Pumpkin 
  /*======================RED_PURPLE_2====================*/ 
  colorWipe(strip.Color(142, 58, 89), 0); // Twilight_lavender
  colorWipe(strip.Color(132, 63, 91), 0); // Deep_ruby
  colorWipe(strip.Color(135, 50, 96), 0); // Boysen_berry
  colorWipe(strip.Color(135, 38, 87), 0); // Dark_raspberry
   
  /*======================RED_3====================*/
  colorWipe(strip.Color(203, 51, 59), 0); // Crimson
  colorWipe(strip.Color(179, 21, 21), 0); // Carnelian
  colorWipe(strip.Color(237, 41, 57), 0); // Imperial 
  colorWipe(strip.Color(193, 51, 17), 0); // Regency
  /*=====================PURPLE_BLUE_3==================*/
  colorWipe(strip.Color(0, 15, 137), 0); // Phthalo_blue
  colorWipe(strip.Color(76, 40, 130), 0); // Spanish_violet
  colorWipe(strip.Color(136, 120, 195), 0); // Ube
  colorWipe(strip.Color(96, 80, 220), 0); // Majorelle_blue 
  /*======================YELLOW_RED_3==================*/
  colorWipe(strip.Color(255, 99, 71), 0); // Tomato
  colorWipe(strip.Color(255, 69, 0), 0); // Yellow_red
  colorWipe(strip.Color(250, 128, 114), 0); // Salmon 
  /*======================RED_PURPLE_3====================*/ 
  colorWipe(strip.Color(102, 2, 60), 0); // Tyrian_purple
  colorWipe(strip.Color(183, 132, 167), 0); // Opera_mauve 

  /*======================RED_4====================*/
  colorWipe(strip.Color(139, 0, 0), 0); // Dark_red 
  colorWipe(strip.Color(255, 99, 71), 0); // Tomato
  colorWipe(strip.Color(255, 69, 0), 0); // Orange_red
}


void activationSequence() {
    /*====================BLUE_GREEN===================*/
  colorWipe(strip.Color(95, 158, 160), 0); // Cadet_blue
  colorWipe(strip.Color(176, 224, 230), 0); // Powder_blue
  colorWipe(strip.Color(0, 165, 156), 0); // Munsell
  colorWipe(strip.Color(0, 128, 128), 0); // Teal
    /*==================GREEN==================*/
  colorWipe(strip.Color(124, 242, 0), 0); // Lawn_green
  colorWipe(strip.Color(127, 255, 0), 0); // Chartreuse
  colorWipe(strip.Color(50, 205, 50), 0); // Lime_green
  colorWipe(strip.Color(0, 255, 0), 0); // Lime 
    /*===================PURPLE=====================*/
  colorWipe(strip.Color(230, 230, 250), 0); // Lavender
  colorWipe(strip.Color(216, 191, 216), 0); // Thistle
  colorWipe(strip.Color(221, 160, 221), 0); // Plum 
  colorWipe(strip.Color(238, 130, 228), 0); // Violet
    /*========================BLUE========================*/
  colorWipe(strip.Color(95, 158, 160), 0); // Alice_blue
  colorWipe(strip.Color(230, 230, 250), 0); // Lavender
  colorWipe(strip.Color(176, 224, 230), 0); // Powder_blue
  colorWipe(strip.Color(173, 216, 230), 0); // Light_blue


  /*====================BLUE_GREEN_2===================*/
  colorWipe(strip.Color(0, 255, 255), 0); // Cyan
  colorWipe(strip.Color(64, 224, 208), 0); // Turquoise
  colorWipe(strip.Color(32, 178, 170), 0); // Light_sea_green
  colorWipe(strip.Color(58, 176, 158), 0); // Keppel
    /*==================GREEN_2==================*/
  colorWipe(strip.Color(34, 139, 34), 0); // Forest_green
  colorWipe(strip.Color(0, 128, 0), 0); // Green
  colorWipe(strip.Color(0, 100, 0), 0); // Darkgreen
  colorWipe(strip.Color(173, 255, 47), 0); // Green_yellow
    /*===================PURPLE_2=====================*/
  colorWipe(strip.Color(218, 112, 214), 0); // Orchid
  colorWipe(strip.Color(255, 0, 255), 0); // Fuchsia
  colorWipe(strip.Color(255, 0, 255), 0); // Magenta
  colorWipe(strip.Color(186, 85, 211), 0); // Medium orchid
    /*========================BLUE_2========================*/
  colorWipe(strip.Color(135, 206, 250), 0); // Light_sky_blue
  colorWipe(strip.Color(0, 191, 255), 0); // Deep_sky_blue
  colorWipe(strip.Color(135, 206, 235), 0); // Sky_blue
  colorWipe(strip.Color(176, 196, 222), 0); // Light_steel_blue

  
  /*====================BLUE_GREEN_3===================*/
  colorWipe(strip.Color(10, 186, 181), 0); // Tiffany_blue
  colorWipe(strip.Color(17, 100, 180), 0); // Green_blue
  colorWipe(strip.Color(10, 200, 100), 0); // Green_blue
  colorWipe(strip.Color(10, 200, 50), 0); // Green_blue
  colorWipe(strip.Color(10, 180, 120), 0); // Green_blue
  /*==================GREEN_3==================*/
  colorWipe(strip.Color(154, 295, 50), 0); // Yellow_green
  colorWipe(strip.Color(0, 255, 127), 0); // Spring_green
  colorWipe(strip.Color(0, 250, 154), 0); // Medium_spring_green
  colorWipe(strip.Color(144, 238, 144), 0); // Light_green
  /*===================PURPLE_3=====================*/ 
  colorWipe(strip.Color(147, 112, 219), 0); // Medium purple
  colorWipe(strip.Color(138, 43, 226), 0); // Blue violet
  colorWipe(strip.Color(148, 0, 211), 0); // Dark violet
  colorWipe(strip.Color(153, 50, 204), 0); // Dark orchid 
  colorWipe(strip.Color(139, 0, 139), 0); // Dark magenta
  colorWipe(strip.Color(128, 0, 128), 0); // Purple 
  /*========================BLUE_3========================*/
  colorWipe(strip.Color(30, 144, 255), 0); // Dodger_blue
  colorWipe(strip.Color(100, 149, 237), 0); // Corn_flower_blue
  colorWipe(strip.Color(70, 130, 180), 0); // Steel_blue
  colorWipe(strip.Color(95, 158, 160), 0); // Cadet_blue

  
    /*==================GREEN_4==================*/
  colorWipe(strip.Color(152, 251, 152), 200); // Pale_green
  colorWipe(strip.Color(143, 188, 143), 200); // Dark_sea_green
  colorWipe(strip.Color(60, 179, 113), 200); // Medium_sea_green
  colorWipe(strip.Color(128, 128, 0), 200); // Olive
  colorWipe(strip.Color(85, 107, 47), 200); // Dark_olive_green
  colorWipe(strip.Color(107, 142, 35), 200); // Olive_drab
  /*========================BLUE_4========================*/
  colorWipe(strip.Color(65, 105, 225), 200); // Royal_blue 
  colorWipe(strip.Color(0, 0, 255), 200); // Blue
  colorWipe(strip.Color(0, 0, 205), 200); // Medium_blue
  colorWipe(strip.Color(0, 0, 139), 200); // Dark_blue
  colorWipe(strip.Color(0, 0, 128), 200); // Navy
}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
