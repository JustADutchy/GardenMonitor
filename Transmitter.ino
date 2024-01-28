//===========================================
// Libraries (Shhhh!)
//===========================================
#include <DHT.h>               // Library for temp & humidity sensor
#include <Wire.h>              // Library for I2C(0) SCL pin 19, SDA pin 18
#include <Adafruit_GFX.h>      // Library for OLED
#include <Adafruit_SSD1306.h>  // Library for OLED


//===========================================
// Definitions (What is the meaning of life?)
//===========================================
#define soilHumVCC 12  // Pin to enable power to soil humidity sensor
#define soilHumPin 14  // Pin to read analog signal from soil humidity sensor
#define DHTPIN 15      // Pin to read air temperature and humidity
#define DHTTYPE DHT22  // Set DHT sensor type

#define interval 2 * 1000  // Set interval in milliseconds and convert it to seconds

#define SCREEN_WIDTH 128  // OLED display width
#define SCREEN_HEIGHT 64  // OLED display height


//===========================================
// Variables
//===========================================
int humidityAir;         // Store air humidity
int temperatureAir;      // Store air temperature
int humiditySoil;          // Store soil humidity
int maxHumiditySoil = 60;  // Maximum soil humidity, dont water if above this
int minHumiditySoil = 35;  // Minimum soil himidity, water if below this
bool soilIsWet;              // true if wet, false if dry


//===========================================
// Set up peripherals
//===========================================
DHT dht(DHTPIN, DHTTYPE);                                                   // Setup the DHT sensor
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1, 1000000);  // Setup the OLED


//===========================================
// Actually do things
//===========================================
void setup() {
  pinMode(soilHumVCC, OUTPUT);  // Pin turns on soil humidity sensor
  pinMode(soilHumPin, INPUT);   // Pin that reads data from soil humidity sensor
  pinMode(DHTPIN, INPUT);       // Pin that reads data from Air humidity & Temp sensor

  Serial.begin(9600);   // Serial port to Computer
  Serial2.begin(9600);  // Serial port to HC12

  dht.begin();  // Start DHT sensor

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize the OLED
  display.setTextSize(1);                     // Set the smalles font size
  display.setTextColor(1);
}

void loop() {
  getAllSensorData();
  updateDisplay();
  delay(interval);  // Replace delay with something smarter sometime
  transmitData();
}


//===========================================
// Funky functions
//===========================================
void getHumidityAir() {
  humidityAir = dht.readHumidity();  // Read current air humidity percentage
  Serial.print("Humidity: ");        // Print to serial cuz why not
  Serial.print(humidityAir);
  Serial.println("%");
}

void getTemperatureAir() {
  temperatureAir = dht.readTemperature();  // Read current air temperature
  Serial.print("Temperature:");            // Print to serial cuz why not
  Serial.print(temperatureAir);
  Serial.println(" Celsius");
}

void getHumiditySoil() {
  digitalWrite(soilHumVCC, HIGH);  // Power the soil sensor ON
  delay(10);
  humiditySoil = map(analogRead(soilHumPin), 200, 1000, 100, 0);  // Read current soil humidity
  delay(10);
  digitalWrite(soilHumVCC, LOW);   // Power the soil sensor OFF
  Serial.print("Humidity Soil:");  // Print to serial cuz why not
  Serial.print(humiditySoil);
  Serial.println("%");
  if (humiditySoil > 35) {
    soilIsWet = true;
  } else {
    soilIsWet = false;
  }
}

void getAllSensorData() {  // Get ALL the data
  getHumidityAir();
  getTemperatureAir();
  getHumiditySoil();
}


void updateDisplay() {     // Display ALL the sensor data
  display.clearDisplay();  // Clear buffer

  display.setCursor(0, 0);  // Update air humidity on OLED
  display.print("Humid. Air:");
  display.setCursor(80, 0);
  display.print(humidityAir);
  display.print("%");

  display.setCursor(0, 16);  // Update soil humidity on OLED
  display.print("Humid. soil:");
  display.setCursor(80, 16);
  display.print(humiditySoil);
  display.print("%");

  display.setCursor(0, 32);  // Update temperature on OLED
  display.print("Temperature:");
  display.setCursor(80, 32);
  display.print(temperatureAir);
  display.print("c");

  display.setCursor(0, 48);  // Update temperature on OLED
  display.print("Soil is  ");
  display.setCursor(80, 48);
  if (soilIsWet) {
    display.print("WET");
  } else {
    display.print("DRY");
  }
  

  display.display();  // Display changes made
}

void transmitData() {
  Serial2.print("Humidity Air:");
  Serial2.println(humidityAir);
  Serial2.print("Humidity Soil:");
  Serial2.println(humiditySoil);
  Serial2.print("Temperature Air:");
  Serial2.println(temperatureAir);
}