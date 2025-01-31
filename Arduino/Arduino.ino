
#define a1a 18
#define a1b 19

unsigned long lastCheck=0;
const unsigned long Minutes=(1000 * 60)*10;


//------------state mode-----------
#define Mode_Temperature 100
#define Mode_SoilHumidity 101
#define Mode_Shabbat 102
#define Mode_Manual 103


void setup() {
  Serial.begin(115200);

  dht.begin(); 

  // WiFi_SETUP();
  pinMode(a1a,OUTPUT);
  pinMode(a1b,OUTPUT);
  digitalWrite(a1a,HIGH);
  digitalWrite(a1b,LOW);
  delay(10000);
  digitalWrite(a1a,HIGH);
  digitalWrite(a1b,HIGH);
}

void loop() {
  // sendData();
  // delay(5000); // Delay before next data transmission

  if(millis()-lastCheck > Minutes){
    lastCheck=millis();
    Serial.println("check mode work from server");
  }
  
}
