
/*******************************************************************************************
 *
 * Libraries included.
 *
 ******************************************************************************************/
 
/*===M5 Stack, Indicator Libraries and Definitions===*/
// M5 Stack system.
#include <M5Stack.h>
#include <SPIFFS.h> /*Enable images*/

// M5 Stack Wifi connection.
#include <WiFi.h>
#include <esp_wifi.h>
WiFiClient wifi_client;

// For Neopixel Turrellian RGB LED lamp strips 
#include <Adafruit_NeoPixel.h>

#define LED_PIN    3
#define LED_COUNT 600

// PubSubClient external library.
#include <PubSubClient.h> /* Manipulated for longer strings */
PubSubClient ps_client( wifi_client );

// JSON parsing library
#include <ArduinoJson.h>

// Extra, created by SEGP team
#include "Timer.h"
#define TEXTSIZE 2

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


/*******************************************************************************************
 *
 * Global Variables
 *
 ******************************************************************************************/

uint8_t guestMacAddress[6] = {0x84, 0xad, 0x8d, 0xc6, 0x83, 0x9c}; // Network of mobile phone device 

// Wifi settings
const char* ssid = "Curtis_Network_2";                 // Set name of Wifi Network
const char* password = "CapeTown123";                      // No password for UoB Guest


// MQTT Settings
const char* MQTT_clientname = "M5Stack"; // Make up a short name
const char* MQTT_sub_topic = "james_turrell"; // pub/sub topics
const char* MQTT_pub_topic = "james_turrell"; // You might want to create your own

// Please leave this alone - to connect to HiveMQ
const char* server = "broker.mqttdashboard.com";
const int port = 1883;

Timer publishing_timer(2000);


/*******************************************************************************************
 *
 * Setup() and Loop()
 *
 ******************************************************************************************/

// Standard, one time setup function.
void setup() 
{
    M5.begin();
    M5.Power.begin();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor( 10, 10 );
    M5.Lcd.setTextColor( WHITE );
    M5.Lcd.println("Reset,  connecting...");

    strip.begin();           
    strip.show();            
    strip.setBrightness(50); 

    Serial.println("*** RESET ***\n");
    connectButton();
    dispConnect();
}


// Standard, iterative loop function (main)
void loop() 
{
  checkConnection(); 
  
  if( M5.Lcd.getCursorY() > M5.Lcd.height() ) {
    M5.Lcd.fillScreen( BLACK );
    M5.Lcd.setCursor( 0, 10 );
  }
  
}

/*******************************************************************************************
 *
 * Functions
 *
 ******************************************************************************************/

/* Waits for initialisation of start of journey */
void connectButton() 
{
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);

  printBattery(); 
  
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setTextSize(TEXTSIZE);

  if(!SPIFFS.begin(true)){
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  M5.Lcd.drawPngFile(SPIFFS, "/Turrellian_LED_logo.png", 70, 40);

  displayTitle("HOLD C");
  while (!M5.BtnC.pressedFor(300)) {
    M5.Lcd.setCursor(10, 260);
    M5.Lcd.println("< CONNECT");
    M5.BtnC.read();
  }
  M5.Lcd.fillScreen(BLACK);
}


void displayTitle(String title) 
{
  //Creates header bar
  M5.Lcd.fillRect(0,0,350,35,0x39E7);
  
  //Prints Title
  M5.Lcd.setTextSize(TEXTSIZE);
  M5.Lcd.setCursor(30, 10);
  M5.Lcd.print(title);

  //Prints battery
  printBattery();
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setTextSize(TEXTSIZE);
}

void dispConnect()
{
  M5.Lcd.fillScreen(BLACK);
  displayTitle("CONNECTING");
  M5.Lcd.drawPngFile(SPIFFS, "/wifi.png", 5, 7);
  
  // Print WIFI and MQTT details
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf("Wifi Network:\n  ");
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println(ssid);

  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println("\nMQTT Topics:");
  M5.Lcd.printf(" -Sub: \n  ");
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println(MQTT_sub_topic);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.printf(" -Pub:\n  ");
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println(MQTT_pub_topic);

  // Displays connected as false
  M5.Lcd.setCursor(10, 200);
  M5.Lcd.print("Connected: ");
  M5.Lcd.setTextColor(RED);
  M5.Lcd.println("FALSE");
  
  // Sets up WiFi and MQTT
  setupWifiWithPassword();
  setupMQTT();
  
  // Once Connected change to true
  M5.Lcd.setCursor(10, 200);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.fillRect(10,200,240,40,BLACK);
  M5.Lcd.println("Conneted: TRUE");

  delay(2000);
  M5.Lcd.fillScreen(BLACK); 
  printBattery(); 
  displayTitle("Main Menu"); 
  M5.Lcd.drawPngFile(SPIFFS, "/wifi.png", 5, 7);
}

