#include <EtherCard.h>
#include <PubSubClient.h>

byte sensorInterrupt = 1;
byte sensorPin = 3;
byte redLedPin = 4;
byte greenLedPin = 5;

//CHANGE
int deviceId = 4;
//CASE A
byte mac[] = {0x00, 0x01, 0x02, 0x04, 0x04, 0x04};
byte ip[] = {192, 168, 25, 4};
//CASE B
//uint8_t mac[6] = {0x00, 0x01, 0x02, 0x17, 0x17, 0x17};
//const static uint8_t ip[] = {192, 168, 1, 117};
//const static uint8_t gw[] = {192, 168, 1, 1};
//const static uint8_t dns[] = {192, 168, 1, 1};
//CHANGE

//LAN
byte gateway[] = {192, 168, 25, 1};
byte dns[] = {192, 168, 25, 1};
byte server[] = {192, 241, 153, 56};
const char website[] PROGMEM = "ruanydepaula.com.br";
EthernetClient ether;
PubSubClient client(server, 1883, ether);
//LAN

volatile byte pulseCount;
float pulseTotal;

void pulseCounter () {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);

  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);

  pulseTotal = 0;
  networkStart();
}

void networkStart () {
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, LOW);
  Serial.println("Starting ethernet...");
  if (!ether.staticSetup(ip, gateway, dns)) {
      Serial.println(F("Static IP failed"));
      digitalWrite(redLedPin, HIGH);
  }

  if (!ether.dnsLookup(website)) {
      Serial.println(F("DNS failed"));
      digitalWrite(redLedPin, HIGH);
  }

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("SRV: ", ether.hisip);
}

void loop() {
  attachInterrupt(digitalPinToInterrupt(sensorInterrupt), pulseCounter, RISING);
  delay(1000);

  Serial.println("Pulse: " + String(pulseCount));

  if (pulseCount != 0) {
    sendToServer(pulseCount);
    pulseTotal += pulseCount;
  }

  if (pulseCount == 0 && pulseTotal != 0) {
    Serial.println("Pulse Amount: " + String(pulseTotal));
    pulseTotal = 0;
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }

  detachInterrupt(digitalPinToInterrupt(sensorInterrupt));
  pulseCount = 0;
}

void sendToServer (float pulseAmount) {
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH);

  String params = "{device_id: " + String(deviceId) + ", pulse: " + String(pulseAmount) + ", time: 1}";
  Serial.println("Sending: " + params);
}
