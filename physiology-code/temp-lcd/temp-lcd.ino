#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int sensorPin = A1; 
const float baselineTemp = 18.0;
float temperature = 0; 

void setup() {
  lcd.begin(16,2);  
  Serial.begin(9600); 
  for(int pinNumber = 2; pinNumber < 5; pinNumber++){
    pinMode(pinNumber, OUTPUT); 
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  lcd.clear();
  lcd.print("Temp C: "); 
  lcd.print(temperature); 
  
  int sensorVal = analogRead(sensorPin); 
  Serial.print("Sensor Value: "); 
  Serial.print(sensorVal); 

  float voltage = (sensorVal/1024.0) * 5.0; 
  Serial.print(", Volts: "); 
  Serial.print(voltage); 

  Serial.print(", degrees C: "); 
  temperature = (voltage - .5) * 100; 
  Serial.println(temperature);

  delay(2000); 
}
