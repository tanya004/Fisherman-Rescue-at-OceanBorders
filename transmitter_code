// TRANSMITTER CODE
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Define pin numbers
#define SWITCH_PIN 5
#define BUZZER_PIN 6
#define LED_PIN 7
#define CE_PIN 9
#define CSN_PIN 10

// GPS Module connections
#define GPS_RX 4  // Arduino RX (connects to GPS TX)
#define GPS_TX 3  // Arduino TX (connects to GPS RX)

RF24 radio(CE_PIN, CSN_PIN); // Create radio object
SoftwareSerial gpsSerial(GPS_RX, GPS_TX); // RX, TX for GPS
TinyGPSPlus gps; // Create GPS object

const byte address[6] = "00001"; // Communication address

struct GPSData {
  float latitude;
  float longitude;
  unsigned long age;
  byte satellites;
  bool valid;
};

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(9600);
  gpsSerial.begin(9600); // Start GPS serial
  
  if (!radio.begin()) {
    Serial.println("Radio initialization failed!");
    while (1) {} // Infinite loop if radio fails
  }
  
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX); // Changed to MAX for better range
  radio.stopListening(); // Set as transmitter
  
  digitalWrite(LED_PIN, LOW); // Initially LED off
  
  Serial.println("GPS NRF24L01 Transmitter Initialized");
}

void loop() {
  // Process GPS data continuously
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // Data is being processed by TinyGPS++
    }
  }
  
  // Check connection status
  bool connectionStatus = radio.isChipConnected();
  digitalWrite(LED_PIN, connectionStatus ? HIGH : LOW);
  
  // Check if switch is pressed
  if (digitalRead(SWITCH_PIN) == LOW) {
    GPSData gpsData = readGPSData();
    
    if (gpsData.valid) {
      bool sent = radio.write(&gpsData, sizeof(gpsData));
      
      if (sent) {
        Serial.print("GPS data sent - Lat: ");
        Serial.print(gpsData.latitude, 6);
        Serial.print(", Lon: ");
        Serial.print(gpsData.longitude, 6);
        Serial.print(", Sats: ");
        Serial.println(gpsData.satellites);
        
        // Beep for 1 second
        digitalWrite(BUZZER_PIN, HIGH);
        delay(1000);
        digitalWrite(BUZZER_PIN, LOW);
      } else {
        Serial.println("Failed to send GPS data");
        // Error beep pattern
        errorBeep();
      }
    } else {
      Serial.println("No valid GPS data available");
      // Error beep pattern
      errorBeep();
    }
    
    // Debounce delay
    delay(200);
  }
  
  // Small delay to prevent flooding
  delay(100);
}

GPSData readGPSData() {
  GPSData data;
  data.valid = false;
  
  if (gps.location.isValid() && gps.location.age() < 2000) { // Only use data < 2 seconds old
    data.latitude = gps.location.lat();
    data.longitude = gps.location.lng();
    data.age = gps.location.age();
    data.satellites = gps.satellites.value();
    data.valid = true;
    Serial.println("Valid GPS data obtained");
  } else {
    Serial.print("GPS data invalid or stale. Age: ");
    Serial.println(gps.location.age());
  }
  
  return data;
}

void errorBeep() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}
