void setup() {
  Serial.begin(9600);                 // Serial port to PC for debugging
  Serial2.begin(9600);                // Serial port to HC12
}

void loop() {
  while (Serial2.available()) {       // Check if HC12 has received data
    Serial.write(Serial2.read());     // Send the data to PC serial monitor
  }
}
