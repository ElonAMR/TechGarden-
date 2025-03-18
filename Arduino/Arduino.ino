#include <DHT.h>
#include <ArduinoJson.h>



// #define dht DHT22
// DHT dht(dhtPin, dht);
#define a1a 18
#define a1b 19
#define lightSensor=39;
#define humiditySensor=40;

//------------הגדרת משתנים כלליים---------------

#define TEMP_MODE 100
#define SOIL_MOISTURE_MODE 101
#define SHABBAT_MODE 102
#define MANUAL_MODE 103

JsonDocument doc;
int currentState;
unsigned long lastCheckTime = 0;
const unsigned long ONE_MINUTES = (1000 * 60); // convert milli-seconds to 1 min
unsigned long DataPullTime=0;
unsigned long activationTime=0;
bool pumpPowerOn=false;

//------------הגדרת משתנים מוד טמפרטורה---------------

float currentTemp;
float tempServer;
int minTime ,maxTime ;
int light;
bool isMorning;
int counterOnPump = 0;

//------------הגדרת משתנים מוד לחות---------------

float humidity;
float currentHumidity;

//------------הגדרת משתנים מוד שבת---------------

int currentHour;
int firstStart;
int secondStart;
int wateringDuration;
bool firstActivation = false;
bool secondActivation = false;

//------------הגדרת משתנים מוד ידני---------------

bool activatePump;



//------------קוד---------------

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi_SETUP();
  pinMode(a1a,OUTPUT);
  pinMode(a1b,OUTPUT);
  lastCheckTime=millis();
}


void loop() {

  if( (millis() - lastCheckTime) >= (ONE_MINUTES * 10) ){
    currentState = GetData();
    lastCheckTime = millis();
    DataPullTime = 0;
    activationTime = 0;
    pumpOff();
    pumpPowerOn = false;
    Serial.println("current State = "+ String(currentState));
  }

  switch(currentState){

        case TEMP_MODE:
          Serial.println("Mode: Temperature");
          currentTemp = dht.readTemperature();
          light = map(analogRead(lightSensor), 0, 4095, 0, 100);

          if (millis() - DataPullTime >= (2 * minutes) || lastCheckTime == 0 ) {
               deserializeJson(doc, getJsonData("temperature"));
               tempServer = (float) doc["temp"];
               minTime = doc["minTime"];
               maxTime = doc["maxTime"];
               DataPullTime = millis();
          }

            isMorning = (light >= 30);
            // אם בוקר ועדיין לא השקנו
          if (isMorning && counterOnPump == 0 && !pumpPowerOn) {
                pumpOn();
                pumpPowerOn = true;
                activationTime = millis();
                counterOnPump++;
          }
          else if (!isMorning && counterOnPump < 2 && !pumpPowerOn) {
                pumpOn();
                pumpPowerOn = true;
                activationTime = millis();
                counterOnPump++;
          }
            // אם המשאבה דלוקה - בדיקה אם צריך לכבות
          if (pumpPowerOn) {
              if (millis() - activationTime >= ((tempServer > currentTemp ? maxTime : minTime) * ONE_MINUTES)) {
                  pumpOff();
                  pumpPowerOn = false;
              }
          }
          // בדיקה אם צריך להתחיל יום חדש
          if (isMorning && counterOnPump == 2) {
               counterOnPump = 0;
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
            if (millis() - DataPullTime >= (2 * ONE_MINUTES) || DataPullTime == 0) {
                deserializeJson(doc, getJsonData("shabbat"));
                currentHour = String(doc["currentTimeHour"]).toInt();
                firstStart = String(doc["firstStart"]).substring(0,2).toInt();
                secondStart = String(doc["secondStart"]).substring(0,2).toInt();
                wateringDuration = String(doc["wateringDuration"]).toInt();
                DataPullTime = millis();
            }
            // בדיקה אם יש צורך להפעיל את המשאבה
            if (currentHour == firstStart && !firstActivation && !pumpPowerOn) {
                pumpOn();
                pumpPowerOn = true;
                activationTime = millis();
                firstActivation = true;
            }
            else if (currentHour == secondStart && !secondActivation && !pumpPowerOn) {
                pumpOn();
                pumpPowerOn = true;
                activationTime = millis();
                secondActivation = true;
            }
            // כיבוי המשאבה לאחר משך זמן ההשקיה
            if (pumpPowerOn && (millis() - activationTime >= (wateringDuration * ONE_MINUTES))) {
                pumpOff();
                pumpPowerOn = false;
            }
            // איפוס ההפעלות לשבת הבאה
            if (currentHour == 0) {
                firstActivation = false;
                secondActivation = false;
            }
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



//------------פונקציות להדלקת וכיבוי משאבה---------------

function pumpOn(){
    digitalWrite(a1a,HIGH);
    digitalWrite(a1b,LOW);
}

function pumpOff(){
  digitalWrite(a1a,HIGH);
  digitalWrite(a1b,HIGH);
}


