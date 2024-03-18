#include <LiquidCrystal_I2C.h>

// Inisialisasi alamat LCD 16x2 pada I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inisialisasi pin PIR
int pirPin = 12;
int count = 0; // Variabel untuk menghitung jumlah deteksi gerakan
bool motionDetected = false; // Variabel untuk menandai deteksi gerakan

void setup() {
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  
  // Inisialisasi pin PIR sebagai input
  pinMode(pirPin, INPUT);

  // Tampilkan pesan awal di LCD
  lcd.setCursor(0,0);
  lcd.print("No Motion Detect!");
}

void loop() {
  // Baca nilai dari sensor PIR
  int motion = digitalRead(pirPin);

  // Jika gerakan terdeteksi dan belum ada gerakan yang sedang terdeteksi sebelumnya
  if (motion == HIGH && !motionDetected) {
    motionDetected = true; // Tandai gerakan sedang terdeteksi
    lcd.clear(); // Hapus tampilan sebelumnya
    lcd.setCursor(0,0); // Pindah ke baris pertama LCD
    lcd.print("Motion Detect!");
    lcd.setCursor(0,1); // Pindah ke baris kedua LCD
    lcd.print("Count = ");
    lcd.print(++count); // Tambahkan dan tampilkan jumlah deteksi gerakan
  }
  
  // Jika tidak ada gerakan terdeteksi
  if (motion == LOW && motionDetected) {
    motionDetected = false; // Tandai gerakan selesai terdeteksi
    lcd.clear(); // Hapus tampilan sebelumnya
    lcd.setCursor(0,0); // Pindah ke baris pertama LCD
    lcd.print("No Motion Detect!");
  }
}
