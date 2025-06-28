/*
  * This code reads the ADC values from 8 LDR sensors connected to an ESP32 board.
  * It prints the ADC values to the Serial Monitor, allowing you to monitor the light intensity detected by each LDR.
  * The LDRs are connected to specific GPIO pins defined in the code.
*/
#define LDR_COUNT 8 // Number of LDR sensors

// Connected GPIO pins for the LDR sensors
#define INPUT_PIN_1 34
#define INPUT_PIN_2 35
#define INPUT_PIN_3 32
#define INPUT_PIN_4 33
#define INPUT_PIN_5 25
#define INPUT_PIN_6 26
#define INPUT_PIN_7 27
#define INPUT_PIN_8 14 // Leftmost LDR (LDR8)

// Array to hold the GPIO pins for the LDR sensors
int ldrPins[LDR_COUNT] = {INPUT_PIN_1, INPUT_PIN_2, INPUT_PIN_3, INPUT_PIN_4, INPUT_PIN_5, INPUT_PIN_6, INPUT_PIN_7, INPUT_PIN_8};

void setup() {
  Serial.begin(115200);   
  analogReadResolution(12);
}

void loop() {
  Serial.println(" ADC value of LDR sensors:");
  // Read ADC values from each LDR and print them
  // The loop iterates from the last LDR to the first one (LDR8 to LDR1)
  // This is done to match the order of the LDRs as they are connected from
  for (int i = LDR_COUNT - 1; i >= 0; i--) {
    int adcValue = analogRead(ldrPins[i]);
    Serial.print("LDR ");
    Serial.print(i + 1);
    Serial.print(" (Pin ");
    Serial.print(ldrPins[i]);
    Serial.print("): ");
    Serial.print(adcValue);
    Serial.print("\t");
  }
  Serial.println("\n---------------------------------");
  delay(1000); 
}
