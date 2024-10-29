#ifndef NetworkManagerH
#define NetworkManagerH

#include <SystemPreferences.h>
#include <../../include/Beginner.h>

class NetworkManager : public SystemPreferencesReceiver, public Beginner
{
public:
  NetworkManager(SystemPreferencesAccessor* preferences);
  bool begin();
  void receiveUpdatedPreferences(SystemPreferencesAccessor* preferences);
private:
  SystemPreferencesAccessor* preferences;
  String ssid;
  String password;
};

#endif