# Installing the firmware

Install the driver:
https://www.silabs.com/Support%20Documents/Software/Mac_OSX_VCP_Driver.zip

Download esptool.py:
[Esptool](https://github.com/themadinventor/esptool)

Download espruino:
[Espruino](https://github.com/nodemcu/nodemcu-firmware/releases)

connect ESP8266 to USBSerial:
![Pinout](https://raw.githubusercontent.com/guyz/pyesp8266/master/esp8266_pinout.png)
![Firmware](http://iot-playground.com/images/articles/016/esp8266-reflash-firmware.png)

Then, run:
```
./esptool.py --port=/dev/cu.usbserial write_flash  -fm=dio -fs=32m 0x00000 nodemcu_float_0.9.6-dev_20150704\ 2.bin
```

It will return:
> Connecting...
> Erasing flash...
> Wrote 462848 bytes at 0x00000000 in 45.4 seconds (81.6 kbit/s)...
> 
> Leaving...

Disconnect and connect the USB again

===
# Testing
Comunicando com espruino:
Mude a combinação dos fios para a imagem 3

Install the IDE
(Espruino IDE)[https://chrome.google.com/webstore/detail/espruino-web-ide/bleoifhkdalbjfbobjackfdifdneehpo?hl=pt-BR]

Change the baudrate in settings >> communications:
> Baud Rate: 9600

Connect using /dev/cu.usbserial

# Useful links
[
https://github.com/nodemcu/nodemcu-devkit/wiki/Getting-Started-on-OSX](
https://github.com/nodemcu/nodemcu-devkit/wiki/Getting-Started-on-OSX)