# About it

This is a project for a master degree with the goal of store water flow data in a house.

It uses a flow sensor, connected on an ESP8266 to send it thought the internet to an endpoint.
It has a USBSerial to update the ESP8266 firmware and code.

* [Roadmap](https://github.com/ericmaicon/water-sensor/blob/master/docs/Roadmap.md)

Some research about ESP8266:

* [Espruino firmware](https://github.com/ericmaicon/water-sensor/blob/master/docs/Espruino.md)
* [NodeLUA firmware](https://github.com/ericmaicon/water-sensor/blob/master/docs/Nodelua.md)
* [NodeMCU firmware](https://github.com/ericmaicon/water-sensor/blob/master/docs/Nodemcu.md)
* [AT firmware](https://github.com/ericmaicon/water-sensor/blob/master/docs/AT.md)

Raspberry:

* [Install Debian on Raspberry from Mac](https://github.com/ericmaicon/water-sensor/blob/master/docs/Install-Raspberry.md)
* [Using raspberry and ESP8266 as router](https://github.com/ericmaicon/water-sensor/blob/master/docs/Raspberry.md)

# Useful Links

## Schematics
* [Convert 5V to 3.3V](http://kb.kaminskiengineering.com/node/171)
* [Convert AC to DC](http://www.elprocus.com/steps-to-convert-the-230v-ac-to-5v-dc/)

## Flow Sensor
* [Sensor](http://www.seeedstudio.com/wiki/G1'1/4_Water_Flow_sensor)
* [Datasheet](http://www.seeedstudio.com/depot/datasheet/water%20flow%20sensor%20datasheet.pdf)
* [Datasheet](http://www.hobbytronics.co.uk/datasheets/sensors/YF-S201.pdf)
* [Portuguese Tutorial](http://labdegaragem.com/profiles/blogs/tutorial-como-utilizar-o-sensor-de-fluxo-de-agua)
* [Code example](http://www.hobbytronics.co.uk/download/YF-S201.ino)
* [Tutorial](http://diyhacking.com/arduino-flow-rate-sensor/)
* [Code example](http://diyhacking.com/projects/FlowMeterDIY.ino)

## ESP8266
* [GPIO API](http://esp8266.co.uk/tutorials/introduction-to-the-gpio-api/)
* [Flow Sensor and ESP8266](http://www.esp8266.com/viewtopic.php?f=18&t=5624)
* [Two ESP8266 talking](http://randomnerdtutorials.com/how-to-make-two-esp8266-talk/)
* [Log data in MySQL](https://primalcortex.wordpress.com/2015/02/19/esp8266-logging-data-in-a-mysql-database/)

## Arduino
* [Ethercard](https://github.com/jcw/ethercard)

Arduino drive on MAC:
[Drive](http://www.wch.cn/download/CH341SER_MAC_ZIP.html)
Download, install.

Run:
`sudo nvram boot-args="kext-dev-mode=1"`
reboot