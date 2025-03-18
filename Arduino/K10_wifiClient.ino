#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>


const char* ssid = "0000";
// const char* password = "0000";

WiFiClient Client;

void WiFi_SETUP(){
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}


void sendData(float temp, int light, int moisture){
  HTTPClient http;
  String dataUrl = "temp=" + String(temp);
  dataUrl+= "&light="+ String(light);
  dataUrl+= "&moisture="+ String(moisture);
  http.begin(Client,  "http://172.19.240.1:4000/esp?"+dataUrl);
  
  int httpCode = http.GET();
  if(httpCode == HTTP_CODE_OK) {
    Serial.print("HTTP response code ");
    Serial.println(httpCode);
    // String Res = http.getString();
    //Serial.println(Res);
    //  ret = Res.toInt();
    }
    http.end();
}


int GetData() {
   int ret = -1;
   HTTPClient http;
   http.begin(client, "http://172.19.240.1:4000/esp/state");
   int httpCode = http.GET();
   Serial.println(httpCode);
   if(httpCode == HTTP_CODE_OK) {
     Serial.print("HTTP response code ");
     Serial.println(httpCode);
     String Res = http.getString();
     Serial.println(Res);
     ret = Res.toInt();
   }
   http.end();
        
   return ret;
}

String getJsonData(String state){
    string json = "";
    HTTPClient http;
    http.begin(client, "http://192.168.1.83:4000/esp/dataMode?state="+state);
    int httpCode = http.GET();
    Serial.println(httpCode);
    if (httpCode == HTTP_CODE_OK) {
      Serial.print("HTTP response code ");
      Serial.println(httpCode);
      json = http.getString();
    }
    http.end();

    return json;
}