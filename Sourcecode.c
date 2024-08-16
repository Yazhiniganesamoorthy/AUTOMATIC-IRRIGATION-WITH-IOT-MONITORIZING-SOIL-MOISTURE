#include <DHT.h>
#include <ESP8266WiFi.h>

#define MOISTURE_SENSOR_PIN A0
#define WATER_PUMP_PIN 2
#define DHT_PIN 5 // Replace with the appropriate pin connected to the DHT sensor
#define DHT_TYPE DHT22 // Change to DHT11 if you’re using that sensor
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int moistureLevel = analogRead(MOISTURE_SENSOR_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Moisture: ");
  Serial.println(moistureLevel);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  // Adjust moisture and temperature thresholds based on your requirements
  if (moistureLevel < 500 || temperature > 30.0 || humidity < 40.0) {
    turnOnWaterPump();
    delay(5000); // Run the pump for 5 seconds, adjust as needed
    turnOffWaterPump();
  }

  delay(600000); // Wait for 10 minutes before checking again, adjust as needed
}

void turnOnWaterPump() {
  digitalWrite(WATER_PUMP_PIN, HIGH);
  Serial.println("Water pump turned ON");
}

void turnOffWaterPump() {
  digitalWrite(WATER_PUMP_PIN, LOW);
  Serial.println("Water pump turned OFF");
}
