#ifndef RecentTimesStorageH
#define RecentTimesStorageH

#include <WebServer.h>
#include <Preferences.h>
#include <../../include/Beginner.h>
#include <vector>

class RecentTimesStorage : public RecentTimesStorageProvider, public Beginner
{
public:
  RecentTimesStorage(Preferences* preferences);
  bool begin();
  void addRecentTimes(RecentTime time);
  int getRecentTimes(RecentTime* times, int max);
private:
  bool loadRecentTimes();
  bool storeRecentTimes();
  std::vector<RecentTime>* times;
  Preferences* preferences;
};

#endif