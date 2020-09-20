#ifndef OTA_SERVER
#define OTA_SERVER

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include "CommandController.h"

class OTAServer {
    private:
        char * host;
        char * ssid;
        char * wifi_password;
        WebServer * webServer;
        CommandController * cmdController;

    public:
        OTAServer(char *host, char *ssid, char *password, CommandController *cmdController);
        ~OTAServer();
        bool begin();
        void addRoutes();
        void startWebServer();
        void handleClient();
        void handleCommand();
};

#endif