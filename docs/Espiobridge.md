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

Download esp8266-universal-io-bridge Firmware:
* [esp8266-universal-io-bridge Firmware](https://github.com/eriksl/esp8266-universal-io-bridge/releases/download/11/espiobridge.bin)

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
./esptool.py --port=/dev/cu.usbserial write_flash -fm=dio -fs=32m 0x00000 espiobridge.bin
```

It will return:
> Connecting...
> 
> Erasing flash...
> 
> Wrote 264192 bytes at 0x00000000 in 26.0 seconds (81.1 kbit/s)...
> 
> 
> Leaving...

# Testing

1. Remove the pin 2 from the ground
2. unplug and plug again the usbserial



# Useful links
* [https://github.com/eriksl/esp8266-universal-io-bridge](https://github.com/eriksl/esp8266-universal-io-bridge)
* [http://www.esp8266.com/viewtopic.php?f=6&t=3959&start=76](http://www.esp8266.com/viewtopic.php?f=6&t=3959&start=76)