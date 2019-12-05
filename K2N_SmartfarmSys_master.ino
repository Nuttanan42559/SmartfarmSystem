#include <TaskScheduler.h>
#include <Wire.h>
#include <DHT.h>
//#include <BH1750FVI.h>
//#include <NTPClient.h>
//#include <WiFiUdp.h>
//#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
//#include <WiFiClient.h>
//#include <BlynkSimpleEsp32.h>

#define POT(x) Serial.print(x); 
#define PUT(x) Serial.println(x); 

#define SlaveNano 5

//char ssid_name[] = "SHA256";
//char password[] = "123456789";
//char auth[] = "8e75203d0b2446f09fd580b74f01b392";

Scheduler task;
void task1();
void task2();
Task t1 (100 * TASK_MILLISECOND, TASK_FOREVER, &task1, &task, true);
Task t2 (100 * TASK_MILLISECOND, TASK_FOREVER, &task2, &task, true);
//BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
DHT dht1(18, DHT22);
DHT dht2(19, DHT22);
//LiquidCrystal_I2C monitors(0x27, 20, 4);

int state = 0;

void setup() {
  Serial.begin(115200);
//  WiFi.begin(ssid_name, password);
  Wire.begin();
  dht1.begin();
  dht2.begin();
//  LightSensor.begin();
//  monitors.begin();
//  monitors.backlight();
//  //_________________________ .
//  monitors.setCursor(4, 0);
//  monitors.print("K2N. Monitor");
//  monitors.setCursor(0, 1);
//  monitors.print("Temps_in : ");
//  monitors.setCursor(0,2);
//  monitors.print("Temps_out : ");
//  monitors.setCursor(0, 3);
//  monitors.print("Humidity : ");
//  //_________________________ .
  
}

void loop() {
  task.execute();
}

void task1() {
//  uint16_t lux = LightSensor.GetLightIntensity();
//  Serial.println(lux);
//  if(lux < 20){
//    state = 101;
//    Wire.beginTransmission(SlaveNano);
//    Wire.write(state);
//    Wire.endTransmission();
//  }
//  else if(lux > 20){ 
//    state = 100;
//    Wire.beginTransmission(SlaveNano);
//    Wire.write(state);
//    Wire.endTransmission();
//  }
}

void task2() {
  int temps1 = dht1.readTemperature();
  int humis1 = dht1.readHumidity();
  int temps2 = dht2.readTemperature();
  int humis2 = dht2.readHumidity();
  Serial.println(temps1);
  Serial.println(temps2);
//  monitors.setCursor(11, 1);
//  monitors.print(temps1);
//  monitors.setCursor(12, 2);
//  monitors.print(temps2);
//  monitors.setCursor(11, 3);
//  monitors.print(humis1);
  if(temps1 < temps2){
    state = 201;
    Wire.beginTransmission(SlaveNano);
    Wire.write(state);
    Wire.endTransmission();
  }
  else if(temps1 >= temps2){
    state = 200;
    Wire.beginTransmission(SlaveNano);
    Wire.write(state);
    Wire.endTransmission();
  }
}
