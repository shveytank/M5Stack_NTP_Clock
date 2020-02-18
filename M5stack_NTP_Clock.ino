#include <NTPClient.h>
// change next line to use with another board/shield
#include <WiFi.h>
#include <Arduino.h>
#include <M5Stack.h>
const char *ssid     = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASS";
const long utcOffsetInSeconds = 19800;

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup(){
  Serial.begin(115200);
 M5.begin();
  WiFi.begin(ssid, password);
  M5.Power.begin();

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());
  M5.Lcd.setCursor(20,90);
  M5.Lcd.setTextSize(6);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  M5.Lcd.print(timeClient.getFormattedTime());
  delay(1000);
  M5.Lcd.clear();
  M5.Lcd.fillScreen(TFT_BLACK);
}
