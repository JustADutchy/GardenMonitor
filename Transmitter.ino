//===========================================
// Libraries (Shhhh!)
//===========================================
#include <DHT.h>                              // Library for temp & humidity sensor
#include <Wire.h>                             // I2C-0 SCL pin 19, SDA pin 18
#include <Adafruit_GFX.h>                     // Library for OLED
#include <Adafruit_SSD1306.h>                 // Library for OLED

//===========================================
// Definitions (What is the meaning of life?)
//===========================================
#define soilHumVCC 12                         // Pin to enable power to soil humidity sensor
#define soilHumPin 14                         // Pin to read analog signal from soil humidity sensor
#define DHTPIN 15                             // Pin to read air temperature and humidity
#define DHTTYPE DHT22                         // Set DHT sensor type

#define interval 2 * 1000                     // Set interval in milliseconds and convert it to seconds

#define SCREEN_WIDTH 128                      // OLED display width
#define SCREEN_HEIGHT 64                      // OLED display height

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1, 1000000);    // Setup the OLED


//===========================================
// Variables ()
//===========================================
float humidityAir;                            // Store air humidity
float temperatureAir;                         // Store air temperature
int humiditySoil;                             // Store soil humidity


//===========================================
// No clue what to label this
//===========================================
DHT dht(DHTPIN, DHTTYPE);                     // Create DHT sensor

void setup() {
  pinMode (soilHumVCC, OUTPUT);
  pinMode (soilHumPin, INPUT);
  pinMode (DHTPIN, INPUT);

  Serial.begin(9600);                         // Serial port to Computer
  Serial2.begin(9600);                        // Serial port to HC12
  dht.begin();                                // Start DHT sensor

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);
  display.clearDisplay();
  display.display();

}

void loop() {
  updateDisplay();
  delay(interval);
}


//===========================================
// Funky Functions
//===========================================
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

void getAllSensorData() {                     // Get ALL the data
  getHumidityAir();
  getTemperatureAir();
  getHumiditySoil();
}

void updateDisplay() {                        // Display ALL the data | NOTE | For some reason X starts at -2 and Y starts at -5 (First pixel top left)
  display.clearDisplay();                     // Clear buffer
  display.setTextSize(1);
  display.setTextColor(1);
  display.setCursor(-2,-5);                   // Top Left test
  display.print(".");
  display.setCursor(122,-5);                  // Top Right test
  display.print(".");
  display.setCursor(-2,57);                   // Bottom Left test
  display.print(".");
  display.setCursor(122,57);                  // Bottom Right test
  display.print(".");
  display.display();                          // Display changes made
  delay(1000);
}