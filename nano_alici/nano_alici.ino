/*
  ALICI KODU - ARDUINO NANO
 
  Bağlantılar (Nano + YL-105):
  CE   -> 9
  CSN  -> 10
  MOSI -> 11
  MISO -> 12
  SCK  -> 13
 */

#include <SPI.h>
#include <RF24.h>

// nano için CE ve CSN pin tanımlaması
RF24 radio(9, 10);

// iletişim adresi
const byte address[6] = "00001";

void setup() 
{
  Serial.begin(9600);
  Serial.println("Alici hazir. Veri bekleniyor...");

  if (!radio.begin()) {
    Serial.println("NRF24L01 Modulu Bulunamadi! Baglantilari kontrol edin.");
    while (1) {} 
  }

  radio.openReadingPipe(0, address); // 0. kanaldan dinlemeye başla
  radio.setPALevel(RF24_PA_MIN);     // güç seviyesi
  radio.startListening();            // alıcı moduna geç
}

void loop() 
{
  if (radio.available()) {
    char gelenMesaj[32] = "";
    
    radio.read(&gelenMesaj, sizeof(gelenMesaj));
    
    Serial.print("Mega'dan mesaj var: ");
    Serial.println(gelenMesaj);
  }
}