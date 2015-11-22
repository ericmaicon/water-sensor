# Installing the firmware

Download esptool.py:
[Esptool](https://github.com/themadinventor/esptool)

Download nodelua:
[Nodelua](http://nodelua.org/download_firmware)

connect ESP8266 to USBSerial:
![Source: http://iot-playground.com/images/articles/016/esp8266-reflash-firmware.png](schemas/1.png)
![Source: https://raw.githubusercontent.com/guyz/pyesp8266/master/esp8266_pinout.png](schemas/2.png)

Then, run:
```
./esptool.py -p /dev/cu.usbserial write_flash 0x00000 nodelua_8266.fw
```

It will return:
> Connecting...
> Erasing flash...
> Wrote 62464 bytes at 0x00000000 in 6.1 seconds (81.9 kbit/s)...
> Erasing flash...
> Wrote 371712 bytes at 0x00010000 in 36.6 seconds (81.3 kbit/s)...
> 
> Leaving...

Disconnect and connect the USB again

===
# Testing
![Source: unkonwn](schemas/3.png)

Install minicom
(Minicom)[http://pbxbook.com/other/sw/minicom-2.2.zip]

Configure minicom:
> /opt/minicom/2.2/bin/minicom -s

Connect:
> /opt/minicom/2.2/bin/minicom -D /dev/cu.usbserial -b 115200 -c on

===
# Useful links
[http://nodelua.org/doc/tutorial/make-your-first-node/](http://nodelua.org/doc/tutorial/make-your-first-node/)