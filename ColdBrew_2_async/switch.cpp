// switch.cpp
#include "switch.h"
#include "variables.h"
#include "wifi_mqtt.h"
#include "utils.h"

void orderCoffeeCleaning(){
  Serial.println("커피머신 세정 시작");
  if(!systemStatus){
    Serial.println("이미 동작중입니다");
    return;
  }
  systemStatus = false;
  currentProcess = COFFEE_CLEANING;

  getCoffeeMachineStatus();

  if(coffeeMachineStatus){
    Serial.println("커피머신 대기 확인 세척시작");
    
    client.publish(middleServer1, "coffeeMachine/cleaning");
    getCoffeeMachineStatus();
    Serial.print("현재 확인된 커피머신 상태");
    Serial.println(coffeeMachineStatus);
    
    while(!coffeeMachineStatus){
      client.loop();
      yield(); // 와치독 타이머를 리셋

      delay(100);
    }
    Serial.println("커피머신 세정 종료");
    systemStatus = true;
    currentProcess = NONE;

  }else{
    Serial.println("커피머신이 대기상태가 아닙니다.");
    systemStatus = true;
    currentProcess = NONE;
    return;
  }
}

void orderCoffeeLowerCleaning(){
  
}