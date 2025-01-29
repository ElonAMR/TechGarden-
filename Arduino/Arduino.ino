
#define a1a 18
#define a1b 19


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
  
}
