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

```
git clone git@github.com:themadinventor/esptool.git
```

Download AT Firmware:
* [AT Firmware](http://www.mediafire.com/download/bn1wpwmc4mcm48c/esp8266+Aplica%C3%A7%C3%A3o+%2B+firmware+%28Vers%C3%A3o+092+e+Lua%29.rar)

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
./esptool.py --port=/dev/cu.usbserial write_flash  -fm=dio -fs=32m 0x00000 v0.9.2.2\ AT\ Firmware.bin
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

1. Remove the pin 2 from the ground
2. unplug and plug again the usbserial

Open the Arduino IDE, check if the right usbserial is selected on Serial menu and change the baudrate to 9600.

Open the serial Monitor and type:

```
AT
```

It should return:

> AT
> 
> OK

Try:

```
AT+GMR
```

> AT+GMR
> 
> It should return the firmware serial:
> 0018000902
> 
> OK

# Useful links
* [https://www.youtube.com/watch?v=Na7CSbq467M](https://www.youtube.com/watch?v=Na7CSbq467M)
* [http://electronut.in/an-iot-project-with-esp8266/](http://electronut.in/an-iot-project-with-esp8266/)