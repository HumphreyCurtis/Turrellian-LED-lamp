#include <ArduinoJson.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 

//  const String input = "{\"sensor\":\"gps\",\"time\":1351824,\"data\":[48.756080,2.302038]}"; 
//  StaticJsonDocument<256> doc;  
//
//  DeserializationError err = deserializeJson(doc, input); 
//
//  if (err) {
//    Serial.print("ERROR: "); 
//    Serial.println(err.c_str()); 
//    return; 
//  }
//
//  const String sensor = doc["sensor"];
//  long time = doc["time"]; 
//  float lat = doc["data"][0]; 
//  float lon = doc ["data"][1]; 
//
//   Serial.println(sensor); 
//   Serial.println(time); 
//   Serial.println(lat, 6); 
//   Serial.println(lon, 6); 

   const String input = "{\"mood_id\":\"O0SBW0lT\",\"current_mood\":\"good\",\"desired_mood\":\"relaxed\"}"; 
   StaticJsonDocument<256> doc;
   Serial.println("====================="); 
   Serial.println("Before serialization");
   Serial.println(input);  

   DeserializationError err = deserializeJson(doc, input); 

   if (err) {
      M5.Lcd.print("ERROR: "); 
      M5.Lcd.println(err.c_str()); 
      return; 
   }

   String desiredMood = doc["desired_mood"]; 
   M5.Lcd.println(desiredMood); 

   if (desiredMood.equals("focused") || desiredMood.equals("excited") || desiredMood.equals("happy")){
    M5.Lcd.println("Upper-right quadrant of PAD model"); 
   } else if (desiredMood.equals("contented") || desiredMood.equals("serene") || desiredMood.equals("relaxed")){
    M5.Lcd.println("Lower-right quadrant of PAD model"); 
   }

   


   
  
}


void loop() {
  // put your main code here, to run repeatedly:

}
