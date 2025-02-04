// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <HTTPClient.h>


// const char* ssid = "0000";
// // const char* password = "0000";

// WiFiClient Client;

// void WiFi_SETUP(){
//   WiFi.begin(ssid);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.println("WiFi connected");
// }


// void sendData(){
//   HTTPClient http;
//   http.begin(Client, "http://10.9.1.91:4000/esp");
  
//   int httpCode = http.GET();
//   if(httpCode == HTTP_CODE_OK) {
//     Serial.print("HTTP response code ");
//     Serial.println(httpCode);
//     // String Res = http.getString();
//     //Serial.println(Res);
//     //  ret = Res.toInt();
//     }
//     http.end();
// }


// // int GetData() {
// //    int ret = -1;
// //    HTTPClient http;
// //    String dataURL = "";
// //    dataURL += "IDY=";
// //    dataURL += IDY;
// //    http.begin(client, "http://192.168.1.83:4000/ESP/Pull?" + dataURL);
// //    int httpCode = http.GET();
// //    //Serial.println(httpCode);
// //    if(httpCode == HTTP_CODE_OK) {
// //      //Serial.print("HTTP response code ");
// //      //Serial.println(httpCode);
// //      String Res = http.getString();
// //      //Serial.println(Res);
// //      ret = Res.toInt();
// //     }
// //     http.end();
        
// //     return ret;
// // }