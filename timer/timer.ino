#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define PERIPHERAL_NAME     "Darkroom Timer"
#define SERVICE_UUID        "9759fea6-c846-4719-9d5c-c959efd61aeb"
#define CHARACTERISTIC_UUID "0be3132d-5d94-414c-b542-2f0da985ea82"

#define MESSAGE_START 0x02
#define MESSAGE_END 0x03
#define MAX_LENGTH 256

#define BUZZER_PIN 25
#define START_PIN 26
#define BRIGHTNESS_PIN 4

#define BRIGHTNESS_MAX 15

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;

Adafruit_7segment matrix = Adafruit_7segment();

uint8_t currentTimersN = 3;
uint16_t currentTimerStart = 0;
uint16_t timerSet[MAX_LENGTH] = {60 * 2, 30, 5 * 60};
uint16_t currentTimerLength = timerSet[0];
int currentTimerSet = 0;

std::string lastBLEValue;

void updateTimeleft(uint16_t timeLeft) {
  uint16_t minutes = timeLeft / 60;
  uint16_t seconds = timeLeft - (minutes * 60);

  int displayTime = (minutes * 100) + seconds;

  matrix.print(displayTime, DEC);

  matrix.drawColon(true);
  
  matrix.writeDisplay();
}

bool readBLE() {
  std::string value = pCharacteristic->getValue();
  if (value.compare(lastBLEValue) == 0) {
    return false;
  }
  lastBLEValue = value;
  const char* bytes = value.c_str();
  int l = value.length();
  if (bytes[0] != MESSAGE_START) {
    return false;
  }
  int length = uint8_t(bytes[1]);
  if (length >= MAX_LENGTH || length == 0 || bytes[2 + (length * 2)] != MESSAGE_END) {
    return false;
  }
  for (int i = 0; i < length; i++) {
     timerSet[i] = uint16_t(bytes[(i * 2) + 2]) | (uint16_t(bytes[(i * 2) + 3]) << 8);
     Serial.printf("Seconds: %d\n", timerSet[i]);
  }
  currentTimersN = length;
  return true;
}

void setup() {
  Serial.begin(115200);

  if (!matrix.begin(0x70)) {
    Serial.println("Display not ready");
    while (1) {}
  }

  matrix.print("0000");
  matrix.writeDisplay();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(START_PIN, INPUT);
  pinMode(BRIGHTNESS_PIN, INPUT);

  BLEDevice::init(PERIPHERAL_NAME);
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("BLE ready.");

  updateTimeleft(timerSet[0]);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  int analogValue = analogRead(BRIGHTNESS_PIN);
  int brightnessValue = map(analogValue, 0, 3670, BRIGHTNESS_MAX, 0);
  matrix.setBrightness(brightnessValue);

  if (readBLE()) {
    currentTimerStart = 0;
    currentTimerSet = 0;
    currentTimerLength = timerSet[0];
    updateTimeleft(currentTimerLength);
  } else if (currentTimerStart > 0) {
    int timeLeft = currentTimerLength - ((millis() / 1000) - currentTimerStart);
    if (timeLeft >= 0) {
      updateTimeleft(timeLeft);
    } else {
      currentTimerStart = 0;
      currentTimerLength = 0;
      updateTimeleft(0);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(1000);
      digitalWrite(BUZZER_PIN, LOW);
      updateTimeleft(timerSet[currentTimerSet % currentTimersN]);
    }
  }
  if (digitalRead(START_PIN) == HIGH) {
    currentTimerStart = millis() / 1000;
    currentTimerLength = timerSet[currentTimerSet % currentTimersN];
    currentTimerSet++;
    updateTimeleft(currentTimerLength);
    delay(500);
  }
}
