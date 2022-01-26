#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define PERIPHERAL_NAME     "Darkroom Timer"
#define SERVICE_UUID        "9759fea6-c846-4719-9d5c-c959efd61aeb"
#define CHARACTERISTIC_UUID "0be3132d-5d94-414c-b542-2f0da985ea82"

#define MESSAGE_START 0x02
#define MESSAGE_END 0x03
#define EXPECTED_PARTS 3

#define BUZZER_PIN 25
#define START_PIN 26
#define N_TIMERSETS 3

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;

uint16_t currentTimerStart = 0;
uint16_t currentTimerLength = 0;
uint16_t timerSet[N_TIMERSETS] = {60 * 2, 60, 5 * 60};
int currentTimerSet = 0;

std::string lastBLEValue;

void updateTimeleft(uint16_t timeLeft) {
  uint16_t minutes = timeLeft / 60;
  uint16_t seconds = timeLeft - (minutes * 60);
  Serial.printf("%d:%d\n", minutes, seconds);
}

bool readBLE() {
  std::string value = pCharacteristic->getValue();
  if (value.compare(lastBLEValue) != 0) {
    lastBLEValue = value;
    const char* bytes = value.c_str();
    int l = value.length();
    if (l == 8
      && bytes[0] == MESSAGE_START
      && bytes[l - 1] == MESSAGE_END) {
        int b = 0;
        for (int i = 0; i < EXPECTED_PARTS; i++) {
           timerSet[i] = uint16_t(bytes[(i * 2) + 1]) | (uint16_t(bytes[(i * 2) + 2]) << 8);
           Serial.printf("Seconds: %d\n", timerSet[i]);
        }
        return true;
      }
  }
  return false;
}

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(START_PIN, INPUT_PULLUP);

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

  updateTimeleft(60 * 59);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  Serial.println(digitalRead(START_PIN) == LOW);
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
      updateTimeleft(0);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(1000);
      digitalWrite(BUZZER_PIN, LOW);
    }
  } else if (digitalRead(START_PIN) == LOW) {
    currentTimerStart = millis() / 1000;
    currentTimerLength = timerSet[currentTimerSet % N_TIMERSETS];
    currentTimerSet++;
    updateTimeleft(currentTimerLength);
    delay(500);
  } else if (currentTimerLength > 0) {
    updateTimeleft(currentTimerLength);
  }
}
