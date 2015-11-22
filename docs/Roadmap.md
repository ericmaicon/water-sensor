# Roadmap

* Update ESP8266 firmware
* Test the sensor via serial
* Create the circuit
* Develop the system

# The circuit:

* a 5V DC is required
* Converts it to 3.3V with 250mA of current.
* Use 5V on the sensor.
* Use 3.3V on ESP8266
* Use USBSerial
* Create a switch to update or use the GPIO.

# The Circuit System:

* Capture data from the water flow sensor
* Store it
* Check if it has internet, if it has, send it. If it does not have internet, keep trying.

# The WEB System:

* Create an endpoint to receive values
* Check if is receiving data from a sensor, if not, alert.
* Show Charts.
* Show Storage data.