
#define LDR_COUNT   8      // number of LDR sensors
#define SCAN_COUNT  1000   // scan count for each LDR
#define DELAY_MS    2      
#define HYST_RATIO  0.05   // 5% hysteresis ratio

// Define GPIO pins for LDR sensors
int ldrPins[LDR_COUNT] = {34, 35, 32, 33, 25, 26, 27, 14};

// Arrays to store minimum, maximum, and threshold values for each LDR
int ldrMin[LDR_COUNT];
int ldrMax[LDR_COUNT];
int thresholdHigh[LDR_COUNT];
int thresholdLow[LDR_COUNT];

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); 
}

void loop() {
 
  for (int i = 0; i < LDR_COUNT; i++) {
    ldrMin[i] = 4095;     // 12-bit ADC
    ldrMax[i] = 0;
  }

  for (int scan = 0; scan < SCAN_COUNT; scan++) {
    for (int i = 0; i < LDR_COUNT; i++) {
      int val = analogRead(ldrPins[i]);
      if (val < ldrMin[i]) ldrMin[i] = val;
      if (val > ldrMax[i]) ldrMax[i] = val;
    }
    delay(DELAY_MS);
  }


  for (int i = 0; i < LDR_COUNT; i++) {
    thresholdHigh[i] = (ldrMin[i] + ldrMax[i]) / 2;            // High threshold
    int hysteresisGap = (ldrMax[i] - ldrMin[i]) * HYST_RATIO;  // Hysteresis gap
    thresholdLow[i]  = thresholdHigh[i] - hysteresisGap;       // Low threshold
    if (thresholdLow[i] < ldrMin[i]) thresholdLow[i] = ldrMin[i];  // avoid low threshold cannot be less than the minimum value
  }
  Serial.println(F("LDR\tMin\tMax\tHigh\tLow"));
  for (int i = 0; i < LDR_COUNT; i++) {
    Serial.print("LDR ");
    Serial.print(i + 1);      Serial.print('\t');
    Serial.print(ldrMin[i]);  Serial.print('\t');
    Serial.print(ldrMax[i]);  Serial.print('\t');
    Serial.print(thresholdHigh[i]); Serial.print('\t');
    Serial.println(thresholdLow[i]);
  }
  Serial.println(F("============================================="));

  delay(3000); 
}
