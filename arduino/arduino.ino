#include <EtherCard.h>

byte sensorInterrupt = 1;
byte sensorPin = 3;
byte redLedPin = 4;
byte greenLedPin = 5;

//CHANGE
String deviceId = "23";
uint8_t mac[6] = {0x00,0x01,0x02,0x23,0x23,0x23};
const static uint8_t ip[] = {192,168,1,123};
String token = "270590391d1e9dc96c77ab762d287007";
//CHANGE

//LAN
const static uint8_t gw[] = {192,168,1,1};
const static uint8_t dns[] = {192,168,1,1};
const char website[] PROGMEM = "ruanydepaula.com.br";
byte Ethernet::buffer[700];
static byte session;
Stash stash;
//LAN

volatile byte pulseCount;  
float pulse;
float pulseTotal;
unsigned long oldTime;

void setup()
{
    Serial.begin(9600);

    pinMode(sensorPin, INPUT_PULLUP);
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);

    pulseTotal = 0;
    networkStart();
}

void pulseCounter ()
{
    pulseCount++;
}

void networkStart ()
{
    bool isOk = true;
    
    setLed(redLedPin, HIGH);
    setLed(greenLedPin, HIGH);
    Serial.println("Starting ethernet...");
    if (ether.begin(sizeof Ethernet::buffer, mac, 10) == 0) {
        Serial.println(F("Failed to access Ethernet controller"));
        isOk = false;
    }
    
    if (!ether.staticSetup(ip, gw, dns)) {
        Serial.println(F("Static IP failed"));
        isOk = false;
    }

    if (!ether.dnsLookup(website)) {
        Serial.println(F("DNS failed"));
        isOk = false;
    }

    ether.printIp("IP:  ", ether.myip);
    ether.printIp("SRV: ", ether.hisip);

    if (isOk) {
        setLed(redLedPin, LOW);
        setLed(greenLedPin, HIGH);
    }
}

void loop()
{
    receiveAnswer();

    if ((millis() - oldTime) > 1000) { 
        detachInterrupt(sensorInterrupt);

        pulse = ((1000.0 / (millis() - oldTime)) * pulseCount);
        Serial.println("Pulse: " + String(pulse));

        pulse = 100;
        if (pulse != 0) {
            sendToServer(pulse);
            pulseTotal += pulse;
        }

        if (pulse == 0 && pulseTotal != 0) {
            Serial.println("Pulse Amount: " + String(pulseTotal));
            pulseTotal = 0;
            setLed(redLedPin, LOW);
            setLed(greenLedPin, HIGH);
        }

        oldTime = millis();
        pulseCount = 0;

        attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    }
}

void receiveAnswer ()
{
    ether.packetLoop(ether.packetReceive());
  
    const char* reply = ether.tcpReply(session);
    if (reply != 0) {
        Serial.println("Answer Received");
    }
}

void sendToServer (float pulseAmount)
{
    setLed(redLedPin, HIGH);
    setLed(greenLedPin, HIGH);

    String params = "device_id=" + deviceId + "&pulse=" + String(pulseAmount) + "&time=1&token=" + token;
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

void setLed (byte led, int statusLed)
{
    digitalWrite(led, statusLed);
}
