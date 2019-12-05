#include <Wire.h>
#include <TaskScheduler.h>
#include <BH1750FVI.h>
//____PIN_OUT .
#define H2O 2
#define Fert1 8
#define Fert2 9
#define H2M 7
#define M2P 6 
#define LSys 4
#define FSys 3

//____PIN_IN .

#define wtSeg1 A1
#define wtSeg2 A2

#define Open LOW
#define Close HIGH

Scheduler task;
void task1();
void task2();
void task3();
Task t1(100 * TASK_MILLISECOND, TASK_FOREVER, &task1, &task, true);
Task t2(100 * TASK_MILLISECOND, TASK_FOREVER, &task2, &task, true);
Task t3(100 * TASK_MILLISECOND, TASK_FOREVER, &task3, &task, true);
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
int dimt = 0;

void setup() {
  pinMode(H2O, OUTPUT);pinMode(Fert1, OUTPUT);pinMode(Fert2, OUTPUT);
  pinMode(H2M, OUTPUT);pinMode(M2P, OUTPUT);pinMode(LSys, OUTPUT);
  pinMode(FSys, OUTPUT);
  digitalWrite(H2O, Close);digitalWrite(Fert1, Close);digitalWrite(Fert2, Close);
  digitalWrite(H2M, Close);digitalWrite(M2P, Close);digitalWrite(LSys, Close);
  digitalWrite(FSys, Close);
  LightSensor.begin();
  Serial.begin(115200);
  Wire.begin(5);  
  Wire.onReceive(receivecall);
}

void receivecall(int buff){
  dimt = Wire.read();
  
}

void loop() {
  task.execute();
}

void task1(){
  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.println(lux);
  if(lux < 20){
     digitalWrite(LSys, Open);
  }
  else if(lux > 20){ 
    digitalWrite(LSys, Close);
  }
  
}

void task2(){
  if(dimt == 200){
    digitalWrite(FSys, Close);
  }
  else if(dimt == 201){
    digitalWrite(FSys, Open);
  }
}

void task3(){
  int wets_1 = analogRead(wtSeg1);
  int wets_2 = analogRead(wtSeg2);
//  int avg;
//  avg = (wets_1 + wets_2)/2;
  if(wets_2 > 900){
    digitalWrite(H2O, Open);
    digitalWrite(H2M, Open);
    digitalWrite(M2P, Open);
    digitalWrite(Fert1, Open);
    digitalWrite(Fert2, Open);
  }
  else if(wets_2 < 820) {
    digitalWrite(H2O, Close);
    digitalWrite(H2M, Close);
    digitalWrite(M2P, Close);
    digitalWrite(Fert1, Close);
    digitalWrite(Fert2, Close);
  }
}
