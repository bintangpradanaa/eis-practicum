#define pirPin 2
#define ledPin 3
int statusPir = LOW;
int m;

void setup() {
  // put your setup code here, to run once:
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  m = digitalRead(pirPin);
  if (m == HIGH){
    delay(2000);
    digitalWrite(ledPin, HIGH);

    Serial.println("Gerakan Terdeteksi");
    statusPir = HIGH;
  }
  else {
    digitalWrite(ledPin, LOW);
    Serial.println("Tidak Ada Gerakan");
    statusPir = LOW;
  }
  delay(2000);
}
