#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <SD.h>

TinyGPSPlus gps;
SoftwareSerial ss(4, 3);
Adafruit_BMP085 bmp;
LiquidCrystal lcd(1, 2, 6, 7, 8, 9);
const byte SDCARD_CS_PIN = 10;

#define time_offset 3600
char Time[] = "00:00:00";
char TimeWithoutSec[] = "00:00";
char Date[] = "00/00/2000";
byte last_second, Second, Minute, Hour, Day, Month;
int Year;

void setup(){
  pinMode(10, OUTPUT);
  if (!SD.begin(SDCARD_CS_PIN)) {}
  File file = SD.open("Data.txt", FILE_WRITE);
  file.println()
  file.println("Date;Hour;altitude(GPS);altitude(CPT);gap;pressure;latitude;longitude;temperature");
  file.flush();
  file.close();

  lcd.begin(16, 2);
  ss.begin(9600);
  if (!bmp.begin()) {
    while (1) {}
  }
}

static void smartDelay(unsigned long ms){
  unsigned long start = millis();
  do{
    while (ss.available()){
      gps.encode(ss.read());
    }
  }
  while (millis() - start < ms);
}

 static void printFloat(float val, bool valid, int prec){
  if (!valid){
    Serial.println("Invalid");
  }
  else{
    Serial.println(val, prec);
  }
  smartDelay(250);
}

void loop(){
  while (ss.available() > 0){
    if (gps.encode(ss.read())){
      displayInfo();
      sdcard();
    }
  }
}

static void sdcard() {
  File file = SD.open("Data.txt", FILE_WRITE);
  file.print(Date);
  file.print(";");
  file.print(Time);
  file.print(";");
  file.print(gps.altitude.meters(), 0);
  file.print(";");
  file.print(bmp.readAltitude(100600), 0);
  file.print(";");
  float ecart = (abs(gps.altitude.meters() - bmp.readAltitude(100600)) / gps.altitude.meters())*100;
  file.print(ecart);
  file.print("%");
  file.print(";");
  file.print(bmp.readPressure());
  file.print(";");
  file.print(gps.location.lat(), 6);
  file.print(";");
  file.print(gps.location.lng(), 6);
  file.print(";");
  file.print(bmp.readTemperature(), 1);
  file.println();
  file.flush();
  file.close();
}

static void displayInfo(){
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 1);
  printFloat(gps.location.lat(), gps.location.isValid(), 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 6);

  if (gps.date.isValid()){
    Day = gps.date.day();
    Month = gps.date.month();
    Year = gps.date.year();
  }

  if (gps.time.isValid()){
    Minute = gps.time.minute();
    Second = gps.time.second();
    Hour = gps.time.hour();
  }

  if(last_second != gps.time.second()){
    last_second = gps.time.second();
    setTime(Hour, Minute, Second, Day, Month, Year);
    adjustTime(time_offset);

    Time[6] = second() / 10 + '0';
    Time[7] = second() % 10 + '0';
    Time[3] = minute() / 10 + '0';
    Time[4] = minute() % 10 + '0';
    Time[0] = hour() / 10 + '0';
    Time[1] = hour() % 10 + '0';

    TimeWithoutSec[0] = Time[0];
    TimeWithoutSec[1] = Time[1];
    TimeWithoutSec[3] = Time[3];
    TimeWithoutSec[4] = Time[4];

    Date[8] = (year() / 10) % 10 + '0';
    Date[9] = year() % 10 + '0';
    Date[3] = month() / 10 + '0';
    Date[4] = month() % 10 + '0';
    Date[0] = day() / 10 + '0';
    Date[1] = day() % 10 + '0';
  }

  lcd.setCursor(0, 0);
  lcd.print("Gps");
  lcd.setCursor(0, 1);
  lcd.print(gps.altitude.meters(), 0);
  lcd.setCursor(5, 0);
  lcd.print("Cpt");
  lcd.setCursor(5, 1);
  lcd.print(bmp.readAltitude(100600), 0);
  lcd.setCursor(10, 0);
  lcd.print("Hour");
  lcd.setCursor(10, 1);
  lcd.print(TimeWithoutSec);
}