void printBattery()
{
  //Gets Battery level
  uint8_t bat = M5.Power.getBatteryLevel();
  //Prints battery bar
  M5.Lcd.fillRect(193, 10, 38, 15, WHITE);
  M5.Lcd.progressBar(195, 12, 33, 11, bat);
  M5.Lcd.setCursor(165, 14);
  M5.Lcd.setTextSize(0.5);
  //If charging print lightning bolt icon
  if(M5.Power.isCharging()){
    int centreX=212;
    int centreY=17;
    M5.Lcd.drawPixel(centreX+1,centreY-3,YELLOW);
    M5.Lcd.drawPixel(centreX,centreY-2,YELLOW);
    M5.Lcd.drawPixel(centreX+1,centreY-2,YELLOW);
    M5.Lcd.drawPixel(centreX-1,centreY-1,YELLOW);
    M5.Lcd.drawPixel(centreX,centreY-1,YELLOW);
    M5.Lcd.drawPixel(centreX-1,centreY,YELLOW);
    M5.Lcd.drawPixel(centreX,centreY,YELLOW);
    M5.Lcd.drawPixel(centreX+1,centreY,YELLOW);
    M5.Lcd.drawPixel(centreX,centreY+1,YELLOW);
    M5.Lcd.drawPixel(centreX+1,centreY+1,YELLOW);
    M5.Lcd.drawPixel(centreX-1,centreY+2,YELLOW);
    M5.Lcd.drawPixel(centreX,centreY+2,YELLOW);
    M5.Lcd.drawPixel(centreX-1,centreY+3,YELLOW);
  }
  //Prints charge percentage
  else{
    M5.Lcd.printf("%d%%",bat);
  }
}


void checkConnection() 
{
  //Checks if m5stack is connected
  if (!ps_client.connected()) {
    reconnect();
  }
  ps_client.loop();
}

