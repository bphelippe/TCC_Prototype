#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <dht.h>

//Digital
#define dht22_pin       2
//#define dustLed_pin     3

//Analog
//#define dustSensor_pin  0
#define mq002_pin       1
#define mq007_pin       2
#define mq135_pin       3

Adafruit_BMP085 bmp;
dht DHT;
int mq002;
int mq007;
int mq135;
int chk;
//float dust;
float temperature_bmp;
float pressure_bmp;
float temperature_dht;
float humidity_dht;

void setup() {
  Serial.begin(9600);
  //pinMode(dustLed_pin, OUTPUT);
  /*
    bmp.begin(mode)
    ULTRALOWPOWER mode = 0
    STANDARD      mode = 1
    HIGHRES       mode = 2
    ULTRAHIGHRES  mode = 3
  */
  if (!bmp.begin(3)) Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
}

void loop() {
  chk   = DHT.read22(dht22_pin);
  mq002 = analogRead(mq002_pin);
  mq007 = analogRead(mq007_pin);
  mq135 = analogRead(mq135_pin);
  temperature_bmp = bmp.readTemperature();
  pressure_bmp = bmp.readPressure();
  temperature_dht = DHT.temperature;
  humidity_dht = DHT.humidity;

  /*
    digitalWrite(dustLed_pin, LOW); // power on the LED
    delayMicroseconds(280);
    dust = analogRead(dustSensor_pin); // read the dust value via pin 5 on the sensor
    delayMicroseconds(40);
    digitalWrite(dustLed_pin, HIGH); // turn the LED off
    delayMicroseconds(9680);
  */

  Serial.print("MQ002= ");
  Serial.print(mq002);
  Serial.println("\tLPG, i-butane, propane, methane, alcohol, Hydrogen, smoke");
  Serial.print("MQ007= ");
  Serial.print(mq007);
  Serial.println("\tcarbon monoxide(CO)");
  Serial.print("MQ135= ");
  Serial.print(mq135);
  Serial.println("\tNH3, NOx, alcohol, Benzene, smoke, CO2, etc");

  /*
    Serial.print("Dust= ");
    Serial.print(dust);
    Serial.println(" mg/m3");
  */

  Serial.print("Temperature.BMP= ");
  Serial.print(temperature_bmp, 1);
  Serial.print("\t");
  Serial.print("Pressure= ");
  Serial.print(pressure_bmp / 100, 2);
  Serial.println(" hPa");

  Serial.print("Temperature.DHT= ");
  Serial.print(temperature_dht, 1);
  Serial.print("\t");
  Serial.print("Humidity= ");
  Serial.println(humidity_dht, 1);

  Serial.println("");

  delay(5000);        // delay in between reads for stability
}
