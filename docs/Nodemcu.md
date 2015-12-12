# Installing the firmware

Install the driver:
* [Driver](http://www.prolific.com.tw/US/ShowProduct.aspx?p_id=229&pcid=41)

If you have any problems with serial on new mac os versions (el capitain):

[http://scottbrant.net/?p=757](http://scottbrant.net/?p=757)

```
boot mac into recovery mode (command+r). hold it down until you see the mouse cursor
utilities, terminal
csrutil status
probably says enabled
csrutil disable
reboot
```

Download esptool.py:
* [Esptool](https://github.com/themadinventor/esptool)

Download NodeMCU:
* [NodeMCU](https://github.com/nodemcu/nodemcu-firmware/releases)

connect ESP8266 to USBSerial:
![Source: http://iot-playground.com/images/articles/016/esp8266-reflash-firmware.png](schemas/1.png)

![Source: https://raw.githubusercontent.com/guyz/pyesp8266/master/esp8266_pinout.png](schemas/2.png)

Install Python Serial:

```
wget https://bootstrap.pypa.io/get-pip.py
sudo python get-pip.py
sudo pip install pyserial
```

Then, run:
```
./esptool.py --port=/dev/cu.usbserial write_flash  -fm=dio -fs=32m 0x00000 nodemcu_float_0.9.6-dev_20150704.bin
```

It will return:
> Connecting...
> 
> Erasing flash...
> 
> Wrote 462848 bytes at 0x00000000 in 45.4 seconds (81.6 kbit/s)...
> 
> 
> Leaving...

Disconnect and connect the USB again


# Testing
![Source: unkonwn](schemas/3.png)


Open Esplorer:
[Esplorer](http://esp8266.ru/esplorer/)

Change configs to:
```
port: /dev/cu.usbserial
baudrate 9600
```
Click on Open, it should show:

> PORT OPEN 9600
> 
> Communication with MCU...
> 
> Got answer! AutoDetect firmware...
> 
> 
> Can't autodetect firmware, because proper answer not received.

Use the following script to do a Hello World:
[https://github.com/nodemcu/nodemcu-devkit/wiki/A-Simple-First-Script](https://github.com/nodemcu/nodemcu-devkit/wiki/A-Simple-First-Script)

After put the script on the left side, press "Save to ESP". It will show the script, line by line, on the right side.

# Fast tests

Open CoolTerm and try:
```
gpio.mode(3, gpio.OUTPUT)
gpio.write(3, gpio.UP)
gpio.write(3, gpio.DOWN)
```

# Node GPIO Map
![Source: http://pedrominatel.com.br/eletronica/esp8266-o-guia-basico-de-hardware/](schemas/4.png)

# Useful links
* [https://github.com/nodemcu/nodemcu-firmware/wiki/nodemcu_api_en](https://github.com/nodemcu/nodemcu-firmware/wiki/nodemcu_api_en)
* [https://github.com/nodemcu/nodemcu-devkit/wiki/Getting-Started-on-OSX](
https://github.com/nodemcu/nodemcu-devkit/wiki/Getting-Started-on-OSX)