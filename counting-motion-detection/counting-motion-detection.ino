#include <LiquidCrystal_I2C.h>

// Inisialisasi alamat LCD 16x2 pada I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inisialisasi pin PIR
int pirPin = 12;
int count = 0; // Variabel untuk menghitung jumlah deteksi gerakan

void setup() {
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  
  // Inisialisasi pin PIR sebagai input
  pinMode(pirPin, INPUT);

  // Menampilkan serial monitor
  Serial.begin(9600); 
  Serial.println("No Motion Detected!");

  // Tampilkan pesan awal di LCD
  lcd.setCursor(0,0);
  lcd.print("No Motion Detect!");
}

void loop() {
  // Baca nilai dari sensor PIR
  int motion = digitalRead(pirPin);

  // Jika gerakan terdeteksi dan belum ada gerakan yang sedang terdeteksi sebelumnya
  if (motion == HIGH) {
    count++; // Tambahkan nilai count

    // Menampilkan pesan ke serial monitor
    Serial.print("Motion Detect = ");
    Serial.println(count);
 
    lcd.clear(); // Hapus tampilan sebelumnya
    lcd.setCursor(0,0); // Pindah ke baris pertama LCD
    lcd.print("Motion Detect!");
    lcd.setCursor(0,1); // Pindah ke baris kedua LCD
    lcd.print("Count = ");
    lcd.print(count); // Tampilkan jumlah deteksi Gerakan ke LCD
    
    while (digitalRead(pirPin) == HIGH) {
      // Tidak ada yang perlu dilakukan, tunggu sampai tidak ada gerakan
    }
  }
  
  // Jika tidak ada gerakan terdeteksi
  else {
    delay(2000); // Delay 2 detik
    Serial.println("No Motion Detected!");
    lcd.clear(); // Hapus tampilan sebelumnya
    lcd.setCursor(0,0); // Pindah ke baris pertama LCD
    lcd.print("No Motion Detect!");
  }
}
