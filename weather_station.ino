//added to github at 11am

#include <Wire.h>
#include <math.h>
#include "AMS_5600.h"
#include "Adafruit_HTU21DF.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define N 45

#define SEALEVELPRESSURE_HPA (1013.25)


// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
float angle;

AMS_5600 ams5600;
Adafruit_HTU21DF htu = Adafruit_HTU21DF();
Adafruit_BME280 bme;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   sensors.begin();
  Wire.begin();
  
  if (!htu.begin()) {
    Serial.println("Couldn't find HTU sensor!");
    while (1);
  }

      if (!bme.begin()) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  angle=ams5600.getScaledAngle()*0.0879;
  Serial.print("Angle: ");Serial.println(ams5600.getScaledAngle()*0.0879);
  windDirection();
  Serial.print("HTU21  Temp: "); Serial.print(htu.readTemperature());
  Serial.print("\t\tHum: "); Serial.println(htu.readHumidity());
  printValues();
    sensors.requestTemperatures(); 
      //print the temperature in Celsius
  Serial.print("DS18B Temp: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(" *C");
  Serial.println();
    Serial.println();
  delay(300000);
}

void printValues() {
    Serial.print("BME280 Temp: ");
    Serial.print(bme.readTemperature());
    Serial.print(" *C");

    Serial.print("\t\tHum: ");
    Serial.print(bme.readHumidity());
    Serial.print(" %");
    
    Serial.print("\t\t Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.print("\t\t hPa");

    Serial.print("\t\tApprox. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
};

void windDirection(){
  int angleInt = round(float((int(angle)-N+360)%360)/45);


  switch(angleInt){
    case 1:
      Serial.println("Wind Direction: NE");
      break;
    case 2:
      Serial.println("Wind Direction: E");
      break;
    case 3:
      Serial.println("Wind Direction: SE");
      break;
    case 4:
      Serial.println("Wind Direction: S");
      break;
    case 5:
      Serial.println("Wind Direction: SW");
      break;
    case 6:
      Serial.println("Wind Direction: W");
      break;
    case 7:
      Serial.println("Wind Direction: NW");
      break;
    default:
      Serial.println("Wind Direction: N");
    }
  
}
