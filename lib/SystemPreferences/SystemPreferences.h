#ifndef SystemPreferencesH
#define SystemPreferencesH

#include <Preferences.h>
#include <vector>
#include <../../include/Beginner.h>

class SystemPreferencesAccessor
{
public:
  virtual String getWifiSSID();
  virtual String getWifiPassword();
  virtual int getBrightness();
};

class SystemPreferencesReceiver
{
public:
  virtual void receiveUpdatedPreferences(SystemPreferencesAccessor* preferences);
};

class SystemPreferences : public SystemPreferencesAccessor, public Beginner
{
public:
  SystemPreferences(Preferences* preferences);
  bool begin();
  void setWifiMode(String ssid, String password);
  String getWifiSSID();
  String getWifiPassword();
  void setBrightness(int brightness);
  int getBrightness();
  void addReceiver(SystemPreferencesReceiver* reciever);
private:
  void callUpdateReceivers();
  Preferences* preferences;
  std::vector<SystemPreferencesReceiver*>* updateRecievers;
};

#endif