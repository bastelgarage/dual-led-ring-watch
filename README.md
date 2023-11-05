# dual-led-ring-watch
3D Printed Wall-Mounted NeoPixel LED Clock with NTP Synchronization

## Description
This project is a creative take on a digital clock, utilizing a circular arrangement of NeoPixel LEDs that face towards the wall, casting an ambient glow that visually represents the time. It is designed to be wall-mounted with the LED ring's connection point situated at the bottom for a cleaner appearance. The clock synchronizes with NTP servers for precise timekeeping and automatically adjusts for daylight saving time in the Central European Timezone (CET/CEST).

![NeoPixel LED Clock](/picture.jpg)

## Features
- **Ambient Wall Display**: The LED ring projects light onto the wall, creating a halo effect that is both functional and decorative.
- **NTP Time Synchronization**: Ensures the time displayed is always accurate by syncing with network time protocol servers.
- **Daylight Saving Time Ready**: With the Timezone library, it transitions smoothly for daylight saving time changes in CET/CEST zones.
- **Configurable LED Ring**: A strip of 2x 60 NeoPixel LEDs is arranged in a ring, with the ability to change colors to indicate hours and minutes.
- **Discreet Bottom Connection**: The power and data connections for the LED ring are located at the bottom, minimizing visibility and maintaining the clock's aesthetic.

## Hardware Components
- ESP8266 WiFi Microcontroller
- 2x 60 LED NeoPixel Ring
- 5V Power Supply (adequate for powering the LED ring)
- Logic Level Shifter (if needed by the ESP8266)

## Software Libraries
- `ESP8266WiFi` for WiFi functionality.
- `WiFiManager` for easy WiFi setup without hardcoding credentials.
- `Timezone` for handling local time and daylight saving adjustments.
- `TimeLib` for time-related functions.
- `NTPClient` for retrieving accurate time from internet servers.
- `Adafruit_NeoPixel` for controlling the NeoPixel LEDs.

## Setup Instructions
1. Secure the NeoPixel LED ring to the desired wall location, ensuring the connection point is oriented at the bottom.
2. Wire the LED ring to the ESP8266, taking care to connect to the correct data input and provide sufficient power.
3. Upload the provided sketch to the ESP8266 using an IDE like Arduino IDE.
4. At first startup, the device will create a WiFi access point named "NeoPixelClock" for configuration.
5. Connect to this access point with a smartphone or computer to input your WiFi network details.
6. The clock will then connect to your network and begin displaying the time, casting a beautiful ambient light onto the wall.

## Customization
Modify the `setTimeOnLEDs` function in the code to personalize the LED colors for hours and minutes to your taste or match your interior design.

## Tags

- `NeoPixel`
- `LED-Clock`
- `NTP-Synchronization`
- `ESP8266`
- `WiFi`
- `IoT`
- `Home-Automation`
- `DIY`
- `Arduino`
- `Timekeeping`
- `Wall-Clock`
- `Daylight-Saving`
- `CET`
- `CEST`
- `Ambient-Lighting`
- `bastelgarage`
