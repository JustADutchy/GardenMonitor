//===========================================
// Actually do things
//===========================================
void setup() {
  pinMode (soilHumVCC, OUTPUT);               // Pin turns on soil humidity sensor
  pinMode (soilHumPin, INPUT);                // Pin that reads data from soil humidity sensor
  pinMode (DHTPIN, INPUT);                    // Pin that reads data from Air humidity & Temp sensor

  Serial.begin(9600);                         // Serial port to Computer
  Serial2.begin(9600);                        // Serial port to HC12

  dht.begin();                                // Start DHT sensor

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize the OLED
  display.setTextSize(1);
  display.setTextColor(1);

}

void loop() {
  getAllSensorData();
  updateDisplay();
  delay(interval);                            // Replace delay with something smarter sometime 
}
