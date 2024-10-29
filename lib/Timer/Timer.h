#ifndef TimerH
#define TimerH
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

#include <WebServer.h>
#include <SystemPreferences.h>
#include <../../include/Beginner.h>

class Timer : public TimeReceiver, public SystemPreferencesReceiver, public Beginner
{
public:
  Timer(int startPin, int buzzerPin, int brightnessPin);
  bool begin();
  void receiveTimes(int *times, int nTimes);
  void step();
  void receiveUpdatedPreferences(SystemPreferencesAccessor* preferences);
private:
  void checkStartButton();
  void checkBrightness();
  void checkBuzzer();
  void playBuzzer();
  void updateDisplay();
  Adafruit_7segment* matrix;
  int startPin;
  int buzzerPin;
  int brightnessPin;
  unsigned long endTime = 0;
  int* times;
  int nTimes = 0;
  int timeIndex;
  unsigned long debounce = 0;
  int lastDisplayValue = 0;
  unsigned long endBuzzer = 0;
  int brightness = 15;
};

#endif