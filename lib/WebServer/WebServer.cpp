#include <WebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#define JSON_KEY_PREFS_BRIGHTNESS "brightness"
#define JSON_KEY_PREFS_WIFI_SSID "wifiSSID"
#define JSON_KEY_PREFS_WIFI_PASS "wifiPassword"

WebServer::WebServer(FS *fs, int port, TimeReceiver* timeReceiver, RecentTimesStorageProvider* recentTimeStorage, SystemPreferences* preferences)
{
  this->fs = fs;
  this->port = port;
  this->timeReceiver = timeReceiver;
  this->recentTimeStorage = recentTimeStorage;
  this->preferences = preferences;
}

bool WebServer::begin()
{
  this->server = new AsyncWebServer(80);

  this->server->on("/", HTTP_GET, this->serveGzip("/index.html.gz", "text/html"));
  this->server->on("/data.json", HTTP_GET, this->serveGzip("/data.json.gz", "application/json"));
  this->server->on("/set", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(200);
  }, NULL, this->serveSetTimesHandler());
  this->server->on("/recent", HTTP_GET, this->serveGetRecentTimesHandler());
  this->server->on("/preferences", HTTP_GET, this->serveGetPreferencesHandler());
  this->server->on("/preferences", HTTP_POST, this->serveGetPreferencesHandler(), NULL, this->serveSetPreferencesHandler());
  this->server->onNotFound(this->notFound());

  this->server->begin();

  return true;
}

ArRequestHandlerFunction WebServer::notFound()
{
  return [](AsyncWebServerRequest *request)
  {
    request->send(404, "text/plain", "Not found");
  };
}

ArRequestHandlerFunction WebServer::serveGzip(const String path, const String contentType)
{
  return [this, path, contentType](AsyncWebServerRequest *request)
  {
    File f = this->fs->open(path, FILE_READ);
    Serial.printf("File %s is %d bytes\n", path, f.size());
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * (f.size() + 1));
    f.readBytes((char*)buffer, f.size() + 1);
    AsyncWebServerResponse *response = request->beginResponse_P(200, contentType, buffer, f.size());
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
    free(buffer);
    f.close();
  };
}

ArBodyHandlerFunction WebServer::serveSetTimesHandler()
{
  return [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
  {
    JsonDocument doc;
    deserializeJson(doc, data);
    JsonArray times = doc["times"].as<JsonArray>();
    int nTimes = times.size();
    int *timesBuf = (int*)malloc(sizeof(int) * nTimes);
    for (int i = 0; i < nTimes; i++)
    {
      timesBuf[i] = times[i];
    }
    if (this->timeReceiver != NULL)
    {
      this->timeReceiver->receiveTimes(timesBuf, nTimes);
    }

    if (this->recentTimeStorage != NULL)
    {
      String name = doc["name"];
      RecentTime time;
      time.name = (char*)malloc(sizeof(char) * name.length());
      strcpy(time.name, name.c_str());
      time.times = timesBuf;
      time.nTimes = nTimes;
      this->recentTimeStorage->addRecentTimes(time);
    }
  };
}

ArRequestHandlerFunction WebServer::serveGetRecentTimesHandler()
{
  return [this](AsyncWebServerRequest *request)
  {
    if (this->recentTimeStorage != NULL) {
      int listSize = 20;
      RecentTime* buffer = (RecentTime*)malloc(sizeof(RecentTime) * listSize);
      int total = this->recentTimeStorage->getRecentTimes(buffer, listSize);
      JsonDocument root;
      for (int i = 0; i < total; i++)
      {
        root["times"][i]["name"] = buffer[i].name;
        for (int j = 0; j < buffer[i].nTimes; j++)
        {
          root["times"][i]["times"][j] = buffer[i].times[j];
        }
      }
      String jsonBuffer;
      serializeJson(root, jsonBuffer);
      request->send(200, "application/json", jsonBuffer);
      free(buffer);
    } else {
      request->send(404);
    }
  };
}

ArBodyHandlerFunction WebServer::serveSetPreferencesHandler()
{
  return [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
  {
    JsonDocument doc;
    deserializeJson(doc, data);
    this->preferences->setBrightness(doc[JSON_KEY_PREFS_BRIGHTNESS].as<int>());
    this->preferences->setWifiMode(doc[JSON_KEY_PREFS_WIFI_SSID], doc[JSON_KEY_PREFS_WIFI_PASS]);
  };
}

ArRequestHandlerFunction WebServer::serveGetPreferencesHandler()
{
  return [this](AsyncWebServerRequest *request)
  {
    JsonDocument root;

    root[JSON_KEY_PREFS_BRIGHTNESS] = this->preferences->getBrightness();
    root[JSON_KEY_PREFS_WIFI_SSID] = this->preferences->getWifiSSID();
    root[JSON_KEY_PREFS_WIFI_PASS] = this->preferences->getWifiPassword();

    String jsonBuffer;
    serializeJson(root, jsonBuffer);
    request->send(200, "application/json", jsonBuffer);
  };
}