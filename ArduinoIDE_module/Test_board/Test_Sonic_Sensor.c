#include <Arduino.h>

// Define pins for the HC-SR04 sensor
const int trigPin = 5;
const int echoPin = 18;

// Define variables for duration and distance
long duration;
int distance;

void setup() {
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);

    // Set the trigPin as an OUTPUT
    pinMode(trigPin, OUTPUT);

    // Set the echoPin as an INPUT
    pinMode(echoPin, INPUT);
}

void loop() {
    // Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Set the trigPin HIGH for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distance = duration * 0.034 / 2;

    // Print the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Wait for 1 second before the next loop
    delay(1000);
}