#include <LiquidCrystal.h>

// Define the analog pins for each soil moisture sensor
const int soilMoisturePins[] = {A0, A1, A2, A3, A4};  // Sensors connected to A0-A4
const int numSensors = 5;  // Number of sensors

// Set up the LCD (with parallel connection)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // RS, E, D4, D5, D6, D7 pins

// Moisture threshold (adjust this based on your sensor calibration)
const int moistureThreshold = 60; // Above 60% means the plant is happy, below means needs water

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize the LCD
  lcd.begin(16, 2);  // 16 columns, 2 rows
  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture");  // Display a header message
  delay(2000);  // Wait for 2 seconds to let user see the header
}

void loop() {
  // Loop through each soil moisture sensor and display its value
  for (int i = 0; i < numSensors; i++) {
    int moistureValue = analogRead(soilMoisturePins[i]);

    // Map the moisture value to a percentage (0 to 100)
    int moisturePercentage = map(moistureValue, 0, 1023, 0, 100);

    // Determine the plant's mood based on the moisture level
    String plantMood = (moisturePercentage >= moistureThreshold) ? "Happy" : "Unhappy";

    // Display sensor info on the LCD
    lcd.clear();  // Clear the screen for the next update
    lcd.setCursor(0, 0);
    lcd.print("Sensor ");
    lcd.print(i + 1);  // Show the sensor number
    lcd.print(": ");
    lcd.print(moisturePercentage);
    lcd.print("%");

    // Display plant's mood (happy or unhappy)
    lcd.setCursor(0, 1);
    lcd.print("Plant is ");
    lcd.print(plantMood);

    // Draw a progress bar on the second row to indicate moisture level
    lcd.setCursor(0, 1);  // Move cursor to second row
    int progressBarLength = map(moisturePercentage, 0, 100, 0, 16); // 16 is the max length of the bar
    for (int j = 0; j < progressBarLength; j++) {
      lcd.write(255);  // Character 255 is a solid block
    }

    // Print to Serial Monitor for debugging
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(" Moisture Level: ");
    Serial.print(moisturePercentage);
    Serial.print("% - ");
    Serial.println(plantMood);

    // Wait for a short time before updating the next sensor
    delay(2000);  // Delay 2 seconds between updates for each sensor
  }
}
