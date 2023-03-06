# ArduinoWeatherStation

This is the code for an **Arduino Weather Station** using these external components :
- A gps *NEO-6m*
- A MicroSD card adapter
- A barometric Sensor *GY-68*
- An LCD screen 16x2

### Here's how it works :

First it picks up ***date, hour, altitude, longitude, latitude*** from the gps and ***altitude, air pressure, temperature*** from the barometric sensor, then it
writes in a .txt file (stored in the MicroSD card) all this data every second. It also displays on the LCD screen the hour and both altitudes.

### Some Pictures :

![image] (files://C:/Users/jules.lascret/Desktop/IMG_0642.jpg)
