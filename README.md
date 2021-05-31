# SonoffPow
Alexa ESP8266 firmware for Sonoff Pow 

Simple connected plug using FauxmoESP library (Philips Hue Fake Device).

Note: HLW8012 component (Energy meter) is not used.

*Libraries needed:*
* FauxmoESP https://bitbucket.org/xoseperez/fauxmoesp/src/master/
* ESPAsyncTCP https://github.com/me-no-dev/ESPAsyncTCP

Arduino SDK or platformIO (tested with nodemcu 0.9)

+ Red  led = Relay state (on=relay on off=relay off) buildin
+ Blue led = Wifi state (blinking=connected on=not connected off=no power)


*Use a TTL serial converter (3.3v) and press button for downloading code inside Sonoff Pow*

![alt text](https://github.com/tirfil/SonoffPow/blob/main/IMG_20210529_190255.jpg)

Warning:
Open the case and downloading this firmware voids the product warranty.

