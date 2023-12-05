/**
 * FmiWeatherStationesp2866.ino
 * Weather forecast
 * 
 */

#include <Arduino.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include  <Wire.h>
#include <U8g2lib.h> //oled lib
#include <DHT.h> //dgt-22 temp & moisture sensor

// select which pin will trigger the configuration portal when set to LOW
#define TRIGGER_PIN 4
//WifiManager seconds to run for 
int timeout = 120; 

// dht-22 sensor config
#define DHTPIN 5
#define DHTTYPE DHT22 

// http request frequency
#define REFRESH_INTERWALL 60000l

//init oled
U8G2_SSD1306_128X64_NONAME_F_SW_I2C
u8g2(U8G2_R0,14,12,U8X8_PIN_NONE);
DHT dht(DHTPIN, DHTTYPE);
volatile bool startWifiManager;

void ICACHE_RAM_ATTR ISR() {
  startWifiManager=true;
}

void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  
  u8g2.begin();
  Serial.begin(115200);
  WiFiManager wm; 
  wm.autoConnect("WeatherStation","1234");
  Serial.println("\n Starting");
  dht.begin();
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TRIGGER_PIN), ISR, RISING);
}

long lastRun = 0;
String times="",temps="",outdoor="";
String house_tmp="",house_humidity="";

void loop() {

  if(startWifiManager){
    startWifiManager =false;
    Serial.println("WifiMgr starting...");
    printWiFiManager();
    startWiFiManager();
  }

  int* ptrRefreshDHT;
  ptrRefreshDHT = refreshDHT();

  house_tmp =String(ptrRefreshDHT[0]);
  house_humidity= String(ptrRefreshDHT[1]);
  if(lastRun+REFRESH_INTERWALL < millis() || lastRun == 0 ){
    String payload = refreshForecast();
    times = payload.substring(0,15);
    temps = payload.substring(16,32);
    outdoor =  payload.substring(33);
    lastRun =millis();
    Serial.print("http: ");Serial.print(times);Serial.print(temps);Serial.print(outdoor);
  }
  
  printMe( times, temps, outdoor, house_tmp, house_humidity );
  delay(500);
}


void printMe(String times,String temps,String outdoors,String house_tmp,String house_humidity){

  u8g2.clearBuffer();
  u8g2.setCursor( 0, 14 );
  u8g2.setFont( u8g2_font_unifont_t_76 );
  u8g2.print( ( (char)0x2610 ) );
  u8g2.setFont( u8g2_font_unifont_t_weather );
  u8g2.print( 0x01 );
  u8g2.setFont( u8g2_font_7x14B_tr );
  u8g2.print( house_tmp );u8g2.print( "'C" );
  u8g2.setFont( u8g2_font_unifont_t_weather ); 
  u8g2.print( 0x02 );
  u8g2.setFont( u8g2_font_7x14B_tr );
  u8g2.print( house_humidity );u8g2.print("%");

  u8g2.setCursor(0, 14+14);
  u8g2.println(outdoors);
  u8g2.setCursor(0, 14+14+14);
  u8g2.println(times);
  u8g2.setCursor(0, 14+14+14 +14);
  u8g2.println(temps);
  u8g2.sendBuffer();

}

void printWiFiManager(){
    u8g2.clearBuffer();
    u8g2.setCursor( 0, 14 );
    u8g2.setFont( u8g2_font_7x14B_tr );
    u8g2.print( "Setup wifi:" );
    u8g2.setCursor( 0, 14+14 );
    u8g2.print( "connect to: ");
    u8g2.setCursor( 0, 14+14+14 );
    u8g2.print( "WeatherStation" );
    u8g2.setCursor( 0, 14+14+14+14 );
    u8g2.print( "with mobile");
    u8g2.sendBuffer();
}

int * refreshDHT(){
  static  int toRet[2];
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  toRet[0] = (int)round(t);
  toRet[1] = (int)round(h);
  return toRet;
}

String refreshForecast(){
  WiFiClient client;
  HTTPClient http;
  String toRet = "";
  if (http.begin(client, "http://robo.sukelluspaikka.fi/images/forecast.txt")) {  // HTTP
    int httpCode = http.GET();
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        toRet = http.getString();
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect");
  }
  return toRet;
}


void startWiFiManager (){
  WiFiManager wm; 
  Serial.println("Starting manager");
  //wm.resetSettings();
  // set configportal timeout
  wm.setConfigPortalTimeout(timeout);

  if (!wm.startConfigPortal("WeatherStation")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(5000);
  }
  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
}
