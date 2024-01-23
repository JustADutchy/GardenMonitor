// Libraries (Shhhh!)
#include <DHT.h>

// Definitions (What is the meaning of life?)
#define soilHumVCC 12           // Pin to enable power to soil humidity sensor
#define soilHumPin 14           // Pin to read analog signal from soil humidity sensor
#define DHTPIN 15               // Pin to read air temperature and humidity
#define DHTTYPE DHT22           // Set DHT sensor type

// Variables ()
float humidityAir;
float temperatureAir;

// No clue what to label this
DHT dht(DHTPIN, DHTTYPE);       // Create DHT sensor

void setup() {
  pinMode (soilHumVCC, OUTPUT); //
  pinMode (soilHumPin, INPUT);  //
  pinMode (DHTPIN, INPUT);      //

  Serial.begin(9600);           // Serial port to Computer
  Serial2.begin(9600);          // Serial port to HC12
  dht.begin();                  // Start DHT sensor

}

void loop() {
//  Serial2.write("test");                  // Send data to HC-12 - DEBUG ONLY
//  delay(1000);                            // Send data to HC-12 - DEBUG ONLY
  //getHumidityAir();
  //getTemperatureAir();
  getHumiditySoil();
  delay(2000);
}

// Funky Functions

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
  int humiditySoil = analogRead(soilHumPin);  // Read current soil humidity
  delay(10);
  digitalWrite(soilHumVCC, LOW);              // Power the soil sensor OFF
  Serial.print("Humidity Soil:");             // Print to serial cuz why not
  Serial.print(humiditySoil);
  Serial.print(" %\n");
}