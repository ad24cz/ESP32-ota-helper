# ESP32-ota-helper
This is copy-paste style Arduino IDE .ino file. Use it to download new code from any source on your ESP32. Can also check Hash for you! This project can save you few minutes

# Configuration
## PlatformIO
`platformio.ini`:
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
upload_port = YOUR_ESP
upload_flags =
    --port=3232
;    --auth=admin
```
Replace `YOUR_ESP` with the IP address of your ESP or with the hostname (eg. `esp32.local`). If you use authentication, uncomment the last line.

## Arduino IDE
Tools > Port, select your ESP under 'Network Ports' (Arduino IDE should find it automatically). Unfortunately this didn't work for me, but that's probably because my home WiFi is weird.

# The simplest use
Since the ArduinoOTA library handles all the thing itself, the only thing you really have to do is to connect to WiFi and run `ArduinoOTA.begin()` in `setup()` and `ArduinoOTA.handle()` in `loop()`. Rest of the code (`ArduinoOTA.onStart`, `ArduinoOTA.onEnd`, `ArduinoOTA.onProgress`, `ArduinoOTA.onError`) are just event handlers, they are not really needed.
