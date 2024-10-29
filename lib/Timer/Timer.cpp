#include <Timer.h>

#define BRIGHTNESS_MAX 15
#define DEBOUNCE 400

Timer::Timer(int startPin, int buzzerPin, int brightnessPin)
{
  this->matrix = new Adafruit_7segment();
  this->startPin = startPin;
  this->buzzerPin = buzzerPin;
  this->brightnessPin = brightnessPin;
  this->nTimes = 3;
  this->times = (int*)malloc(sizeof(int) * 3);
  this->times[0] = 120;
  this->times[1] = 30;
  this->times[2] = 60 * 5;
  this->timeIndex = 0;
}

bool Timer::begin()
{
  if (!this->matrix->begin(0x70)) {
    Serial.println("Display not ready");
    return false;
  }

  this->matrix->print("0000");
  this->matrix->writeDisplay();

  pinMode(this->buzzerPin, OUTPUT);
  pinMode(this->startPin, INPUT_PULLUP);
  pinMode(this->brightnessPin, INPUT);

  this->playBuzzer();

  return true;
}

void Timer::receiveTimes(int *times, int nTimes)
{
  Serial.printf("Received %d times: ", nTimes);
  for (int i = 0; i < nTimes; i++)
  {
    Serial.printf("%d ", times[i]);
  }
  Serial.println("");
  this->times = times;
  this->nTimes = nTimes;
  this->endTime = 0;
}

void Timer::step()
{
  if (this->endTime != 0 && this->endTime <= millis())
  {
    playBuzzer();
    this->endTime = 0;
  }
  this->checkStartButton();
  this->checkBrightness();
  this->updateDisplay();
}

void Timer::checkStartButton()
{
  if (digitalRead(this->startPin) == LOW && this->nTimes > 0 && millis() - debounce > DEBOUNCE) {
    this->debounce = millis();
    this->endTime = millis() + ((unsigned long)(this->times[this->timeIndex % this->nTimes]) * 1000);
    this->timeIndex++;
  }
}

void Timer::checkBuzzer()
{
  digitalWrite(this->buzzerPin, this->endBuzzer > millis() ? HIGH : LOW);
}

void Timer::playBuzzer()
{
  this->endBuzzer = millis() + 500;
}

void Timer::updateDisplay()
{
  int timeLeft = 0;
  if (this->endTime == 0)
  {
    timeLeft = this->times[this->timeIndex % this->nTimes];
  } else {
    timeLeft = (int)(this->endTime - millis()) / 1000;
  }
  if (timeLeft == lastDisplayValue) {
    return;
  }
  lastDisplayValue = timeLeft;
  uint16_t minutes = timeLeft / 60;
  uint16_t seconds = timeLeft - (minutes * 60);
  int displayTime = (minutes * 100) + seconds;
  this->matrix->print(displayTime, DEC);
  this->matrix->drawColon(true);
  this->matrix->writeDisplay();
}

void Timer::checkBrightness()
{
  if (this->brightness > 0)
  {
    this->matrix->setBrightness(this->brightness);
    this->brightness = 0;
  }
}

void Timer::receiveUpdatedPreferences(SystemPreferencesAccessor* preferences)
{
  this->brightness = preferences->getBrightness();
}