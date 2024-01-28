//===========================================
// Variables
//===========================================
float humidityAir;                            // Store air humidity
float temperatureAir;                         // Store air temperature
int humiditySoil;                             // Store soil humidity


//===========================================
// Set up peripherals
//===========================================
DHT dht(DHTPIN, DHTTYPE);                   // Setup the DHT sensor
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1, 1000000);    // Setup the OLED


//===========================================
// Libraries (Shhhh!)
//===========================================
#include <DHT.h>                              // Library for temp & humidity sensor
#include <Wire.h>                             // Library for I2C(0) SCL pin 19, SDA pin 18
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

