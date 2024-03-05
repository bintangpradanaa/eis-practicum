void setup() {
  Serial.begin(9600); 
  pinMode(2, OUTPUT); // Mengatur pin 2 sebagai output (untuk LED kuning)
  pinMode(3, OUTPUT); // Mengatur pin 3 sebagai output (untuk LED biru)
  pinMode(4, OUTPUT); // Mengatur pin 4 sebagai output (untuk LED merah)
}

void loop() {
  int yellow = 2; // Variabel untuk menyimpan nomor pin LED kuning
  int blue = 3;   // Variabel untuk menyimpan nomor pin LED biru
  int red = 4;    // Variabel untuk menyimpan nomor pin LED merah
  int sensorValue = analogRead(A1); // Membaca nilai analog dari pin A1 (sensor YL)

  digitalWrite(2, LOW); // Matikan LED kuning
  digitalWrite(3, LOW); // Matikan LED biru
  digitalWrite(4, LOW); // Matikan LED merah
  
  // Memeriksa nilai sensor dan mengatur LED dan pesan serial yang sesuai
  if (sensorValue >= 1000) (digitalWrite(yellow, HIGH)); // Jika kelembaban tanah terlalu kering, hidupkan LED kuning
  else if ((sensorValue <= 999) && (sensorValue >=901)) (digitalWrite(blue, HIGH)); // Jika kelembaban tanah optimal, hidupkan LED biru
  else if (sensorValue <= 900) (digitalWrite(red, HIGH)); // Jika kelembaban tanah terlalu basah, hidupkan LED merah
  else ;

  // Mengirim pesan serial berdasarkan kondisi kelembaban tanah
  if (sensorValue >= 1000) (Serial.print("SOIL IS TOO DRY!!!!!")); // Pesan untuk kelembaban tanah terlalu kering
  else if ((sensorValue <= 999) && (sensorValue >=901)) (Serial.print("SOIL IS PERFECT!!!!!")); // Pesan untuk kelembaban tanah optimal
  else if (sensorValue <= 900) (Serial.print("SOIL IS TOO WET!!!!!")); // Pesan untuk kelembaban tanah terlalu basah
  else;
  
  Serial.print("Soil Humidity is: "); // Pesan untuk data kelembaban tanah yang akan ditampilkan
  Serial.println(sensorValue); // Mencetak nilai kelembaban tanah yang didapat
  delay(500); // Delay untuk memberi waktu sebelum iterasi berikutnya
}
