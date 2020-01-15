#include "HX711.h"
#include <Wire.h>
#include <BH1750.h>
#include "DHT.h"

#define NAME "DIDRIK"

//defines
#define DHTPIN 4
#define DHTTYPE DHT11
#define DELAY_TIME_MS 1000

// Wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

// Instance Variables
HX711 scaleInstance;
BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);

bool lightMeterConnected = false;

void setup() {
  // General
  Serial.begin(38400);

  // scale
  scaleInstance.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  float scaleMult = 0;

  if (NAME == "KOSTAS") {
    scaleMult = 134.13f;
  } else if (NAME == "DIDRIK") {
    scaleMult = 131.0f;
  } else if (NAME == "WILL") {
    scaleMult = 135.747f;
  }

  scaleInstance.set_scale(scaleMult);
  scaleInstance.tare();

  //light
  Wire.begin();
  if (lightMeter.begin()) {
    lightMeterConnected = true;
  }

  //temp_humidity
  dht.begin();

  Serial.println("name|scale|moisture|lux|humidity|temp");
}

void loop() {

  // scale
  long scale = 0;
  if (scaleInstance.is_ready()) {
    scale = scaleInstance.get_units(10);
  }

  // moisture
  float moisture = analogRead(A0);

  // light
  float lux = -1;
  if (lightMeterConnected) {
    lux = lightMeter.readLightLevel();
  }

  //temp_humidity
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  // print order:
  // name|scale|moisture|lux|humidity|temp
  Serial.print(NAME);
  Serial.print("\t");
  Serial.print(scale);
  Serial.print("\t");
  Serial.print(moisture);
  Serial.print("\t");
  Serial.print(lux);
  Serial.print("\t");
  Serial.print(humidity);
  Serial.print("\t");
  Serial.print(temp);
  Serial.println();

  delay(DELAY_TIME_MS);
}
