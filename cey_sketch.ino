#include "DHT.h"
#include <WiFi.h>
#include <HTTPClient.h>

#define DHTPIN 26
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

const char* name = "Quasar";
const char* pw = "northpole";

const char* server = "http://192.168.60.125:5000/sensor/data";

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();

  WiFi.begin(name, pw);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi ...");
  }
  Serial.println("Connected to WiFi!");
}

void loop() {
  delay(2000);

  float humid = dht.readHumidity();
  float temp = dht.readTemperature();

  Serial.print(F("Humidity: "));
  Serial.print(humid);

  Serial.print(F("%Temperature: "));
  Serial.print(temp);
  Serial.println(F("°C "));

  HTTPClient http;

  String url = String(server) + "?temp = " + String(temp) + "&humidness = " + String(humid);

  http.begin(url);

  int repcode = http.POST("");

  if (repcode == 200) {
    String rep = http.getString();
    Serial.println(repcode);
    Serial.println(rep);
  }
  else {
    Serial.print("Error on sending POST: ");
    Serial.println(repcode);
  }
}
