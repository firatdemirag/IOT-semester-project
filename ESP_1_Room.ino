#include "BluetoothSerial.h"
#include "DHTesp.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

const int DHT_PIN = 15;

DHTesp dhtSensor;
BluetoothSerial SerialBT;
String sensor_temperature = "";
String sensor_humidity = "";

void setup() {
  Serial.begin(115200);
  SerialBT.begin();
  Serial.println("Bluetooth Started! Ready to pair...");
  dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
}

void loop() {
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  sensor_temperature = "Temp: " + String(data.temperature, 2) + "°C";
  sensor_humidity = "Humidity: " + String(data.humidity, 1) + "%";
  SerialBT.println(sensor_temperature);
  SerialBT.println(sensor_humidity);
  
  delay(1000);
}
