#ifndef WebServerH
#define WebServerH

#include <ESPAsyncWebServer.h>
#include <../../include/Beginner.h>
#include <SystemPreferences.h>

class TimeReceiver
{
public:
  virtual void receiveTimes(int *times, int nTimes);
};

typedef struct {
  char* name;
  int* times;
  int nTimes;
} RecentTime;

class RecentTimesStorageProvider
{
public:
  virtual void addRecentTimes(RecentTime time);
  virtual int getRecentTimes(RecentTime* times, int max);
};

class WebServer : public Beginner
{
public:
  WebServer(FS *fs, int port, TimeReceiver* timeReceiver, RecentTimesStorageProvider* recentTimeStorage, SystemPreferences* preferences);
  bool begin();
private:
  ArRequestHandlerFunction serveGzip(const String path, const String contentType);
  ArBodyHandlerFunction serveSetTimesHandler();
  ArRequestHandlerFunction serveGetRecentTimesHandler();
  ArRequestHandlerFunction notFound();
  ArBodyHandlerFunction serveSetPreferencesHandler();
  ArRequestHandlerFunction serveGetPreferencesHandler();
  int port;
  AsyncWebServer* server;
  TimeReceiver* timeReceiver;
  RecentTimesStorageProvider* recentTimeStorage;
  FS *fs;
  SystemPreferences* preferences;
};

#endif