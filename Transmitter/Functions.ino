void getHumidityAir() {
  humidityAir = dht.readHumidity();           // Read current air humidity percentage
  Serial.print("Humidity: ");                 // Print to serial cuz why not
  Serial.print(humidityAir);
  Serial.print("%\n");
}

void getTemperatureAir() {
  temperatureAir = dht.readTemperature();     // Read current air temperature
  Serial.print("Temperature:");               // Print to serial cuz why not
  Serial.print(temperatureAir);
  Serial.print(" Celsius\n");
}

void getHumiditySoil() {
  digitalWrite(soilHumVCC, HIGH);             // Power the soil sensor ON
  delay(10);
  humiditySoil = analogRead(soilHumPin);  // Read current soil humidity
  delay(10);
  digitalWrite(soilHumVCC, LOW);              // Power the soil sensor OFF
  Serial.print("Humidity Soil:");             // Print to serial cuz why not
  Serial.print(humiditySoil);
  Serial.print(" %\n");
}

void getAllSensorData() {                     // Get ALL the data
  getHumidityAir();
  getTemperatureAir();
  getHumiditySoil();
}


void updateDisplay() {                        // Display ALL the sensor data
  display.clearDisplay();                     // Clear buffer

  display.setCursor(0,0);                     // Update air humidity on OLED
  display.print("Humid. Air  |%|");
  display.setCursor(96,0);
  display.print(humidityAir);

  display.setCursor(0,16);                    // Update temperature on OLED
  display.print("Temperature |c|");
  display.setCursor(96,16);
  display.print(temperatureAir);

  display.setCursor(0,32);                    // Update soil humidity on OLED
  display.print("Humid. soil |%|");
  display.setCursor(96,32);
  display.print(humiditySoil);

  display.display();                          // Display changes made
}