#include <Adafruit_MCP23X17.h>

#define MCP1_ADDR 0x20
#define MCP2_ADDR 0x21
#define N_SEGMENTS 7
#define N_DIGITS 2

Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;

void assignSegments(bool *result, bool settings[N_SEGMENTS]) {
  for (int i = 0; i < N_SEGMENTS; i++) {
    result[i] = settings[i];
  }
}


//  0
// 1 2
//  3
// 4 5
//  6
void mapCharToSegments(char c, bool *result) {
  switch (c) {
    case 0:
      bool vals[N_SEGMENTS] = {true, true, true, false, true, true, true};
      assignSegments(result, vals);
      break;
  }
}

void mapIntToSegments(int v, bool **result) {
  char str[N_DIGITS];
  sprintf(str, "%d", v);
  for (int i = 0; i < N_DIGITS; i++) {
    mapCharToSegments(str[i], result[i]);
  }
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
