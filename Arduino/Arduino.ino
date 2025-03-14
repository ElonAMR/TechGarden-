#include <DHT.h>
#include <ArduinoJson.h>




#define a1a 18
#define a1b 19
#define lightSensor=39;
#define humiditySensor=40;

//------------הגדרת משתנים כלליים---------------

#define TEMP_MODE 100
#define SOIL_MOISTURE_MODE 101
#define SHABBAT_MODE 102
#define MANUAL_MODE 103

// #define dht DHT22
// DHT dht(dhtPin, dht);

JsonDocument doc;

int currentState;
unsigned long lastCheckTime = 0;
const unsigned long ONE_MINUTES = (1000 * 60); // convert milli-seconds to 1 min
unsigned long DataPullTime;
unsigned long activationTime;

bool isOnPump;
bool pumpPowerOn=false;
int counterOnPump = 0;
unsigned long DataPullTime;
unsigned long pumpOnTime;

float currentTemp;
float tempServer;
int minTime ,maxTime ;
int light;


float humidity;
float currentHumidity;


int currentHour;
int firstStart;
int secondStart;
int wateringDuration;



bool activatePump;

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
    currentState = GetData();
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
            deserializeJson(doc, getJsonData("soilHumidity"));
            Humidity = doc["desiredHumidity"];
            currentHumidity = map(analogRead(humiditySensor), 0, 4095, 0, 100);
            if(currentHumidity < (humidity * 0.9)){
                pumpOn();
                pumpPowerOn=true;
            }else if(currentHumidity > (humidity * 1.1)){
                 pumpOff();
                 pumpPowerOn = false;
            }
            break;




        case SHABBAT_MODE:
            Serial.println("Mode: Shabbat");

            deserializeJson(doc, getJsonData("shabbat"));
            currentHour = doc["currentTimeHour"];
            firstStart = doc["firstStart"];
            secondStart = doc["secondStart"];
            wateringDuration = doc["wateringDuration"];






            break;



        case MANUAL_MODE:
            Serial.println("Mode: Manual");
            deserializeJson(doc, getJsonData("manual"));
            activatePump = doc["activatePump"];
            if(activatePump && !pumpPowerOn){
                pumpOn();
            }else if(!activatePump){
                pumpOff()
            }
            break;

        default:
            Serial.println("Unknown mode, switching to Manual");
            currentState = Mode_Manual;
            break;
    }

}


function pumpOn(){
    digitalWrite(a1a,HIGH);
    digitalWrite(a1b,LOW);
}

function pumpOff(){
  digitalWrite(a1a,HIGH);
  digitalWrite(a1b,HIGH);
}


