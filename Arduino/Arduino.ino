
// #define a1a 18
// #define a1b 19

// unsigned long lastCheck=0;
// const unsigned long Minutes=(1000 * 60)*10;



int lightLDR=39;

//------------state mode-----------
// #define Mode_Temperature 100
// #define Mode_SoilHumidity 101
// #define Mode_Shabbat 102
// #define Mode_Manual 103

// int modeWork;



void setup() {
  Serial.begin(115200);

  // dht.begin();
  // WiFi_SETUP();
  // pinMode(a1a,OUTPUT);
  // pinMode(a1b,OUTPUT);

}

void loop() {
  // sendData();
int light=analogRead(lightLDR);
int mapValue = map(light, 0, 4095, 0, 255);
Serial.println(mapValue);
delay(500);




//   if(millis()-lastCheck > Minutes){
//     lastCheck=millis();
//     Serial.println("check mode work from server");
//   }
//
//   switch(modeWork){
//         case Mode_Temperature:
//             Serial.println("Mode: Temperature");
//             break;
//         case Mode_SoilHumidity:
//             Serial.println("Mode: Soil Humidity");
//             break;
//         case Mode_Shabbat:
//             Serial.println("Mode: Shabbat");
//             break;
//         case Mode_Manual:
//             Serial.println("Mode: Manual");
//             break;
//         default:
//             Serial.println("Unknown mode, switching to Manual");
//             modeWork = Mode_Manual;
//             break;
//     }
  
}


// function pumpOn(){
//     digitalWrite(a1a,HIGH);
//     digitalWrite(a1b,LOW);
// }
//
// function pumpOff(){
//   digitalWrite(a1a,HIGH);
//   digitalWrite(a1b,HIGH);
// }