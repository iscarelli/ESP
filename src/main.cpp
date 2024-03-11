#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <TFT_eSPI.h>       // Hardware-specific library
#include <NTPClient.h>

#include <ESP32ZabbixSender.h>

ESP32ZabbixSender zSender;


TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

char ssid[] = "NetRosas_Qualidade";
char pass[] = "qualidade@55";

WiFiUDP udp;
NTPClient ntp(udp, "a.st1.ntp.br", -3 * 3600, 60000);
String hora;
String data;

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void setup(void) {
  Serial.begin(9600);
  Serial.print("Conectando...");

  WiFi.useStaticBuffers(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  printWifiStatus();

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  ntp.begin();
  ntp.forceUpdate();

  tft.fillRect(0,0,280,30, TFT_RED);
  tft.drawRoundRect(0,0,280,240,43,TFT_RED);
  tft.setCursor(60,7,2);
  tft.setTextColor(TFT_WHITE);
  tft.print("ZABBIX SENDER: MELO");
  tft.fillRect(0,210,280,30, TFT_RED);
  
}

// -------------------------------------------------------------------------
// Main loop
// -------------------------------------------------------------------------
void loop()
{
  // tft.fillRectHGradient(0, 0, 280, 50, TFT_MAGENTA, TFT_BLUE);
  // tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(10,50,2);
  tft.println("Horizontal gradient");

  // tft.fillRectVGradient(0, 60, 160, 50, TFT_ORANGE, TFT_RED);
  tft.setCursor(10,120,2);
  tft.print("Vertical gradient");

  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.setCursor(140,217,2);
  tft.print("IP: ");
  tft.print(WiFi.localIP());

  hora = ntp.getFormattedTime();
  data = ntp.getDay();

  tft.setCursor(35,217,2);
  tft.print(hora);

  delay(1000); // Wait here
}