void relaxationSequence() 
{
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


void activationSequence() 
{
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
  colorWipe(strip.Color(152, 251, 152), 0); // Pale_green
  colorWipe(strip.Color(143, 188, 143), 0); // Dark_sea_green
  colorWipe(strip.Color(60, 179, 113), 0); // Medium_sea_green
  colorWipe(strip.Color(128, 128, 0), 0); // Olive
  colorWipe(strip.Color(85, 107, 47), 0); // Dark_olive_green
  colorWipe(strip.Color(107, 142, 35), 0); // Olive_drab
  /*========================BLUE_4========================*/
  colorWipe(strip.Color(65, 105, 225), 0); // Royal_blue 
  colorWipe(strip.Color(0, 0, 255), 0); // Blue
  colorWipe(strip.Color(0, 0, 205), 0); // Medium_blue
  colorWipe(strip.Color(0, 0, 139), 0); // Dark_blue
  colorWipe(strip.Color(0, 0, 128), 0); // Navy
}

void colorWipe(uint32_t color, int wait) 
{
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void rainbow(int wait) 
{
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}


/*******************************************************************************************
 *
 * Helper functions after this...
 *
 ******************************************************************************************/


// Use this function to publish a message.  It currently
// checks for a connection, and checks for a zero length
// message.  Note, it doens't do anything if these fail.
//
// Note that, it publishes to MQTT_topic value
//
// Also, it doesn't seem to like a concatenated String
// to be passed in directly as an argument like:
// publishMessage( "my text" + millis() );
// So instead, pre-prepare a String variable, and then
// pass that.
void publishMessage( String message ) 
{

  if( ps_client.connected() ) {

    // Make sure the message isn't blank.
    if( message.length() > 0 ) {
      // Convert to char array
      char msg[ message.length() ];
      message.toCharArray( msg, message.length() );

      M5.Lcd.print(">> Tx: ");
      // Send
      ps_client.publish( MQTT_pub_topic, msg );
    }

  } else {
    Serial.println("Can't publish message: Not connected to MQTT :( ");
  }

}

// This is where we pick up messages from the MQTT broker.
// This function is called automatically when a message is
// received.
//
// Note that, it receives from MQTT_topic value.
//
// Note that, you will receive messages from yourself, if
// you publish a message, activating this function.

void callback(char* topic, byte* payload, unsigned int length) 
{
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String in_str = "";

  // Copy chars to a String for convenience.
  // Also prints to USB serial for debugging
  for (int i=0;i<length;i++) {
    in_str += (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();

  M5.Lcd.println("\n<< Rx: " );
  M5.Lcd.println( in_str );

  StaticJsonDocument<256> doc; 
  DeserializationError err = deserializeJson(doc, in_str); 

  if (err) {
     M5.Lcd.print("ERROR: "); 
     M5.Lcd.println(err.c_str());
     delay(3000);  
     M5.Lcd.fillScreen(BLACK); 
     printBattery(); 
     displayTitle("Main Menu");
     M5.Lcd.drawPngFile(SPIFFS, "/wifi.png", 5, 7);
     M5.Lcd.drawPngFile(SPIFFS, "/Turrellian_LED_logo.png", 70, 40);
     return; 
  }

  /* PARSE JSON FOR DESIRED MOOD */

   String desiredMood = doc["desired_mood"]; 

   if (desiredMood.equals("focused") || desiredMood.equals("excited") || desiredMood.equals("happy")){
     activationDisplay(); 
     activationSequence(); 
   } else if (desiredMood.equals("contented") || desiredMood.equals("serene") || desiredMood.equals("relaxed")){
     relaxationDisplay(); 
     relaxationSequence(); 
   } 


}

void activationDisplay() {
    M5.Lcd.fillScreen(BLACK); 
    printBattery(); 
    displayTitle("Main Menu");
    M5.Lcd.drawPngFile(SPIFFS, "/wifi.png", 5, 7);
    M5.Lcd.drawPngFile(SPIFFS, "/happy_emoji.png", 70, 40); 
}

void relaxationDisplay() {
    M5.Lcd.fillScreen(BLACK); 
    printBattery(); 
    displayTitle("Main Menu");
    M5.Lcd.drawPngFile(SPIFFS, "/wifi.png", 5, 7);
    M5.Lcd.drawPngFile(SPIFFS, "/relax_emoji.png", 70, 40);
}



/*******************************************************************************************
 *
 *
 * You shouldn't need to change any code below this point!
 *
 *
 *
 ******************************************************************************************/


void setupMQTT() 
{
    ps_client.setServer(server, port);
    ps_client.setCallback(callback);
}

void setupWifi() 
{
    byte mac[6];
    Serial.println("Original MAC address: " + String(WiFi.macAddress()));
    esp_base_mac_addr_set(guestMacAddress);
    Serial.println("Borrowed MAC address: " + String(WiFi.macAddress()));

    Serial.println("Connecting to network: " + String(ssid));
    WiFi.begin(ssid );
    while (WiFi.status() != WL_CONNECTED) delay(500);
    Serial.println("IP address allocated: " + String(WiFi.localIP()));
}

void setupWifiWithPassword() 
{
    byte mac[6];
    Serial.println("Original MAC address: " + String(WiFi.macAddress()));
    esp_base_mac_addr_set(guestMacAddress);
    Serial.println("Borrowed MAC address: " + String(WiFi.macAddress()));

    Serial.println("Connecting to network: " + String(ssid));
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) delay(500);
    Serial.println("IP address allocated: " + String(WiFi.localIP()));

}

void reconnect() 
{
   
  // Loop until we're reconnected
  while (!ps_client.connected()) {

    Serial.print("Attempting MQTT connection...");

    // Attempt to connect
    // Sometimes a connection with HiveMQ is refused
    // because an old Client ID is not erased.  So to
    // get around this, we just generate new ID's
    // every time we need to reconnect.
    String new_id = generateID();

    Serial.print("connecting with ID ");
    Serial.println( new_id );

    char id_array[ (int)new_id.length() ];
    new_id.toCharArray(id_array, sizeof( id_array ) );

    if (ps_client.connect( id_array ) ) {
      Serial.println("connected");

      // Once connected, publish an announcement...
      ps_client.publish( MQTT_pub_topic, "reconnected");
      // ... and resubscribe
      ps_client.subscribe( MQTT_sub_topic );
    } else {
      M5.Lcd.println(" - Coudn't connect to HiveMQ :(");
      M5.Lcd.println("   Trying again.");
      Serial.print("failed, rc=");
      Serial.print(ps_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  M5.Lcd.println("\n\n- Success!");
  M5.Lcd.println("Connected to Hive MQ"); 
}

String generateID() 
{

  String id_str = MQTT_clientname;
  id_str += random(0,9999);

  return id_str;
}
