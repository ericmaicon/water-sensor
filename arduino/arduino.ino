#include <SPI.h>
#include <UIPEthernet.h>

//pins configuration
byte sensorInterrupt = 1;  // 0 = digital pin 2
byte sensorPin = 3;

//Lan + Server config
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(192,241,153,56);
EthernetClient client;
String deviceId = "1";

//pulse vars
volatile byte pulseCount;
float pulse;
float pulseAmount;
float oldPulseAmount;

unsigned long oldTime;

/**
 * Setup
 **/
void setup()
{
    Serial.begin(9600);
    networkStart();

    pinMode(sensorPin, INPUT);
    digitalWrite(sensorPin, HIGH);

    pulseCount = 0;
    pulse = 0;
    pulseAmount = 0;
    oldTime = 0;

    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

/**
 * Main program loop
 **/
void loop()
{
    if (client.available()) {
        char c = client.read();
        Serial.write(c);
    }
  
    if ((millis() - oldTime) > 1000)
    {
        // Disable the interrupt while calculating flow rate
        detachInterrupt(sensorInterrupt);

        //the amount of pulse is calculated per seconds. If the flow stops in the middle of a second, 
        //the following code calculate the fraction of it.
        pulse = ((1000.0 / (millis() - oldTime)) * pulseCount);

        oldTime = millis();


        oldPulseAmount = pulseAmount;

        //sum all pulses
        pulseAmount += pulse;
        if (pulseAmount == oldPulseAmount and pulseAmount != 0) {
            sendOrSave(pulseAmount);
            pulseAmount = 0;
        }

        // Reset the pulse counter so we can start incrementing again
        pulseCount = 0;

        // Enable the interrupt again now that we've finished sending output
        attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
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
void sendOrSave (float pulseAmount)
{
    String params = "device_id=1&pulse=" + String(pulseAmount);

    client.stop();
    if (client.connect(server, 80)) {
        Serial.println("Sending: " + params);
        
        client.println("POST /index.php?r=api/create HTTP/1.1");
        client.println("Host: 192.241.153.56");
        client.println("Content-Type: application/x-www-form-urlencoded");
        //client.println("Content-Length: " + params.length());
        client.println(params);
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
