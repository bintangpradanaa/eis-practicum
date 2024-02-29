#include <NewPing.h>  // library untuk sensor

 // pin yang akan digunakan
#define TRIGGER_PIN 11 
#define ECHO_PIN 12

// jarak maksimum yang diset
#define MAX_DISTANCE 200 

NewPing sonar (TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // untuk sensor baru

void setup() {  // ini bagian yang akan dijalankan sekali saat program dimulai
Serial.begin(9600);
}

void loop() { // ini bagian yang akan dijalankan secara berulang
delay (1000); // dengan delay 1000 milidetik

unsigned int distance = sonar.ping_cm(); // bagian ini untuk mendeteksi jarak dari sensor
  
Serial.print ("Jarak = ");  // bagian ini akan menampilkan jarak
Serial.print (distance);
Serial.println (" cm");
}
