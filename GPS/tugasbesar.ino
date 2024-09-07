#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

// Define the pin numbers for the push buttons
const int button1Pin = 4; // Connects to the first button
const int button2Pin = 5; // Connects to the second button
const int button3Pin = 6; // Connects to the third button
const int button4Pin = 7; // Connects to the fourth button
const int button5Pin = 8; // Connects to the fifth button

void setup() {
  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(30);

    // Attach button pins to the corresponding functions
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT_PULLUP);
    pinMode(button3Pin, INPUT_PULLUP);
    pinMode(button4Pin, INPUT_PULLUP);
    pinMode(button5Pin, INPUT_PULLUP);

  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {
  // Check each button and play corresponding audio
  if (digitalRead(button1Pin) == LOW) {
    player.play(1);
    delay(500); // Add a delay to avoid multiple readings
  } else if (digitalRead(button2Pin) == LOW) {
    player.play(2);
    delay(500);
  } else if (digitalRead(button3Pin) == LOW) {
    player.play(3);
    delay(500);
  } else if (digitalRead(button4Pin) == LOW) {
    player.play(4);
    delay(500);
  } else if (digitalRead(button5Pin) == LOW) {
    player.play(5);
    delay(500);
  }
}
