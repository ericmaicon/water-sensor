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

# Sequence AT commands used to test with the API

AT+CWLAP
AT+CIFSR

AT+RST
AT+CWMODE=1
AT+CIPMUX=1
AT+CWJAP="",""
AT+CIPSTART=4,"TCP","192.241.153.56",80
AT+CIPSEND=4,178
POST /index.php?r=api/create HTTP/1.1
Host: 192.241.153.56
Content-Type: application/x-www-form-urlencoded
Content-Length: 20

device_id=1&pulse=10

AT+CIPCLOSE

# Useful links
* [https://www.youtube.com/watch?v=Na7CSbq467M](https://www.youtube.com/watch?v=Na7CSbq467M)
* [http://electronut.in/an-iot-project-with-esp8266/](http://electronut.in/an-iot-project-with-esp8266/)
* [http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module](http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module)
* [http://www.cse.dmu.ac.uk/~sexton/ESP8266/](http://www.cse.dmu.ac.uk/~sexton/ESP8266/)
* [http://mcuoneclipse.com/2014/12/14/tutorial-iot-datalogger-with-esp8266-wifi-module-and-frdm-kl25z/](http://mcuoneclipse.com/2014/12/14/tutorial-iot-datalogger-with-esp8266-wifi-module-and-frdm-kl25z/)
* [http://rootpower.com/?p=73](http://rootpower.com/?p=73)
* [http://contractorwolf.com/esp8266-wifi-arduino-micro/](http://contractorwolf.com/esp8266-wifi-arduino-micro/)
* [https://github.com/contractorwolf/ESP8266](https://github.com/contractorwolf/ESP8266)
* [http://br-arduino.org/2015/05/esp8266-arduino-facil.html](http://br-arduino.org/2015/05/esp8266-arduino-facil.html)
* [https://cdn.sparkfun.com/assets/learn_tutorials/4/0/3/4A-ESP8266__AT_Instruction_Set__EN_v0.30.pdf](https://cdn.sparkfun.com/assets/learn_tutorials/4/0/3/4A-ESP8266__AT_Instruction_Set__EN_v0.30.pdf)
* [http://aura-comms.com/ac/getting-started-with-the-esp8266/](http://aura-comms.com/ac/getting-started-with-the-esp8266/)