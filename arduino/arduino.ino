#include <EtherCard.h>

byte sensorInterrupt = 1;
byte sensorPin = 3;
byte redLedPin = 4;
byte greenLedPin = 5;

//CHANGE
String deviceId = "7";
uint8_t mac[6] = {0x00,0x01,0x02,0x07,0x07,0x07};
const static uint8_t ip[] = {192,168,25,207};




String token = "270590391d1e9dc96c77ab762d287007";
//CHANGE

const static uint8_t gw[] = {192,168,25,1};
const static uint8_t dns[] = {192,168,25,1};
const char website[] PROGMEM = "ruanydepaula.com.br";
byte Ethernet::buffer[700];
static byte session;
Stash stash;
volatile byte pulseCount;  
float pulse;
float pulseTotal;
unsigned long oldTime;
unsigned long lastValidatedTime;
bool checkReset = false;

void setup()
{
    Serial.begin(9600);

    pinMode(sensorPin, INPUT_PULLUP);
    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);

    setLed(redLedPin, HIGH);
    setLed(greenLedPin, HIGH);
    delay(2000);
    setLed(redLedPin, LOW);
    setLed(greenLedPin, LOW);

    lastValidatedTime = millis();
    pulseTotal = 0;
    networkStart();
}

void loop()
{
    receiveAnswer();
    resetIfNecessary();

    if ((millis() - oldTime) > 1000)
    { 
        detachInterrupt(sensorInterrupt);

        pulse = ((1000.0 / (millis() - oldTime)) * pulseCount);
        Serial.println("Pulse: " + String(pulse) + ", Available memory: " + String(availableMemory()));
        
        if (pulse != 0) {
            sendToServer(pulse);
            pulseTotal += pulse;
        }

        if (pulse == 0 && pulseTotal != 0) {
            Serial.println("Pulse Amount: " + String(pulseTotal));
            pulseTotal = 0;
        }

        oldTime = millis();
        pulseCount = 0;

        attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    }
}

void networkStart ()
{
    setLed(redLedPin, HIGH);
    Serial.println("Starting ethernet...");
    if (ether.begin(sizeof Ethernet::buffer, mac, 10) == 0) {
        checkReset = true;
        Serial.println(F("Failed to access Ethernet controller"));
    }
    
    if (!ether.staticSetup(ip, gw, dns)) {
        checkReset = true;
        Serial.println(F("Static IP failed"));
    }

    ether.printIp("IP:  ", ether.myip);
    dnsLookup();
    setLed(redLedPin, LOW);
    setLed(greenLedPin, HIGH);
}

void sendToServer (float pulseAmount)
{
    checkReset = true;
    setLed(redLedPin, HIGH);
    setLed(greenLedPin, LOW);
    
    dnsLookup();

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

void dnsLookup ()
{
    if (!ether.dnsLookup(website)) {
        checkReset = true;
        Serial.println(F("DNS failed"));
    }

    ether.printIp("SRV: ", ether.hisip);
}

void receiveAnswer ()
{
    ether.packetLoop(ether.packetReceive());
  
    const char* reply = ether.tcpReply(session);
    if (reply != 0) {
        //Serial.println(reply);
        Serial.println("ok");
        setLed(redLedPin, LOW);
        setLed(greenLedPin, HIGH);
        checkReset = false;
        lastValidatedTime = millis();
    }
}

void pulseCounter ()
{
    pulseCount++;
}

void setLed (byte led, int statusLed)
{
    digitalWrite(led, statusLed);
}

void resetIfNecessary () {
    //Serial.println("Checking if reset is necessary: " + String(millis() - lastValidatedTime) + ", bool: " + String(checkReset));
    if (checkReset and millis() - lastValidatedTime > 60000) {
        asm volatile("  jmp 0");
    }
}

int availableMemory() {
    int size = 1024; // Use 2048 with ATmega328
    byte *buf;

    while ((buf = (byte *) malloc(--size)) == NULL);
    free(buf);

    return size;
}
