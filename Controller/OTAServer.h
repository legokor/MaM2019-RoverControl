#ifndef OTA_SERVER
#define OTA_SERVER

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

class OTAServer {
    private:
        char * host;
        char * ssid;
        char * wifi_password;
        WebServer * webServer;

    public:
        OTAServer(char * host, char * ssid, char *password);
        ~OTAServer();
        bool begin();
        void addRoutes();
        void startWebServer();
        void handleClient();
};

#endif