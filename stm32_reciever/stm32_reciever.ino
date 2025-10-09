#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x08

#define CE_PIN  PA4 // CE Pin for NRF24
#define CSN_PIN PB0 // CSN Pin for NRF24
#define BUZZER_PIN PA3 // CSN Pin for NRF24

RF24 radio(CE_PIN, CSN_PIN);  // nRF24L01(+) radio
RF24Network network(radio);   // RF24Network using that radio
const uint16_t this_node = 00;  // Address of this node (in octal)

// Define the payload structure
struct JoystickPayload {
  int8_t joyRX;
  int8_t joyRY;
  int8_t joyLX;
  int8_t joyLY;

  uint8_t armingSwitch : 1;
  uint8_t toggleSwitch2 : 1;
  uint8_t toggle3Switch1 : 2;
  uint8_t toggle3Switch2 : 2;
  uint8_t reserved : 2;
} __attribute__((__packed__));

struct Velocity1D {
  int8_t rightV;
  int8_t leftV;

};

// Create a variable to store incoming payload
JoystickPayload payload;
Velocity1D velocityData;

// Heartbeat
unsigned long lastHeartbeatTime = 0;
const unsigned long HEARTBEAT_TIMEOUT = 2000; // 2 seconds timeout

unsigned long lastBuzzerTime = 0;
const unsigned long BUZZER_TIME = 150;
bool enableBuzzer = false;
bool buzzerActive = false;
bool prevArmingState = false;


// Heartbeat check
void checkHeartbeat() {
  if (millis() - lastHeartbeatTime > HEARTBEAT_TIMEOUT) {
    Serial.println("HeartBeat TimeOut...");

    // Stop motors
    velocityData.rightV = 0;
    velocityData.leftV = 0;
    sendVelocityData(velocityData);

    Serial.println("Motors stopped due to disconnection.");
  }
}

void sendVelocityData(Velocity1D data) {
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write((byte*)&data, sizeof(velocityData));
  Wire.endTransmission();
}

void soundBuzzer() {
  if (buzzerActive) {
    if (millis() - lastBuzzerTime < BUZZER_TIME) {
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
      buzzerActive = false;
    }
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
}


void setup() {
  delay(500);
  Serial.begin(115200);
  while (!Serial) {
    // Wait for Serial (if using native USB)
  }

  Serial.println(F("Receiver Starting..."));

  if (!radio.begin()) {
    Serial.println(F("Radio hardware not responding!"));
    while (1);  // Stay here if radio fails
  }

  radio.setChannel(90);           // Set RF channel
  network.begin(this_node);       // Start the network

  Wire.begin();

  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("Receiver Setup Successful!");
  delay(1000);
}

void loop() {
  network.update();  // Update network
  // Serial.println("Loop");
  if (network.available()) {
    RF24NetworkHeader header;
    network.read(header, &payload, sizeof(payload));  // Read payload into struct

    lastHeartbeatTime = millis();  // Update heartbeat timer

    // Handle the payload
    Serial.print("JR X: "); Serial.print(payload.joyRX);
    Serial.print(" Y: "); Serial.print(payload.joyRY);
    Serial.print(" | JL X: "); Serial.print(payload.joyLX);
    Serial.print(" Y: "); Serial.println(payload.joyLY);

    bool currentArmingState = payload.armingSwitch;

    if (currentArmingState && !prevArmingState) {
      // Rising edge detected (arming just turned on)
      lastBuzzerTime = millis();
      buzzerActive = true;
    }

    prevArmingState = currentArmingState;

    if (currentArmingState) {
      velocityData.rightV = payload.joyRX;
      velocityData.leftV = payload.joyLX;
    } else {
      velocityData.rightV = 0;
      velocityData.leftV = 0;
    }

    sendVelocityData(velocityData);

  }
  // else {
  //   // Serial.println("Waiting...");
  // }


  soundBuzzer();

  checkHeartbeat();  // Check for heartbeat timeout
}
