#include <Adafruit_MCP23X17.h>

#define MCP1_ADDR 0x20
#define MCP2_ADDR 0x21
#define N_SEGMENTS 7
#define N_DIGITS 2

Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;

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

void assignSegments(bool *result, bool settings[N_SEGMENTS]) {
  for (int i = 0; i < N_SEGMENTS; i++) {
    result[i] = settings[i];
  }
}

void mapIntToSegments(int v, bool **result) {
  if (v > 9) {
    assignSegments(result[0], digitMap[v / 10 % 10]);
    assignSegments(result[1], digitMap[v % 10]);
  } else {
    assignSegments(result[0], digitMap[0]);
    assignSegments(result[1], digitMap[v]);
  }
}

void updateDisplay(int seconds) {
  
}

void setup() {
  // put your setup code here, to run once:

  if (!mcp1.begin_I2C(MCP1_ADDR) || !mcp2.begin_I2C(MCP2_ADDR)) {
    Serial.println("MCP init error");
    while (1);
  }
}

void loop() {
  
}
