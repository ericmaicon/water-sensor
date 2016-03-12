#include <SPI.h>
#include <UIPEthernet.h>

//pins configuration
byte sensorInterrupt = 1;  // 0 = digital pin 2
byte sensorPin = 3;

//Lan + Server config
byte mac[] = { 0xDE, 0xAD, 0xBE, 0x05, 0x05, 0x05 };
IPAddress server(192,241,153,56);
EthernetClient client;
String deviceId = "5";

//pulse vars
volatile byte pulseCount;
float pulseAmount;
float oldPulseAmount;
float halfTime;
float timeAmount;

unsigned long currentTime;
unsigned long cloopTime;

/**
 * Setup
 **/
void setup()
{
    Serial.begin(9600);
    Serial.println("Start");
    networkStart();

    pinMode(sensorPin, INPUT_PULLUP);
    digitalWrite(sensorPin, HIGH);

    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

/**
 * Main program loop
 **/
void loop()
{
    currentTime = millis();
    if (currentTime >= (1000 + cloopTime))
    { 
        cloopTime = currentTime;
        oldPulseAmount = pulseAmount;

        //sum all pulses
        pulseAmount += pulseCount;
        timeAmount++;
        if (pulseAmount == oldPulseAmount and pulseAmount != 0) {
            sendOrSave(pulseAmount, timeAmount);
            timeAmount = 0;
            pulseAmount = 0;  
        }

        // Reset the pulse counter so we can start incrementing again
        pulseCount = 0;
    }
}

/**
 * Connect to the serial
 * Start the wifi
 **/
void networkStart ()
{
    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
    }
    
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
}

/**
 * Send to the API
 **/
void sendOrSave (float pulseAmount, float timeAmount)
{
    String params = "device_id=" + deviceId + "&pulse=" + String(pulseAmount) + "&time=" +  String(timeAmount);

    client.stop();
    if (client.connect(server, 80)) {
        Serial.println("Sending: " + params + " Size: " + String(params.length()));
        
        client.println("POST /index.php?r=api/create HTTP/1.1");
        client.println("Host: localhost");
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.println("Content-Length: " + String(params.length()));
        client.println();
        client.println(params);
        client.println();
        Serial.println(client.read());
    } else {
        Serial.println("connection failed");
    }
}


/**
 * Initerrupt Function
 **/
void pulseCounter ()
{
    pulseCount++;
}
