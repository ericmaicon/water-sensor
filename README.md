# About it

This is a project for a master degree with the goal of store water flow data in a house.

It uses a flow sensor, connected on an ESP8266 to send it thought the internet to an endpoint.
It has a USBSerial to update the ESP8266 firmware and code.

[Roadmap](docs/Roadmap.md)

Some studies about ESP8266:

[Espruino firmware](docs/Espruino.md)
[NodeLUA firmware](docs/Nodelua.md)
[NodeMCU firmware](docs/Nodemcu.md)

===
# Fast tests

Open CoolTerm and try:
```
gpio.mode(3, gpio.OUTPUT)
gpio.write(3, gpio.UP)
gpio.write(3, gpio.DOWN)
```

===
# Useful Links

## Schematics
[Convert 5V to 3.3V](http://kb.kaminskiengineering.com/node/171)
[Convert AC to DC](http://www.elprocus.com/steps-to-convert-the-230v-ac-to-5v-dc/)

## Flow Sensor
[Sensor](http://www.seeedstudio.com/wiki/G1'1/4_Water_Flow_sensor)
[Datasheet](http://www.seeedstudio.com/depot/datasheet/water%20flow%20sensor%20datasheet.pdf)
[Portuguese Tutorial](http://labdegaragem.com/profiles/blogs/tutorial-como-utilizar-o-sensor-de-fluxo-de-agua)

## ESP8266
[GPIO API](http://esp8266.co.uk/tutorials/introduction-to-the-gpio-api/)
[Flow Sensor and ESP8266](http://www.esp8266.com/viewtopic.php?f=18&t=5624)