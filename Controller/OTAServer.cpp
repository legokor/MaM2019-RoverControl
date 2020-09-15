#include "OTAServer.h"
#include "WebPages.h"


OTAServer::OTAServer(char * host, char * ssid, char * password) : host(host), ssid(ssid), wifi_password(password){
    this->webServer = new WebServer(80);       
}

OTAServer::~OTAServer(){
    delete this->webServer;
}

bool OTAServer::begin(){
    WiFi.begin(this->ssid, this->wifi_password);
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(this->ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    /*use mdns for host name resolution*/
    if (!MDNS.begin(this->host))
    { //http://esp32.local
        Serial.println("Error setting up MDNS responder!");
        while (1)
        {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");
    
}

void OTAServer::addRoutes(){
    this->webServer->on("/", HTTP_GET, [=]() {
        this->webServer->sendHeader("Connection", "close");
        this->webServer->send(200, "text/html", WebPages::login + WebPages::style);
    });

    this->webServer->on("/serverIndex", HTTP_GET, [=]() {
        this->webServer->sendHeader("Connection", "close");
        this->webServer->send(200, "text/html", WebPages::server + WebPages::style);
    });

    /*handling uploading firmware file */
    this->webServer->on( "/update", HTTP_POST, 
        [=]() {
            this->webServer->sendHeader("Connection", "close");
            this->webServer->send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        ESP.restart(); }, 
        [=]() {
            HTTPUpload& upload = this->webServer->upload();
            if (upload.status == UPLOAD_FILE_START) {
                Serial.printf("Update: %s\n", upload.filename.c_str());
                if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
                    Update.printError(Serial);
                }
            } else if (upload.status == UPLOAD_FILE_WRITE) {
                /* flashing firmware to ESP*/
                if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                    Update.printError(Serial);
                }
            } else if (upload.status == UPLOAD_FILE_END) {
                if (Update.end(true)) { //true to set the size to the current progress
                    Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
                } else {
                    Update.printError(Serial);
                }
            } });
}

void OTAServer::startWebServer(){
    this->webServer->begin();
}
void OTAServer::handleClient(){
    this->webServer->handleClient();
}