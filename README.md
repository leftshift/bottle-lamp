# Bottle Lamp
Aimed at ESP8266 and compatible. Opens an Access Point, provides a website where animation, animation parameters and brightness can be controlled.
When using with an external power bank or battery shield, this can also be used when out and about

## Libraries
Uses the standard ESP8266 libraries from https://github.com/esp8266/Arduino for webserver, mDNS and such
FastLED, so this is compatible with most RGB-LED-Strips. Most animations taken from the supplied DemoReel100

## Changing the website
I'd like to automate this one day, but right now, you can run `python3 file_to_string.py website.html` which will generate `website.html.conv` which you can copy into `website.ino`.
