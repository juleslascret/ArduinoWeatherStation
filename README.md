# ArduinoWeatherStation

This is the code for an **Arduino Weather Station** using and Arduino Uno and these external components :
- A gps *NEO-6m*
- A MicroSD card adapter
- A barometric Sensor *GY-68*
- An LCD screen 16x2

### Here's how it works :

First it picks up ***date, hour, altitude, longitude, latitude*** from the gps and ***altitude, air pressure, temperature*** from the barometric sensor, then it
writes in a .txt file (stored in the MicroSD card) all this data every second. It also displays on the LCD screen the hour and both altitudes. The LCD's contrast can be adjusted by a 10kΩ potentiometer.

### Some Pictures :

![Imgur](https://i.imgur.com/cRvQRQZ.jpg)
![Imgur](https://i.imgur.com/hTr37KB.jpg)
![Imgur](https://i.imgur.com/I3wEVip.jpg)
![Imgur](https://i.imgur.com/eHRCKYs.jpg)
![Imgur](https://i.imgur.com/7mmzeo3.jpg)
