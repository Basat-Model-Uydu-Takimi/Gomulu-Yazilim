/*
  VERİCİ KODU - ARDUINO MEGA 2560
 
  Bağlantılar (Mega + YL-105):
  CE   -> 9
  CSN  -> 53
  MOSI -> 51
  MISO -> 50
  SCK  -> 52
 */

#include <SPI.h>
#include <RF24.h>

// mega için CE ve CSN pin tanımlaması
RF24 radio(9, 53);

// iletişim adresi
const byte address[6] = "00001";

int sayac = 0; // gönderilen paket sayısını takip etmek için

void setup() {
  Serial.begin(9600);
  Serial.println("Verici Baslatiliyor...");

  if (!radio.begin()) {
    Serial.println("NRF24L01 modulu Bulunamadi! Baglantilari kontrol edin");
    while (1) {}
  }

  radio.openWritingPipe(address); // veri göndereceğimiz kanalı ac
  radio.setPALevel(RF24_PA_MIN);  // güc seviyesi (test icin min iyi)
  radio.stopListening();          // verici moduna gec (dinlemeyi durdur)
}

void loop() {
  // gönderilecek mesajı hazırlayalım
  char mesaj[32];
  sprintf(mesaj, "Selam Nano #%d", sayac);
  
  // mesajı gönder
  bool sonuc = radio.write(&mesaj, sizeof(mesaj));

  if (sonuc) {
    Serial.print("Gonderildi: ");
    Serial.println(mesaj);
  } else {
    Serial.println("Gonderim Basarisiz! (Alici kapali veya menzil disinda)");
  }

  sayac++;
  delay(1000);
}