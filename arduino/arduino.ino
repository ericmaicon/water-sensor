#include <SoftwareSerial.h>

//pins configuration
byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin = 2;

//Wifi + Server config
String ssid = "GVT-3EF8";
String pwd = "0148272560";
String serverIp = "192.241.153.56";
int serverPort = 80;
String deviceId = "1";

//Serial config
SoftwareSerial wifi(10, 11); // RX, TX


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
    wifiStart();

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
            Serial.println(pulseAmount);
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
void wifiStart ()
{
    wifi.begin(9600);
    sendCommand("AT+RST", "OK", 60);
    //bool connected = wifi.joinAP(ssid, pwd);
    //wifi.enableMUX();
}

/**
 * Send to the API
 **/
void sendOrSave (float pulseAmount)
{
    String params = "device_id=" + deviceId + "&pulse=" + pulseAmount;
    String command = "POST /index.php?r=api/create HTTP/1.1\r\n";
    command += "Host: 192.241.153.56\r\n";
    command += "Content-Type: application/x-www-form-urlencoded\r\n";
    command += "Content-Length: " + String(params.length()) + "\r\n\r\n";
    command += params;

    int commandSize = command.length();

    char charBuf[commandSize];
    command.toCharArray(charBuf, commandSize);

    //wifi.createTCP(serverIp, serverPort);
    //10 = counting \r\n for each line on the command above
    Serial.println(command);
    //wifi.send(4, (uint8_t *)charBuf, commandSize + 10);
}

bool sendCommand(String cmd, String goodResponse, unsigned long timeout) {
    Serial.println("espSendCommand( " + cmd + " , " + goodResponse + " , " + String(timeout) + " )" );
    wifi.println(cmd);
    unsigned long tnow = millis();
    unsigned long tstart = millis();
    unsigned long execTime = 0;
    String response = "";
    char c;
    while( true ) {
        if( tnow > tstart + timeout ) {
            Serial.println("espSendCommand: FAILED - Timeout exceeded " + String(timeout) + " seconds" );
            if( response.length() > 0 ) {
                Serial.println("espSendCommand: RESPONSE:");
                Serial.println( response );
            } else {
                Serial.println("espSendCommand: NO RESPONSE");
            }
            return false;
        }
        c = wifi.read();
        if( c >= 0 ) {
            response += String(c);
            if( response.indexOf(goodResponse) >= 0 ) {
                execTime = ( millis() - tstart );
                Serial.println("espSendCommand: SUCCESS - Response time: " + String(execTime) + "ms");
                Serial.println("espSendCommand: RESPONSE:");
                Serial.println(response);
                while(wifi.available() > 0) {
                    Serial.write(wifi.read());
                }
                return true;
            }
        }
        tnow = millis();
    }
}

/**
 * Initerrupt Function
 **/
void pulseCounter ()
{
    pulseCount++;
}
