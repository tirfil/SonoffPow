# SonoffPow
Alexa ESP8266 firmware for Sonoff Pow 

Simple connected plug using FauxmoESP library (Philips Hue Fake Device).

Note: HLW8012 component (Energy meter) is not used.

*Libraries needed:*
* FauxmoESP https://bitbucket.org/xoseperez/fauxmoesp/src/master/
* ESPAsyncTCP https://github.com/me-no-dev/ESPAsyncTCP

Arduino SDK (tested with nodemcu 0.9)

+ Red  led = Relay state (on=relay on off=relay off) buildin
+ Blue led = Wifi state (blinking=connected on=not connected off=no power)

