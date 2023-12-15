/**
 * NeoPixel Uhr mit NTP-Synchronisierung
 * Dieses Skript steuert einen NeoPixel LED-Ring, um die aktuelle Zeit anzuzeigen,
 * synchronisiert über NTP (Network Time Protocol).
 *
 * Erstellt am: 04.11.2023
 * Letzte Aktualisierung: 04.11.2023 V1.0
 *
 * Autor: Alf Müller / purecrea gmbh Schweiz / www.bastelgarage.ch
 *
 * Copyright (c) 2023 Alf Müller. Alle Rechte vorbehalten.
 * Veröffentlichung, Verbreitung und Modifikation dieses Skripts sind unter der 
 * Bedingung der Namensnennung erlaubt und lizenzfrei.
 */
#include <ESP8266WiFi.h>
#include "WiFiManager.h"                    //https://github.com/tzapu/WiFiManager
#include <Timezone.h>                       //https://github.com/JChristensen/Timezone
#include <TimeLib.h>                        //https://github.com/PaulStoffregen/Time
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>
#define PIN D6
#define NUMPIXELS 120

// Initialisierung der NeoPixel-Bibliothek
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Initialisierung des NTP-Clients
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000);

// Zeitzone für Zentraleuropa definieren
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120}; // Sommerzeit: Letzter Sonntag im März um 2 Uhr morgens +2 Stunden
TimeChangeRule CET = {"CET", Last, Sun, Oct, 3, 60};    // Standardzeit: Letzter Sonntag im Oktober um 3 Uhr morgens +1 Stunde
Timezone CE(CEST, CET);

// Variable für die Speicherung der letzten Minute
int letzteMinute = -1;

void setup() { 
  pixels.begin();
  WiFiManager wifiManager;
  wifiManager.autoConnect("NeoPixelClock");
  timeClient.begin();
}

void loop() {
  // Aktualisiere die NTP-Zeit
  timeClient.update();

    // Hole die aktuelle Zeit in UTC
  time_t utc = timeClient.getEpochTime();

  // Wandele die UTC-Zeit in lokale Zeit um
  time_t local = CE.toLocal(utc);

  // Hole die aktuelle Stunde, Minute und Sekunde von der NTP-Zeit
  int stunden = hour(local);
  int minuten = minute(local);
  int seconds = second(local);


  // Setze die LEDs basierend auf der aktuellen Zeit
  setTimeOnLEDs(stunden, minuten, seconds, 0, 0, 55, 0, 55, 0);  // Blau für Minuten, Grün für Stunden
  delay(1000);                                          // Warte eine Sekunde bevor der nächste Durchlauf beginnt
}

void setTimeOnLEDs(int stunden, int minuten, int seconds, byte rMinuten, byte gMinuten, byte bMinuten, byte rStunden, byte gStunden, byte bStunden) {
  pixels.clear();  // Schalte alle LEDs aus
        
  // Set the seconds LED
  for (int i = 0; i < seconds; i++) {
    int secondLedIndex = (i + 29) % 60;                                                // Beginne bei LED 29 für die erste Minute
    pixels.setPixelColor(secondLedIndex, pixels.Color(55, 0, 0));  // Setze Farbe für jede Minute
  }

  // Setze die Minuten-LEDs
  for (int i = 0; i < minuten; i++) {
    int minutenLedIndex = (i + 29) % 60;                                                // Beginne bei LED 29 für die erste Minute
    pixels.setPixelColor(minutenLedIndex, pixels.Color(rMinuten, gMinuten, bMinuten));  // Setze Farbe für jede Minute
  }

  // Berechne die Anzahl der LEDs, die für die Stunden eingeschaltet sein sollten
  // Stelle sicher, dass die Stunden im 12-Stunden-Format sind
  stunden = stunden % 12;
  stunden = stunden ? stunden : 12;                // Verwandle 0 Stunden (Mitternacht) in 12
  int stundenAnzahl = stunden * 5 + minuten / 12;  // Jede Stunde hat 5 LEDs, jede Minute fügt 1/12 einer Stunde hinzu

  // Setze die Stunden-LEDs
  for (int i = 0; i < stundenAnzahl; i++) {
    int stundenLedIndex = (90 - i) % 60 + 60;                                           // Beginne bei LED 91 für die erste Stunde
    pixels.setPixelColor(stundenLedIndex, pixels.Color(rStunden, gStunden, bStunden));  // Setze Farbe für Stunden
  }

  pixels.show();  // Aktualisiere den Strip, um die Änderungen anzuzeigen
}

