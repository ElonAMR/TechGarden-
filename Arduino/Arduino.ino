// #include <DHT.h>
//
// #define DHTPIN 16
// #define DHTTYPE DHT11

// DHT dht(DHTPIN,DHTTYPE);
//
// int lightLDR=39;
// int soilMoisture=39;

// #define a1a 18
// #define a1b 19


//------------state mode-----------
// #define TEMP_MODE 100
// #define SOIL_MOISTURE_MODE 101
// #define SHABBAT_MODE 102
// #define MANUAL_MODE 103



//------------temp mode-----------
// int currentState;
// float temp;
// int minTime;
// int maxTime;

// temp = doc["temperature"]["temp"];
// minTime = doc["temperature"]["minTime"];
// maxTime = doc["temperature"]["maxTime"];

//----------------------------------


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

//------------הגדרת משתנים כלליים---------------

int currentState;
unsigned long lastCheckTime=0;
const unsigned long CHECK_10_MIN = (1000 * 60) * 10; // convert milli-seconds to 10 min








void setup() {
  Serial.begin(115200);
  // dht.begin();
  // WiFi_SETUP();
  // pinMode(a1a,OUTPUT);
  // pinMode(a1b,OUTPUT);


}

void loop() {
// sendData();
// int light=analogRead(lightLDR);
// int lightLDRValue = map(light, 0, 4095, 0, 100);
// Serial.println(mapValue);
// delay(500);

// int soilMoistureValue=analogRead(soilMoisture);
// int moistureValue = map(soilMoistureValue, 0, 4095, 0, 100);
// Serial.println(moistureValue);
// delay(1000);


// float temperature=dht.readTemperature();
// float humidity = dht.readHumidity();
//  Serial.print("🌡️ temperature: ");
//   Serial.print(temperature);
//   Serial.println(" °C");

//   Serial.print("💧 humidity: ");
//   Serial.print(humidity);
//   Serial.println(" %");





  if( millis() - lastCheckTime >= CHECK_10_MIN){
    currentState = GetState();
    lastCheckTime = millis();
    Serial.println("current State = "+ string(currentState));
  }

  switch(currentState){
        case TEMP_MODE:
            Serial.println("Mode: Temperature");
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


// function pumpOn(){
//     digitalWrite(a1a,HIGH);
//     digitalWrite(a1b,LOW);
// }
//
// function pumpOff(){
//   digitalWrite(a1a,HIGH);
//   digitalWrite(a1b,HIGH);
// }