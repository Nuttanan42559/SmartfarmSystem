#include <Wire.h>
#include <TaskScheduler.h>
//____PIN_OUT .
#define H2O 1
#define Fert1 7
#define Fert2 8
#define H2M 6
#define M2P 5 
#define LSys 3
#define FSys 2

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
int dimt = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(5);  
  Wire.onReceive(receivecall);
}

void receivecall(int buff){
  dimt = Wire.read();
}

void loop() {
  Serial.println(dimt);
  
}

void task1(){
  switch(dimt){
    case '101':
         digitalWrite(LSys, Open);
         break;
    case '100':
         digitalWrite(LSys, Close);
         break;
    default:
         digitalWrite(LSys, Close);
  }
}

void task2(){
  switch(dimt){
    case '201':
         digitalWrite(FSys, Open);
         break;
    case '200':
         digitalWrite(FSys, Close);
         break;
    default:
         digitalWrite(FSys, Close);
  }
}

void task3(){
  int wets_1 = analogRead(wtSeg1);
  int wets_2 = analogRead(wtSeg2);
  int avg;
  avg = (wets_1 + wets_2)/2;
  if(avg >= 840){
    digitalWrite(H2O, Open);
    delay(10000);
  }
  else if(avg <= 820) {
    digitalWrite(H2O, Close);
  }
}

