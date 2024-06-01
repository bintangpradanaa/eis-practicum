#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define buzzer 4

LiquidCrystal_I2C lcd(0x27, 16, 2);

int valorsensorgas;
int LED = 7;

// Tentukan batas bawah dan atas untuk deteksi gas
const int gasThresholdLow = 300;  
const int gasThresholdHigh = 1000; 

void setup() { 
  pinMode(LED, OUTPUT);
  lcd.init(); 
  lcd.backlight(); 
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  valorsensorgas = analogRead(A1);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Gas:");
  lcd.print(valorsensorgas, 1); 
  Serial.print(valorsensorgas);
  Serial.println();

  // Cek apakah nilai sensor gas berada di luar rentang tertentu
  if (valorsensorgas < gasThresholdLow || valorsensorgas > gasThresholdHigh) {
    digitalWrite(LED, HIGH); // Nyalakan LED
    tone(buzzer, 500); // Bunyi buzzer
    scrollText("GAS BERBAHAYA!"); 
  } else {
    digitalWrite(LED, LOW); // Matikan LED
    noTone(buzzer); // Matikan buzzer
    lcd.setCursor(0, 1);
    lcd.print("                "); 
  }
  delay(1000);
}

void scrollText(String message) {
  int len = message.length();
  // Scroll text
  for (int pos = 0; pos <= 16; pos++) {
    lcd.setCursor(0, 0); 
    lcd.print("Sensor Gas:");
    lcd.print(valorsensorgas, 1); 

    lcd.setCursor(16 - pos, 1);
    lcd.print(message);
    if (pos > 0) {
      lcd.setCursor(16 - pos - 1, 1);
      lcd.print(" ");
    }
    delay(200); 
  }
}
