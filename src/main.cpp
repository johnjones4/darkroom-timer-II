#include <Arduino.h>
#include <AsyncTCP.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Timer.h>
#include <RecentTimesStorage.h>
#include <SystemPreferences.h>
#include <Beginner.h>
#include <NetworkManager.h>

#define BUZZER_PIN 25
#define START_PIN 26
#define BRIGHTNESS_PIN 4
#define N_BEGINNERS 5

WebServer *server;
Timer *timer;
RecentTimesStorage *recentStorage;
SystemPreferences *systemPreferences;
NetworkManager *networkManager;
Preferences preferences;

void setup() 
{
  Serial.begin(9600);

  if (!preferences.begin("timer"))
  {
    Serial.println("Failed to enable preferences");
    while(true){}
  }

  if (!SPIFFS.begin(true))
  {
    Serial.println("Failed to mount SPIFFS filesystem");
    while(true){}
  }

  systemPreferences = new SystemPreferences(&preferences);
  timer = new Timer(START_PIN, BUZZER_PIN, BRIGHTNESS_PIN);
  networkManager = new NetworkManager(systemPreferences);
  recentStorage = new RecentTimesStorage(&preferences);
  server = new WebServer(&SPIFFS, 80, timer, recentStorage, systemPreferences);
  Beginner* beginners[N_BEGINNERS] = {
    systemPreferences,
    networkManager,
    timer,
    recentStorage,
    server
  };
  for (int i = 0; i < N_BEGINNERS; i++)
  {
    if (!beginners[i]->begin())
    {
      Serial.printf("Failed to start dependency %d\n", i);
      while(true){}
    }
  }

  systemPreferences->addReceiver(timer);
  systemPreferences->addReceiver(networkManager);
}

void loop() 
{
  timer->step();
}
