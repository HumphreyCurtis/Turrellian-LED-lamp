

/*===M5 Stack, Indicator Libraries and Definitions===*/
// M5 Stack system.
#include <M5Stack.h>
#include <SPIFFS.h> /*Enable images*/

#define TEXTSIZE 2
#define TITLECOLOUR WHITE 

void setup() {
  
  M5.begin();
  M5.Power.begin();
  M5.Lcd.fillScreen(BLACK);
//  M5.Lcd.setCursor( 10, 10 );
//  M5.Lcd.setTextColor( WHITE );

  if(!SPIFFS.begin(true)){
    Serial.println("SPIFFS Mount Failed");
    return;
  } 
  displayTitle("   Battery:"); 
  M5.Lcd.drawPngFile(SPIFFS, "/wifi.png", 5, 7);
  M5.Lcd.drawPngFile(SPIFFS, "/happy_emoji.png", 70, 40);
    
}

void loop() {
  // put your main code here, to run repeatedly:

}

void displayTitle(String title) {
  //Creates header bar
  M5.Lcd.fillRect(0,0,350,35,0x39E7);
  //Prints Title
  M5.Lcd.setTextSize(TEXTSIZE);
  M5.Lcd.setCursor(30, 10);
  M5.Lcd.setTextColor(TITLECOLOUR, 0x39E7);
  M5.Lcd.print(title);
  //Prints battery
  printBattery();
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setTextSize(TEXTSIZE);
}

void printBattery(){
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
