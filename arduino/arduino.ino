#include <EtherCard.h>

byte sensorInterrupt = 1;
byte sensorPin = 3;

//CHANGE
String deviceId = "3";
uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x03,0x03};
const static uint8_t ip[] = {192,168,25,203};
//CHANGE

const static uint8_t gw[] = {192,168,25,1};
const static uint8_t dns[] = {192,168,25,1};
const char website[] PROGMEM = "ruanydepaula.com.br";
const static uint8_t serverIp[] = {192,241,153,56};
byte Ethernet::buffer[700];
static byte session;
Stash stash;
volatile byte pulseCount;  
float pulse;
float pulseAmount;
float oldPulseAmount;
unsigned long oldTime;
long startTime;

void setup()
{
    Serial.begin(9600);
    networkStart();

    pinMode(sensorPin, INPUT_PULLUP);
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

void loop()
{
    receiveAnswer();
    
    if ((millis() - oldTime) > 1000)
    { 
        detachInterrupt(sensorInterrupt);

        pulse = ((1000.0 / (millis() - oldTime)) * pulseCount);
        Serial.println("Pulse: " + String(pulse));

        if (pulseAmount == 0 and pulseCount > 0) {
            startTime = millis();
        }

        oldPulseAmount = pulseAmount;
        pulseAmount += pulse;

        if (pulseAmount == oldPulseAmount and pulseAmount != 0) {
            float timeAmount = (millis()-startTime)/1000;
            Serial.println("Pulse Amount: " + String(pulseAmount));
            Serial.println("Time Amount: " + String(timeAmount));
        
            sendToServer(pulseAmount, timeAmount);
            pulseAmount = 0;
        }

        oldTime = millis();
        pulseCount = 0;

        attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    }
}

void networkStart ()
{
    Serial.println("Starting ethernet...");
    if (ether.begin(sizeof Ethernet::buffer, mac, 10) == 0) {
        Serial.println(F("Failed to access Ethernet controller"));
    }
    
    if (!ether.staticSetup(ip, gw, dns)) {
        Serial.println(F("Static IP failed"));
    }

    ether.printIp("IP:  ", ether.myip);

    dnsLookup();
}

void sendToServer (float pulseAmount, float timeAmount)
{
    dnsLookup();

    String params = "device_id=" + deviceId + "&pulse=" + String(pulseAmount) + "&time=" +  String(timeAmount);
    Serial.println("Sending: " + params + " Size: " + String(params.length()));

    byte sd = stash.create();
    stash.print(params);
    stash.save();
    int stashSize = stash.size();

    Stash::prepare(PSTR("POST http://$F/index.php?r=api/create HTTP/1.1" "\r\n"
"Host: $F \r\n"
"Content-Length: $D" "\r\n"
"Content-Type: application/x-www-form-urlencoded \r\n"
"\r\n"
"$H"), website, website, stashSize, sd);

    session = ether.tcpSend();
    if (stash.freeCount() <= 3) {
        Stash::initMap(56);
    }
}

void dnsLookup ()
{
    if (!ether.dnsLookup(website)) {
        Serial.println(F("DNS failed"));
    }

    ether.printIp("SRV: ", ether.hisip);
}

void receiveAnswer ()
{
    ether.packetLoop(ether.packetReceive());
  
    const char* reply = ether.tcpReply(session);
    if (reply != 0) {
        Serial.println(reply);
    }
}

void pulseCounter ()
{
    pulseCount++;
}

