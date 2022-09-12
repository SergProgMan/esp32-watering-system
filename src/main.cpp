#include <Arduino.h>
#include <WiFi.h>
#include "time.h"

const char* ssid       = "YOUR_SSID";
const char* password   = "YOUR_PASS";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 7200;
const int   daylightOffset_sec = 0;

const unsigned int hour = 19;
const unsigned int minutes = 0;
const unsigned int seconds = 0;

const unsigned int workSeconds = 30;

void checkTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  char timeMinutes[3];
  strftime(timeMinutes,3, "%M", &timeinfo);
  char timeSeconds[3];
  strftime(timeHour,3, "%S", &timeinfo);
  if(hour == atol(timeHour) && minutes == atol(timeMinutes) && seconds == atol(timeSeconds)) {
    //fire relay
  }
}

void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}
 
void loop()
{
  checkTime();
}