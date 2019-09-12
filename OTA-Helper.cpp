#include <ArduinoOTA.h>
#include <WiFi.h>

const char* ssid = "xxxx";
const char* password = "xxxx";
const char* host = "esp32";
const int port = 3232;

void setup() {
    Serial.begin(115200);

    // connect to WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    ArduinoOTA.setHostname(host);  // mDNS - esp32.local; not needed, default is esp3232-[MAC].local

    ArduinoOTA.setPort(port);  // not needed, 3232 is the default port

    // No authentication by default
    // ArduinoOTA.setPassword("admin");

    // Password can also be set with its MD5 value
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3"); // admin

    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        else  // U_SPIFFS
            type = "filesystem";

        // if updating SPIFFS, unmount it here by SPIFFS.end()
        Serial.println("Start updating " + type);
    });

    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);

        if (error == OTA_AUTH_ERROR)
            Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR)
            Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR)
            Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR)
            Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR)
            Serial.println("End Failed");
    });

    ArduinoOTA.begin();

    Serial.println("Ready!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Hostname: ");
    Serial.println(ArduinoOTA.getHostname());
    Serial.print("Port: ");
    Serial.println(port);
}

void loop() {
    ArduinoOTA.handle();
}
