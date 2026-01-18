#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define pin numbers
#define BUZZER_PIN 6
#define LED_PIN 7
#define ACK_SWITCH_PIN 5
#define CE_PIN 9
#define CSN_PIN 10

// Initialize LCD (adjust address if needed, commonly 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

RF24 radio(CE_PIN, CSN_PIN); // Create radio object

const byte address[6] = "00001"; // Same as transmitter

struct GPSData {
  float latitude;
  float longitude;
  unsigned long age;
  byte satellites;
  bool valid;
};

bool messageReceived = false;
GPSData receivedData;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ACK_SWITCH_PIN, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for");
  lcd.setCursor(0, 1);
  lcd.print("GPS data...");
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN); // Must match transmitter
  radio.startListening(); // Set as receiver
  
  digitalWrite(LED_PIN, LOW); // Initially LED off
  digitalWrite(BUZZER_PIN, LOW); // Buzzer off
}

void loop() {
  // Check connection status
  bool connectionStatus = radio.isChipConnected() && radio.isPVariant();
  digitalWrite(LED_PIN, connectionStatus ? HIGH : LOW);
  
  // Check for incoming data
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    
    if (receivedData.valid) {
      messageReceived = true;
      
      // Display on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lat:");
      lcd.print(receivedData.latitude, 6);
      
      lcd.setCursor(0, 1);
      lcd.print("Lon:");
      lcd.print(receivedData.longitude, 6);
      
      // Turn on buzzer
      digitalWrite(BUZZER_PIN, HIGH);
      
      Serial.print("GPS Data received - Lat: ");
      Serial.print(receivedData.latitude, 6);
      Serial.print(", Lon: ");
      Serial.println(receivedData.longitude, 6);
      Serial.print("Satellites: ");
      Serial.println(receivedData.satellites);
    }
  }
  
  // Check if acknowledgment switch is pressed
  if (messageReceived && digitalRead(ACK_SWITCH_PIN) == LOW) {
    messageReceived = false;
    digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Location");
    lcd.setCursor(0, 1);
    lcd.print("acknowledged!");
    
    delay(2000); // Show acknowledgment for 2 seconds
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Waiting for");
    lcd.setCursor(0, 1);
    lcd.print("GPS data...");
    
    // Debounce delay
    delay(200);
  }
  
  // Small delay to prevent flooding
  delay(100);
}

