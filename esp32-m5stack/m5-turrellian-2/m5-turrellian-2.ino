
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
#include "FastLED.h"
#include <pixeltypes.h>

#define LED_PIN     21
#define NUM_LEDS    600
#define BRIGHTNESS  200
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

// PubSubClient external library.
#include <PubSubClient.h> /* Manipulated for longer strings */
PubSubClient ps_client( wifi_client );

// JSON parsing library
#include <ArduinoJson.h>

// Extra, created by SEGP team
#include "Timer.h"
#define TEXTSIZE 2


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

    // Neopixel initialization
    FastLED.addLeds<WS2811,LED_PIN,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness( BRIGHTNESS ); 
    FastLED.clear(); 
    FastLED.show(); 

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

void relaxationSequence() {
  /*=======RED========*/
colourWipe(CRGB::Red, 30); 
colourWipe(CRGB::Tomato, 30);
colourWipe(CRGB::FireBrick, 30); 
colourWipe(CRGB::Crimson, 30);
  
  /*====PURPLE_BLUE===*/
colourWipe(CRGB::BlueViolet, 30); 
colourWipe(CRGB::Indigo, 30);
colourWipe(CRGB::MidnightBlue, 30); 
colourWipe(CRGB::Violet, 30);
  
  /*====YELLOW_RED====*/
colourWipe(CRGB::OrangeRed, 30); 
colourWipe(CRGB::Orange, 30);
colourWipe(CRGB::Tomato, 30); 
colourWipe(CRGB::PaleVioletRed, 30);

  /*====RED_PURPLE====*/
colourWipe(CRGB::Maroon, 30); 
colourWipe(CRGB::DarkRed, 30);
colourWipe(CRGB::Crimson, 30); 
colourWipe(CRGB::MediumVioletRed, 30);

}


void activationSequence() {
  /*====BLUE_GREEN====*/
colourWipe(CRGB::Turquoise, 30); 
colourWipe(CRGB::Teal, 30);
colourWipe(CRGB::Cyan, 30); 
colourWipe(CRGB::LightSeaGreen, 30);
 
/*======GREEN=======*/
colourWipe(CRGB::Green, 30); 
colourWipe(CRGB::LimeGreen, 30); 
colourWipe(CRGB::ForestGreen, 30); 
colourWipe(CRGB::PaleGreen, 30); 

/*======PURPLE======*/
colourWipe(CRGB::Purple, 30);
colourWipe(CRGB::Plum, 30);
colourWipe(CRGB::Orchid, 30);
colourWipe(CRGB::Magenta, 30);

/*=======BLUE=======*/
colourWipe(CRGB::Aquamarine, 30);
colourWipe(CRGB::Blue, 30);
colourWipe(CRGB::CadetBlue, 30); 
colourWipe(CRGB::DarkBlue, 30); 
}

void colourWipe(CRGB value, int wait) {
  for (int i=0; i<NUM_LEDS; i++) {
        fill_solid(leds, i, value); 
        FastLED.show(); 
        FastLED.delay(wait); 
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
