#include <Arduino.h>
#include "LedControl.h"
#include <WiFiMulti.h>
#include <HTTPClient.h>
#define USE_SERIAL Serial
/*
 Now we need a LedControl to work with.
 pin 12 is connected to the DataIn 
 pin 33 is connected to the CLK 
 pin 27 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,33,27,1);
WiFiMulti wifiMulti;
char ssid[] = "your_network_ssid";
char password[] = "your_network_password";
char endpoint[] = "your_endpoint";

struct DisplayContent {
    int left;
    int right;
    int delay_millis;
};

void displaySetup() {
    /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
    */
    lc.shutdown(0,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(0,8);
    /* and clear the display */
    lc.clearDisplay(0);
}
void serialSetup() {
    USE_SERIAL.begin(115200);
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
}
// REST CLIENT
String queryTripDetails() {
    
    HTTPClient http;
    String payload;
    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
    http.begin(endpoint); //HTTP
    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            payload = http.getString();
            USE_SERIAL.println(payload);
        }
    } else {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    return payload;
}
// WRITING ON DISPLAY
void writeTimeOnSide(char* text) {
    // display text in screen
    lc.setChar(0,7,text[0],false);
    lc.setChar(0,6,text[1],false);
    lc.setChar(0,5,text[2],false);
    lc.setChar(0,4,text[3],false);
    lc.setChar(0,3,text[4],false);
    lc.setChar(0,2,text[5],false);
    lc.setChar(0,1,text[6],false);
    lc.setChar(0,0,text[7],false);
}

void writeInfoInDisplay(DisplayContent display_content) {
  // clear display
  lc.clearDisplay(0);
  delay(display_content.delay_millis);
  writeTextOnDisplay(false, display_content.text);
  delay(display_content.delay_millis);
}
// CONTROLLER FUNCTIONS
void setup() {
    displaySetup();
    serialSetup();
    // connect to wifi
    wifiMulti.addAP(ssid, password);
}
void loop() {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {
        String api_response = queryTripDetails();
        DisplayContent display_content;
        display_content.text = api_response;
        // TODO decide how to determine this delay
        display_content.delay_millis = 1000;
        writeInfoInDisplay(display_content);
    } else {
        writeTextOnDisplay("..Wifi..");
    }
    delay(5000);
}