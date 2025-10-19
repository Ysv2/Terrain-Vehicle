#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define SLAVE_ADDRESS 0x08

#define LED_PIN 2
#define LED_COUNT 28

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t warm_white = strip.Color(255, 200, 80);
uint32_t very_warm_white = strip.Color(255, 180, 40);
uint32_t neutral_white = strip.Color(255, 240, 200);
uint32_t red = strip.Color(255, 0, 0);

//Motor Pin Constants
const int ssPinL = 8;
const int rotationPinL = 7;
const int rbPinL = 6;
const int pwmPinL = 11;        // speed (PWM)

const int ssPinR = 5;
const int rotationPinR = 4;
const int rbPinR = 3;
const int pwmPinR = 10;        // speed (PWM)

unsigned long lastCommandTime = 0;
unsigned long lastSendTime = 0;

const unsigned long SEND_INTERVAL = 10;       // Send motor command every 10 ms
const unsigned long TIMEOUT_DURATION = 2000;  // Stop if no command for 2 seconds


struct Velocity1D {
  int8_t rightV;
  int8_t leftV;

  uint8_t lights;

};

Velocity1D receivedData = {0, 0, 0};

// void processMovementCommand(int8_t rightVel, int8_t leftVel) {
//   if (rightVel > 0) { //Forward
//     digitalWrite(ssPinR, LOW);
//     digitalWrite(rotationPinR, HIGH);
//     // delay(10);
//     digitalWrite(rbPinR, LOW);
//   } 
//   else if (rightVel < 0) {
//     digitalWrite(ssPinR, LOW);
//     digitalWrite(rotationPinR, LOW);
//     // delay(10);
//     digitalWrite(rbPinR, LOW);
//   }
//   else {
//     digitalWrite(ssPinR, LOW);
//     digitalWrite(rotationPinR, HIGH);
//     // delay(10);
//     digitalWrite(rbPinR, HIGH);
//   }

//   if (leftVel > 0) { //Forward
//     digitalWrite(ssPinL, LOW);
//     digitalWrite(rotationPinL, LOW);
//     // delay(10);
//     digitalWrite(rbPinL, LOW);
//   } 
//   else if (leftVel < 0) {
//     digitalWrite(ssPinL, LOW);
//     digitalWrite(rotationPinL, HIGH);
//     // delay(10);
//     digitalWrite(rbPinL, LOW);
//   }
//   else {
//     digitalWrite(ssPinL, LOW);
//     digitalWrite(rotationPinL, LOW);
//     // delay(10);
//     digitalWrite(rbPinL, HIGH);
//   }

//   // delay(10);
// }


void processMovementCommand(int8_t rightVel, int8_t leftVel) {
  // Right Motor
  if (rightVel > 0) {
    digitalWrite(rotationPinR, HIGH); // Forward
    digitalWrite(rbPinR, LOW);
  } 
  else if (rightVel < 0) {
    digitalWrite(rotationPinR, LOW);  // Reverse
    rightVel = -rightVel;
    digitalWrite(rbPinR, LOW);
  }
  else {
    digitalWrite(rbPinR, HIGH);
    digitalWrite(rotationPinR, HIGH);
  }

  // int rightPWM = map(rightVel, 0, 127, 0, 255);
  // analogWrite(pwmPinR, rightPWM);
  analogWrite(pwmPinR, rightVel);



  // Left Motor
  if (leftVel > 0) {
    digitalWrite(rotationPinL, LOW); // Forward
    digitalWrite(rbPinL, LOW);
  } 
  else if (leftVel < 0) {
    digitalWrite(rotationPinL, HIGH);  // Reverse
    leftVel = -leftVel;
    digitalWrite(rbPinL, LOW);
  }
  else {
    digitalWrite(rbPinL, HIGH);
    digitalWrite(rotationPinL, HIGH);
  }

  // int leftPWM = map(leftVel, 0, 127, 0, 255);
  // analogWrite(pwmPinL, leftPWM);

  analogWrite(pwmPinL, leftVel);
}

void setup() {

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  
  pinMode(ssPinL, OUTPUT);
  pinMode(rotationPinL, OUTPUT);
  pinMode(rbPinL, OUTPUT);
  // pinMode(pwmPinL, OUTPUT);

  pinMode(ssPinR, OUTPUT);
  pinMode(rotationPinR, OUTPUT);
  pinMode(rbPinR, OUTPUT);
  // pinMode(pwmPinR, OUTPUT);

  digitalWrite(ssPinL, LOW);
  digitalWrite(ssPinR, LOW);

  processMovementCommand(0, 0);


  Serial.begin(115200);
  Serial.println(F("Motor Controller Starting..."));
  while (!Serial) {
    // some boards need this because of native USB capability
  }

  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Serial.println("Motor Controller Setup Successful!");
  delay(10);
}

void loop() {
  unsigned long currentTime = millis();

  // Check if it's time to update motor command
  if (currentTime - lastSendTime >= SEND_INTERVAL) {
    if (currentTime - lastCommandTime < TIMEOUT_DURATION) {
      processMovementCommand(receivedData.rightV, receivedData.leftV);
    } else {
      // Timeout occurred — stop the motors
      processMovementCommand(0, 0);
    }
    lastSendTime = currentTime;
  }

  if (receivedData.lights == 0) {
    strip.clear(); //! Off leds
  }
  else if (receivedData.lights == 1) {
    // strip.fill(red, 0, strip.numPixels() - 1);
    // strip.fill(color, first, count);
    strip.fill(red, 0, 14);
    strip.fill(warm_white, 14, 14);
    strip.show();
  }
  
}


void receiveEvent(int numBytes) {

  if (numBytes == sizeof(Velocity1D)) {
    Wire.readBytes((char*)&receivedData, sizeof(Velocity1D));

    Serial.print("rightV: "); Serial.println(receivedData.rightV);
    Serial.print("leftV: "); Serial.println(receivedData.leftV);

    lastCommandTime = millis();  // Reset timeout clock

    // if (millis() - lastSendTime > SEND_INTERVAL) {
    //   processMovementCommand(receivedData.rightV, receivedData.leftV);
    //   lastSendTime = millis();
    // }


  } else {
    Serial.println("Wrong struct size");
    while (Wire.available()) Wire.read(); // flush
  }
}