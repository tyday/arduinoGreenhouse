// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTPIN2 4

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

int photocellPin = 0; // the cell and 1K pulldown are connected to a0
int photocellReading; // the analog reading from the sensor divider

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
 
  dht.begin();
  dht2.begin();
}

void serialPrintSensor( float temperature, float humidity){
  Serial.print("{ \"t\":");
  Serial.print(temperature);
  Serial.print(", \"h\":");
  Serial.print(humidity);
  Serial.print("}");
}

void loop() {
  
  // Wait a few seconds between measurements.
  delay(5000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);

  float h2 = dht2.readHumidity();
  // Read temperature as Celsius
  float t2 = dht2.readTemperature();
  // Read temperature as Fahrenheit
  float f2 = dht2.readTemperature(true);

  photocellReading = analogRead(photocellPin); 
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

    // Print out reading from photocell
    Serial.print("{\"s0\":{\"b\":");
    Serial.print(photocellReading);
    Serial.print("}, ");
    
    Serial.print("\"s1\":");
    serialPrintSensor(t, h);
    Serial.print(",\"s2\":");
    serialPrintSensor(t2,h2);
    Serial.println("}");
}
