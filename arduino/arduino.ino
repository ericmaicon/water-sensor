/**
 * @example http://diyhacking.com/projects/FlowMeterDIY.ino
 * @tutorial http://diyhacking.com/arduino-flow-rate-sensor/
 * @shop http://www.hobbytronics.co.uk/yf-s201-water-flow-meter
 * @shop http://www.filipeflop.com/pd-206c5b-sensor-de-fluxo-de-agua-1-2-yf-s201.html
 * @datasheet http://www.hobbytronics.co.uk/datasheets/sensors/YF-S201.pdf
 **/

 #include <SoftwareSerial.h>
 #include <stdlib.h>
 
//RX pin 2, TX pin 3
SoftwareSerial esp8266(2, 3);

int sensorId = 1;
String serverIp = "192.168.25.70";
String serverPort = "3000";

byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin = 2;

volatile byte pulseCount;

float flowRate;
float sumFlowRate;
unsigned long sumSeconds;

unsigned long oldTime;

#define DEBUG true

/**
 *
 **/
void setup ()
{
    // Initialize a serial connection for reporting values to the host
    Serial.begin(9600);

    pinMode(sensorPin, INPUT);
    digitalWrite(sensorPin, HIGH);

    pulseCount = 0;
    oldTime = 0;

    // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
    // Configured to trigger on a FALLING state change (transition from HIGH
    // state to LOW state)
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);

    //connect and reset
    startServer();
}

/**
* Main program loop
*/
void loop()
{
    // Only process counters once per second
    if((millis() - oldTime) > 1000) {
        // Disable the interrupt while calculating flow rate and sending the value to
        // the host
        detachInterrupt(sensorInterrupt);

        // Because this loop may not complete in exactly 1 second intervals we calculate
        // the number of milliseconds that have passed since the last execution and use
        // that to scale the output. 
        flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount);

        // Note the time this processing pass was executed. Note that because we've
        // disabled interrupts the millis() function won't actually be incrementing right
        // at this point, but it will still return the value it was set to just before
        // interrupts went away.
        oldTime = millis();

        // Reset the pulse counter so we can start incrementing again
        pulseCount = 0;

        // Enable the interrupt again now that we've finished sending output
        attachInterrupt(sensorInterrupt, pulseCounter, FALLING);

        //
        if (flowRate > 0) {
            sumFlowRate += flowRate;
            sumSeconds++;
        }

        //
        if (flowRate == 0 and sumFlowRate > 0) {
            Serial.println("Sending data...");
            sendToServer(sumFlowRate, sumSeconds, sensorId);
            
            sumFlowRate = 0;
            sumSeconds = 0;
        }
        
        Serial.print("Flow:");
        Serial.println(flowRate);
    }
}

/**
 * Insterrupt Service Routine
 **/
void pulseCounter ()
{
    pulseCount++;
}

/**
 * Start the server
 **/
void startServer ()
{
    esp8266.begin (9600);
    sendData("AT+RST", 2000);
    sendData("AT+CWMODE=3", 2000);
    sendData("AT+CWJAP=\"GVT3EF8\",\"0148272560\"", 2000);
    Serial.println("Server iniciado");
}

/**
 * Send data
 **/
String sendData(String command, const int timeout)
{
    String response = "";
    if (DEBUG) {
        Serial.println(command);
    }
    esp8266.print(command);

    long int time = millis();
    while ((time + timeout) > millis()) {
        while (esp8266.available()) {
            // The esp has data so display its output to the serial window
            char c = esp8266.read(); // read the next character.
            response += c;
        }
    }
    if (DEBUG) {
        Serial.println(response);
    }
    return response;
}

/**
 * 
 **/
String sendToServer (float flow, float time, int sensorId)
{
    // TCP connection
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += serverIp;
    cmd += "\",";
    cmd += serverPort;
    sendData(cmd, 2000);

    // prepare GET string
    cmd = "AT+CIPSEND=GET /?device_id=";
    cmd += String(sensorId);
    cmd += "&flow=";
    cmd += String(time);
    cmd += "&time=";
    cmd += String(time);

    sendData(cmd, 2000);
}

