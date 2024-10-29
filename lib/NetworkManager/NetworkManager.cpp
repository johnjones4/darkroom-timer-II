#include <NetworkManager.h>
#include <WiFi.h>

NetworkManager::NetworkManager(SystemPreferencesAccessor* preferences)
{
  this->preferences = preferences;
}

bool NetworkManager::begin()
{
  this->ssid = this->preferences->getWifiSSID();
  this->password = this->preferences->getWifiPassword();

  WiFi.softAPdisconnect();
  WiFi.disconnect();

  if (ssid.length() > 0)
  {
    Serial.printf("Attempting to join network \"%s\"\n", ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->ssid, this->password);
    if (WiFi.waitForConnectResult() == WL_CONNECTED) 
    {
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP()); 
      return true;
    }
  }

  WiFi.mode(WIFI_AP);
  Serial.println("Setting wifi to AP mode");
  if (!WiFi.softAP("Dev Timer")) 
  {
    Serial.println("Failed to enable to AP mode");
    return false;
  }
  
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); 

  return true;
}

void NetworkManager::receiveUpdatedPreferences(SystemPreferencesAccessor* preferences)
{
  if (!this->ssid.equals(preferences->getWifiSSID()) || !this->password.equals(preferences->getWifiPassword()))
  {
    // Serial.println("Wifi settings have changed; rebooting");
    // ESP.restart();
    this->begin();
  }
}