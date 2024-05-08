#define BLYNK_TEMPLATE_ID "TMPL6uubhiJDx"
#define BLYNK_TEMPLATE_NAME "Sistem Pompa Air Otomatis di Pertanian"
#define BLYNK_AUTH_TOKEN "2iN0SYAGOZl6DLlN30v0NdbKHumDf_Sp"
#define BLYNK_PRINT Serial

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

#define DHTPIN 15        
#define DHTTYPE DHT22    
#define SOIL_PIN 34      

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 4);  

#define RELAY_PIN 18     
#define PUMP_PIN 19 
const int PHOTO_PIN = 35;  
int lightThreshold = 500;

bool pumpStatus = false; 

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  lcd.setCursor(0, 1);
  lcd.print("==== Water Pump ====");
  delay(2000);  
}

void loop() {
  Blynk.run();
  delay(1000);  
  float humidity = dht.readHumidity();
  int temperature = dht.readTemperature();
  int soilMoisture = analogRead(SOIL_PIN);
  int lightSensor = analogRead(PHOTO_PIN);

  Serial.print("Temperature (C): ");
  Serial.print(temperature);
  Serial.print("Humidity (%): ");
  Serial.print(humidity);
  Serial.print("SoilMoisture: ");
  Serial.println(soilMoisture);
  Serial.print("Light Signal: ");
  Serial.println(lightSensor);

  lcd.clear(); 

  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 2);
  lcd.print("SoilMoisture: ");
  lcd.print(soilMoisture);
  lcd.print("%");

  lcd.setCursor(0, 3);
  if (lightSensor > lightThreshold){
    lcd.print("Light: Sedang");
  } else {
    lcd.print("Light: Terik");
  }
  delay(2000);

  // Controling the water pump based on temp, humidity, and soil moisture value
  if (soilMoisture < 50 && humidity < 60 && temperature >= 25) {
    if (!pumpStatus) { 
        digitalWrite(RELAY_PIN, HIGH); 
        digitalWrite(PUMP_PIN, HIGH);  

        Serial.println("Pompa air dihidupkan");
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.println("Pompa air dihidupkan");
        pumpStatus = true; 
    }
  } else {
    if (pumpStatus) {
        digitalWrite(RELAY_PIN, LOW); 
        digitalWrite(PUMP_PIN, LOW);  

        Serial.println("Pompa air dimatikan");
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.println("Pompa air dimatikan");
        pumpStatus = false; 
      }
  }

  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("  Pump Status: ");
  lcd.print(pumpStatus ? "On" : "Off");
  delay(1000);

  Blynk.virtualWrite(V0, humidity);
  Blynk.virtualWrite(V1, temperature);    
  Blynk.virtualWrite(V2, soilMoisture); 
  Blynk.virtualWrite(V3, lightSensor); 
}