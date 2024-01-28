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
#define pin_Pump 8          // Pin to enable/disable pump
#define pin_soilHumVCC 12   // Pin to enable power to soil humidity sensor
#define pin_soilHumData 14  // Pin to read analog signal from soil humidity sensor
#define pin_DHT 15          // Pin to read air temperature and humidity

#define DHTTYPE DHT22  // Set DHT sensor type

#define interval 2 * 1000  // Set interval in milliseconds and convert it to seconds

#define SCREEN_WIDTH 128  // OLED display width
#define SCREEN_HEIGHT 64  // OLED display height


//===========================================
// Variables
//===========================================

int humidityAir;           // Store air humidity
int humiditySoil;          // Store soil humidity
int maxHumiditySoil = 60;  // Maximum soil humidity, dont water if above this
int minHumiditySoil = 35;  // Minimum soil himidity, water if below this
float temperatureAir;      // Store air temperature
bool soilIsWet;            // true if wet, false if dry
bool DEBUG = false;


//===========================================
// Set up peripherals
//===========================================
DHT dht(pin_DHT, DHTTYPE);                                                  // Setup the DHT sensor
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1, 1000000);  // Setup the OLED


//===========================================
// Actually do things
//===========================================
void setup() {
  pinMode(pin_soilHumVCC, OUTPUT);  // Pin turns on soil humidity sensor
  pinMode(pin_soilHumData, INPUT);  // Pin that reads data from soil humidity sensor
  pinMode(pin_DHT, INPUT);          // Pin that reads data from Air humidity & Temp sensor

  Serial.begin(9600);   // Serial port to Computer
  Serial2.begin(9600);  // Serial port to HC12

  dht.begin();  // Start DHT sensor

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize the OLED
  display.setTextSize(1);                     // Set the smalles font size
  display.setTextColor(1);
}

void loop() {
  getAllSensorData();  // Kinda explains itself doesn't it?
  updateDisplay();     // Updates the display with new sensor status (duh)
  delay(interval);     // Replace delay with something smarter sometime
  transmitData();      // Transmit new sensor data over HC12
}


//===========================================
// Funky functions
//===========================================
void getHumidityAir() {
  humidityAir = dht.readHumidity();  // Read current air humidity percentage
  if (DEBUG) {
    Serial.print("Humidity: ");  // Print to serial cuz why not
    Serial.print(humidityAir);
    Serial.println("%");
  }
}

void getTemperatureAir() {
  temperatureAir = dht.readTemperature();  // Read current air temperature
  if (DEBUG) {
    Serial.print("Temperature:");  // Print to serial cuz why not
    Serial.print(temperatureAir);
    Serial.println(" Celsius");
  }
}

void getHumiditySoil() {
  digitalWrite(pin_soilHumVCC, HIGH);  // Power the soil sensor ON
  delay(10);
  humiditySoil = map(analogRead(pin_soilHumData), 100, 1000, 100, 0);  // Read current soil humidity
  delay(10);
  digitalWrite(pin_soilHumVCC, LOW);  // Power the soil sensor OFF
  if (DEBUG) {
    Serial.print("Humidity Soil:");  // Print to serial cuz why not
    Serial.print(humiditySoil);
    Serial.println("%");
  }
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

  display.setCursor(0, 12);  // Update soil humidity on OLED
  display.print("Humid. soil:");
  display.setCursor(80, 12);
  display.print(humiditySoil);
  display.print("%");

  display.setCursor(0, 24);  // Update temperature on OLED
  display.print("Temperature:");
  display.setCursor(80, 24);
  display.print(temperatureAir, 1);
  display.print("c");

  display.setCursor(0, 54);  // Update soil state on OLED
  display.print("Soil is  ");
  display.setCursor(50, 54);
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
  Serial2.println(temperatureAir, 1);
}

void pumpControl() {
  while (humiditySoil < minHumiditySoil) {
  }
}