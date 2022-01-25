#include <Adafruit_MCP23X17.h>
#include "BluetoothSerial.h"

#define MCP_ADDR 0x20
#define N_SEGMENTS 7
#define N_DIGITS 4
#define N_MCPS 2
#define N_PIN_STARTS 2
#define BUZZER_PIN 25
#define START_PIN 26
#define MODE_PIN 27
#define N_TIMERSETS 3

Adafruit_MCP23X17 mcp[N_MCPS];

BluetoothSerial SerialBT;

bool digitMap[10][N_SEGMENTS] = {
  {true, true, true, false, true, true, true},
  {false, false, true, false, false, true, false},
  {true, false, true, true, true, false, true},
  {true, false, true, true, false, true, true},
  {false, true, true, true, false, true, false},
  {true, true, false, true, false, true, true},
  {true, true, false, true, true, true, true},
  {true, false, true, false, false, true, false},
  {true, true, true, true, true, true, true},
  {true, true, true, true, false, true, true}
};

int pinStarts[2] = {0, 8};

bool digitSettings[N_DIGITS][N_SEGMENTS];

int currentTimerStart = 0;
int currentTimerLength = 0;
int timerSet[N_TIMERSETS] = {30, 60 * 60, 30};
int currentTimerSet = 0;

void assignSettings(int index, bool settings[N_SEGMENTS]) {
  for (int i = 0; i < N_SEGMENTS; i++) {
    digitSettings[index][i] = settings[i];
  }
}

void mapIntToDigitSettings(int v, int offset) {
  if (v > 9) {
    assignSettings(offset, digitMap[v / 10 % 10]);
    assignSettings(offset + 1, digitMap[v % 10]);
  } else {
    assignSettings(offset, digitMap[0]);
    assignSettings(offset + 1, digitMap[v]);
  }
}

void updateLEDs() {
  int d = 0;
  for (int i = 0; i < N_MCPS; i++) {
    for (int j = 0; j < N_PIN_STARTS; j++) {
      for (int k = 0; k < N_SEGMENTS; k++) {
        mcp[i].digitalWrite(pinStarts[j] + k, digitSettings[d][k] ? HIGH : LOW);
      }
    }
  }
}

void updateTimeleft(int timeLeft) {
  int minutes = timeLeft / 60;
  int seconds = timeLeft - (minutes * 60);
  Serial.printf("%d:%d", minutes, seconds);
  mapIntToDigitSettings(minutes, 0);
  mapIntToDigitSettings(seconds, 2);
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("DarkroomTimer");
  
  for (int i = 0; i < N_MCPS; i++) {
    if (!mcp[i].begin_I2C()) {
      Serial.printf("MCP init error: %d\n", i);
      while (1);
    }
    for (int j = 0; j < N_PIN_STARTS; j++) {
      for (int k = 0; k < N_SEGMENTS; k++) {
        mcp[i].pinMode(pinStarts[j] + k, OUTPUT);
      }
    }
  }

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(START_PIN, INPUT_PULLUP);
  pinMode(MODE_PIN, INPUT_PULLUP);

  updateTimeleft(60 * 59);
}

void loop() {
//  if (digitalRead(MODE_PIN) == LOW) {
//    if (currentTimerStart > 0) {
//      int timeLeft = currentTimerLength - ((millis() / 1000) - currentTimerStart);
//      if (timeLeft >= 0) {
//        updateTimeleft(timeLeft);
//      } else {
//        currentTimerStart = 0;
//        updateTimeleft(0);
//        digitalWrite(BUZZER_PIN, HIGH);
//        delay(1000);
//        digitalWrite(BUZZER_PIN, LOW);
//      }
//    } else if (digitalRead(START_PIN) == HIGH) {
//      currentTimerStart = millis() / 1000;
//      currentTimerLength = timerSet[currentTimerSet % N_TIMERSETS];
//      currentTimerSet++;
//      updateTimeleft(currentTimerLength);
//      delay(500);
//    } else if (currentTimerLength > 0) {
//      updateTimeleft(currentTimerLength);
//    }
//  } else {
////    currentTimerStart = 0;
////    currentTimerSet = 0;
////    currentTimerLength = 0;
////    updateTimeleft(0);
//    //Read bluetooth
//  }
}
