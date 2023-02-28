#include "heltec.h"
#include <TinyGPS++.h>
//#include <SoftwareSerial.h>
#include <math.h>
#define BAND 433E6
//SoftwareSerial GPS_SoftSerial(32, 33);
TinyGPSPlus gps;

volatile float minutes, seconds;
volatile int degree, secs, mins;

float sta_lat=11.4960;
float sta_lng=77.2769;
float ta;

void setup()
{
  Heltec.begin(true , true , true , true , BAND );
  Serial.begin(9600);
//  GPS_SoftSerial.begin(9600);
}

void loop() {
  smartDelay(1000);
  unsigned long start;
  float lat_val, lng_val;
  bool loc_valid;
  lat_val = gps.location.lat();
  loc_valid = gps.location.isValid();
  lng_val = gps.location.lng();
  if (!loc_valid)
  {
    Serial.print("Latitude : ");
    Serial.println(lat_val);
    Serial.print("Longitude : ");
    Serial.println(lng_val);
    Serial.print("Time of Arrival : ");
    ta=distanceInKmBetweenEarthCoordinates(lat_val, lng_val, sta_lat, sta_lng)/0.9;
    LoRa.beginPacket();
    LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
    LoRa.print(ta);
    LoRa.println(" Minutes");
    LoRa.endPacket();
    delay(2000);
  }
  else
  {
    Serial.println("GPS READING: ");
    DegMinSec(lat_val);
    Serial.print("Latitude in Decimal Degrees : ");
    Serial.println(lat_val, 6);

    DegMinSec(lng_val);
    Serial.print("Longitude in Decimal Degrees : ");
    Serial.println(lng_val, 6);
    delay(2000);
  }
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Serial.available())
//    while (Serial.available())
    gps.encode(Serial.read());
//    gps.encode(Serial.read());
  } while (millis() - start < ms);
}

void DegMinSec( double tot_val)
{
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}

float degreesToRadians(float degrees) {
  return degrees * 3.14/ 180;
}

float distanceInKmBetweenEarthCoordinates(float lat_val, float lng_val, float sta_lat, float sta_lng) {
  int earthRadiusKm = 6371;

  float dLat = degreesToRadians(lat_val-sta_lat);
  float dLon = degreesToRadians(lng_val-sta_lng);

float  lat1 = degreesToRadians(lat_val);
float  lat2 = degreesToRadians(sta_lat);

  float a = sin(dLat/2) * sin(dLat/2) + sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2);
  float c = 2 * atan2(sqrt(a), sqrt(1-a));
  return earthRadiusKm * c;
}
