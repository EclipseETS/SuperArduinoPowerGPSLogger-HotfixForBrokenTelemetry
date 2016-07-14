#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SD.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
const int chipSelect = 10;
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);

   pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
   
    return;
  }
}

void loop()
{
   {
      // This sketch displays information every time a new sentence is correctly encoded.
      while (ss.available() > 0)
        if (gps.encode(ss.read()))
          displayInfo();
      
      if (millis() > 5000 && gps.charsProcessed() < 10)
      {
        Serial.println(F("No GPS detected: check wiring."));
        while(true);
      }
   }
}

void displayInfo()
{
  String buf;
  if(gps.location.isUpdated()){
  File data = SD.open("gps.csv", FILE_WRITE);
  if(data){
    
    if (gps.date.isValid())
    {
      buf += gps.date.day();
      buf += ",";
      buf += gps.date.month();
      buf += ",";
      buf += gps.date.year();
      buf += ",";
      
    }
    else
    {
      buf += " , , ,";
    }
    if (gps.time.isValid())
    {
      buf += gps.time.hour();
      buf += ",";
      buf += gps.time.minute();
      buf += ",";
      buf += gps.time.second();
      buf += ",";
      
    }
    else
    {
      buf += " , , ,";
    }
    if (gps.location.isValid())
    {
      buf += String(gps.location.lat(),6);
      buf += ",";
      buf += String(gps.location.lng(),6);
      buf += ",";
    }
    else
    {
      buf += " , ,";
    }
    
    if (gps.altitude.isValid())
    {
      buf += gps.altitude.meters();
      buf += ",";
    }
    else
    {
      buf += " ,";
    }
    
    if (gps.speed.isValid())
    {
      buf += gps.speed.kmph();
      buf += ",";
    }
    else
    {
      buf += " ,";
    }
       
    data.println(buf);
    Serial.println(buf);
    data.close();
  }
  else
    Serial.println(F("shit"));
  }

}
