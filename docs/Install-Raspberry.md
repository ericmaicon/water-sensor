# Install Debian on Raspberry from Mac

1. First of all, download [SDFormatter](https://www.sdcard.org/downloads/formatter_4/)
2. Install and format your sdcard.
3. Download [Debian Jessie](https://www.raspberrypi.org/downloads/raspbian/)
4. Download [Pi Filler](http://ivanx.com/raspberrypi/)
5. Run it and install the jessie on your raspberry

# Expand the filesystem

1. After finish, put it on raspberry and start the SO.
2. Get logged in with user pi and password raspberry.
3. run the command:
```
raspi-config
```
4. Select the first option and reboot the system.
5. Run df -h and check the size of the filesystem.

# WIFI on Raspberry

```
vim /etc/network/interfaces
```

> auto wlan0
> allow-hotplug wlan0
> iface wlan0 inet dhcp
> wpa-ssid "WIFI_NAME"
> wpa-psk "WIFI_PASS"

```
ifdown wlan0
ifup wlan1
```

# Install node

```
curl -sLS https://apt.adafruit.com/add | sudo bash
sudo apt-get install node
node -v
v0.12.0
```

# Useful Links

[http://elinux.org/RPi_raspi-config#The_raspi-config_script](http://elinux.org/RPi_raspi-config#The_raspi-config_script)
[https://learn.adafruit.com/node-embedded-development/installing-node-dot-js](https://learn.adafruit.com/node-embedded-development/installing-node-dot-js)