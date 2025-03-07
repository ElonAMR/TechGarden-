#include <DHT.h>
#include <ArduinoJson.h>




#define a1a 18
#define a1b 19
#define lightSensor=39;
//------------הגדרת משתנים כלליים---------------

#define TEMP_MODE 100
#define SOIL_MOISTURE_MODE 101
#define SHABBAT_MODE 102
#define MANUAL_MODE 103

JsonDocument doc;

int currentState;
unsigned long lastCheckTime = 0;
const unsigned long ONE_MINUTES = (1000 * 60); // convert milli-seconds to 1 min
unsigned long DataPullTime;
unsigned long activationTime;

bool isOnPump;
int counterOnPump = 0;
unsigned long DataPullTime;
unsigned long pumpOnTime;

float currentTemp;
float tempServer;
int minTime ,maxTime ;
int light;





void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi_SETUP();
  pinMode(a1a,OUTPUT);
  pinMode(a1b,OUTPUT);
  isOnPump = true;
  lastCheckTime=millis();
}






void loop() {

  if( (millis() - lastCheckTime) >= (ONE_MINUTES * 10){
    currentState = GetState();
    lastCheckTime = millis();
    Serial.println("current State = "+ string(currentState));
  }

  switch(currentState){
        case TEMP_MODE:

            Serial.println("Mode: Temperature");

            currentTemp = dht.readTemperature();
            light = map(analogRead(lightSensor),0,4095,0,100);
             if((millis() - DataPullTime) > (2 * minutes)){
                deserializeJson(doc, getJsonData("temperature"));
                temp = (float) doc["temp"];
                minTime = doc["minTime"];
                maxTime = doc["maxTime"];
                DataPullTime = millis();
             }

            if(light > 90){
                isOnPump = true;
            }else if(light < 10 && counterOnPump == 2){
                isOnPump = true;
                counterOnPump = 0 ;
            }

           if(isOnPump && temp < CurrentTemp && countOn < 2 && light < 40){
              pumpOn();
              if(millis() - activationTime > (maxTime * ONE_MINUTES)){
                 pumpOff();
                 isOnPump = false;
                 counterOnPump++;
                 activationTime = millis();
              }
           }else if(isOnPump && counterOnPump < 2){
              pumpOn();
              if(millis() - activationTime > (minTime * minutes)){
                pumpOff();
                isOnPump = false;
                counterOnPump++;
                activationTime = millis();
              }
            }

            break;
        case SOIL_MOISTURE_MODE:
            Serial.println("Mode: Soil Humidity");
            break;
        case SHABBAT_MODE:
            Serial.println("Mode: Shabbat");
            break;
        case MANUAL_MODE:
            Serial.println("Mode: Manual");
            break;
        default:
            Serial.println("Unknown mode, switching to Manual");
            currentState = Mode_Manual;
            break;
    }

}






// #define dhtPin 16
// #define DHTTYPE DHT11

// DHT dht(dhtPin,DHTTYPE);
//
// int soilMoisture=39;






//------------soilMoisture mode-----------
// desiredHumidity = doc["soilHumidity"]["desiredHumidity"];

//----------------------------------


//------------shabbat mode-----------
// startTime = doc["shabbat"]["startTime"].as<String>();
// endTime = doc["shabbat"]["endTime"].as<String>();
// wateringDuration = doc["shabbat"]["wateringDuration"];
//----------------------------------

//------------manual mode-----------
// activatePump = doc["manual"]["activatePump"];

//----------------------------------








function pumpOn(){
    digitalWrite(a1a,HIGH);
    digitalWrite(a1b,LOW);
}

function pumpOff(){
  digitalWrite(a1a,HIGH);
  digitalWrite(a1b,HIGH);
}



// int soilMoistureValue=analogRead(soilMoisture);
// int moistureValue = map(soilMoistureValue, 0, 4095, 0, 100);
// Serial.println(moistureValue);
// delay(1000);


// float humidity = dht.readHumidity();
//  Serial.print("🌡️ temperature: ");
//   Serial.print(temperature);
//   Serial.println(" °C");

//   Serial.print("💧 humidity: ");
//   Serial.print(humidity);
//   Serial.println(" %");
