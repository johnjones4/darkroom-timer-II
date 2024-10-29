#include <SystemPreferences.h>

#define PREFS_KEY_BRIGHTNESS "brightness"
#define PREFS_KEY_WIFI_SSID  "wifi_ssid"
#define PREFS_KEY_WIFI_PASS  "wifi_pass"

SystemPreferences::SystemPreferences(Preferences* preferences)
{
  this->preferences = preferences;
  this->updateRecievers = new std::vector<SystemPreferencesReceiver*>();
}

bool SystemPreferences::begin()
{
  return true;
}

void SystemPreferences::addReceiver(SystemPreferencesReceiver* reciever)
{
  this->updateRecievers->push_back(reciever);
  reciever->receiveUpdatedPreferences(this);
}

void SystemPreferences::setWifiMode(String ssid, String password)
{
  this->preferences->putString(PREFS_KEY_WIFI_SSID, ssid);
  this->preferences->putString(PREFS_KEY_WIFI_PASS, password);
  this->callUpdateReceivers();
}

String SystemPreferences::getWifiSSID()
{
  return this->preferences->getString(PREFS_KEY_WIFI_SSID, "");
}

String SystemPreferences::getWifiPassword()
{
  return this->preferences->getString(PREFS_KEY_WIFI_PASS, "");
}

void SystemPreferences::setBrightness(int brightness)
{
  if (brightness > 15) {
    brightness = 15;
  }
  if (brightness <= 0) {
    brightness = 1;
  }
  this->preferences->putInt(PREFS_KEY_BRIGHTNESS, brightness);
  this->callUpdateReceivers();
}

int SystemPreferences::getBrightness()
{
  return this->preferences->getInt(PREFS_KEY_BRIGHTNESS, 15);
}

void SystemPreferences::callUpdateReceivers()
{
  for (int i = 0; i < this->updateRecievers->size(); i++)
  {
    this->updateRecievers->at(i)->receiveUpdatedPreferences(this);
  }
}