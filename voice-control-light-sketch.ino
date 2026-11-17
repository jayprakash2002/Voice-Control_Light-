
#include <SoftwareSerial.h>

// HC-05 Bluetooth connection
// HC-05 TX -> Arduino Pin 2
// HC-05 RX -> Arduino Pin 3
SoftwareSerial BTSerial(2, 3);

// Command variable
String command = "";

// Relay pin
const int relay = 13;

void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);

  pinMode(relay, OUTPUT);

  // Active LOW Relay: Initially OFF
  digitalWrite(relay, HIGH);
}

void loop() {

  // Read Bluetooth data
  while (BTSerial.available() > 0) {
    char c = BTSerial.read();
    command += c;
    delay(5);
  }

  // Check received command
  if (command.length() > 0) {

    command.trim();
    command.toLowerCase();

    Serial.print("Received: ");
    Serial.println(command);

    // Light ON command
    if (command.indexOf("on") >= 0) {
      digitalWrite(relay, LOW);
      Serial.println("Relay ON");
    }

    // Light OFF command
    else if (command.indexOf("off") >= 0) {
      digitalWrite(relay, HIGH);
      Serial.println("Relay OFF");
    }

    // Unknown command
    else {
      Serial.println("Unknown Command");
    }

    // Clear command
    command = "";
  }
}
