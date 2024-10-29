#include <RecentTimesStorage.h>
#include <ArduinoJson.h>

#define RECENT_FILE_PATH "recent_times"
#define MAX_RECENT 20

RecentTimesStorage::RecentTimesStorage(Preferences* preferences)
{
  this->preferences = preferences;
  this->times = new std::vector<RecentTime>();
}

bool RecentTimesStorage::begin()
{
  this->loadRecentTimes();
  return true;
}

void RecentTimesStorage::addRecentTimes(RecentTime time)
{
  if (this->times->size() == MAX_RECENT)
  {
    this->times->erase(this->times->begin(), this->times->begin() + 1);
  }
  this->times->push_back(time);
  this->storeRecentTimes();
}

int RecentTimesStorage::getRecentTimes(RecentTime* times, int max)
{
  int total = max < this->times->size() ? max : this->times->size();
  for (int i = 0; i < total; i++)
  {
    times[i] = this->times->at(i);
  }
  return total;
}

bool RecentTimesStorage::loadRecentTimes()
{
  String json = this->preferences->getString(RECENT_FILE_PATH, "");
  if (json.equals("")) {
    return false;
  }

  JsonDocument doc;
  deserializeJson(doc, json);

  JsonArray timesJson = doc["times"].as<JsonArray>();

  this->times->clear();

  for (int i = 0; i < timesJson.size(); i++) 
  {
    RecentTime time;
    String name = timesJson[i]["name"].as<String>();
    Serial.printf("Loading %s\n", name);
    time.name = (char*)malloc(sizeof(char) * name.length());
    strcpy(time.name, name.c_str());
    JsonArray timeValues = timesJson[i]["times"].as<JsonArray>();
    time.nTimes = timeValues.size();
    time.times = (int*)malloc(sizeof(int) * timeValues.size());
    for (int j = 0; j < timeValues.size(); j++)
    {
      time.times[j] = timeValues[j].as<int>();
    }
    this->times->push_back(time);
  }

  return true;
}

bool RecentTimesStorage::storeRecentTimes()
{
  JsonDocument root;
  for (int i = 0; i < this->times->size(); i++)
  {
    root["times"][i]["name"] = this->times->at(i).name;
    for (int j = 0; j < this->times->at(i).nTimes; j++)
    {
      root["times"][i]["times"][j] = this->times->at(i).times[j];
    }
  }
  String json;
  serializeJson(root, json);
  preferences->putString(RECENT_FILE_PATH, json);
  return true;
}