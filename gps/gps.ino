#include <TinyGPS++.h>

TinyGPSPlus gps;

void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);
    Serial.println(F("GPS Modulu baslatiliyor."));
}

void loop()
{
    while (Serial1.available() > 0)
    {
        if (gps.encode(Serial1.read())) 
        {
            showGPSInformation();
        }
    }

    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
        Serial.println(F("GPS verisi alinamiyor."));
        while(true);
    }
}

void showGPSInformation()
{
  if (gps.location.isValid())
  {
    Serial.print(F("Enlem: "));
    Serial.println(gps.location.lat(), 6);
    Serial.print(F("Boylam: "));
    Serial.println(gps.location.lng(), 6);
  }
  else
  {
    Serial.println(F("Konum araniyor..."));
  }
}