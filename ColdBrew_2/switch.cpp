// switch.cpp
#include "switch.h"
#include "variables.h"
#include "wifi_mqtt.h"
#include "pinControl.h"
#include "utils.h"
// 커피머신 세정
void orderCoffeeMachineCleaning() {
  Serial.println("커피머신 세정 시작");
  if (!systemStatus && currentProcess != NONE) {
    errorMessage = "이미 동작중입니다.";
    Serial.println("이미 동작중입니다");
    return;
  }
  systemStatus = false;
  currentProcess = COFFEE_CLEANING;

  getCoffeeMachineStatus();

  if (coffeeMachineStatus) {
    Serial.println("커피머신 대기 확인 세척시작");
    client.publish(middleServer1, "coffeeMachine/cleaning");
    getCoffeeMachineStatus();
    Serial.print("현재 확인된 커피머신 상태");
    Serial.println(coffeeMachineStatus);

    while (!coffeeMachineStatus) {
      client.loop();

      delay(100);
    }
    Serial.println("커피머신 세정 종료");
    systemStatus = true;
    currentProcess = NONE;

  } else {
    errorMessage = "커피머신이 대기상태가 아닙니다.";
    Serial.println("커피머신이 대기상태가 아닙니다.");
    systemStatus = true;
    currentProcess = NONE;
    coffeeMachineStatus = false;
    return;
  }
}


// 커피머신 하단부 세정
void orderCoffeeMachineLowerCleaning() {
  Serial.println("커피머신 하단부 세정 시작");
  if (!systemStatus && currentProcess != NONE) {
    errorMessage = "이미 동작중입니다";
    Serial.println("이미 동작중입니다");
    return;
  }
  Serial.println("커피 잔량 확인");
  if (cfLevel < limitLevelMin) {
    errorMessage = "커피가 남아있습니다";
    Serial.println("커피가 남아있습니다");
    return;
  }
  systemStatus = false;
  currentProcess = COFFEE_LOWER_CLEANING;

  controlPin(hash1, true);
  controlPin(hash6, true);

  getCoffeeMachineStatus();

  if (coffeeMachineStatus) {
    Serial.println("커피머신 대기 확인 하단부 세정 시작");

    client.publish(middleServer1, "coffeeMachine/cleaningLower");
    getCoffeeMachineStatus();
    Serial.print("현재 확인된 커피머신 상태");
    Serial.println(coffeeMachineStatus);

    while (!coffeeMachineStatus) {
      client.loop();

      delay(100);
    }
    TimerCheck(timer1);

    controlPin(hash12, false);
    controlPin(hash6, false);

    Serial.println("커피머신 하단부 세정 종료");
    systemStatus = true;
    currentProcess = NONE;
    coffeeMachineStatus = false;

  } else {
    errorMessage = "커피머신이 대기상태가 아닙니다.";
    Serial.println("커피머신이 대기상태가 아닙니다.");
    systemStatus = true;
    currentProcess = NONE;
    return;
  }
}

// 디카페인 사이클 세정
void orderCfCycleCleaning() {
  Serial.println("디카페인 사이클 세정 시작");

  if (!systemStatus && currentProcess != NONE) {
    errorMessage = "이미 동작중입니다.";
    Serial.println("이미 동작중입니다");
    return;
  }
  systemStatus = false;
  currentProcess = COFFEE_CYCLE_CLEANING;

  controlPin(hash2, true);
  controlPin(hash3, false);

  while (cfCleanCurrentCount < cfCleanCount) {
    cfCleanCurrentCount++;
    Serial.print("목표 세정횟수");
    Serial.println(cfCleanCount);
    Serial.print("현재 반복횟수");
    Serial.println(cfCleanCurrentCount);


    controlPin(hash13, true);

    while (cfLevel >= limitLevelMax) {
      Serial.print("현재 레벨 : ");
      Serial.println(cfLevel);
      Serial.print("목표 레벨 : ");
      Serial.println(limitLevelMax);
      client.loop();

      delay(100);
    }
    Serial.println("물 충전 완료");
    controlPin(hash13, false);

    controlPin(hash15, true);
    TimerCheck(cfCleanTime);
    controlPin(hash15, false);

    controlPin(hash6, true);
    while (cfLevel <= limitLevelMin) {
      Serial.print("현재 레벨 : ");
      Serial.println(cfLevel);
      Serial.print("목표 레벨 : ");
      Serial.println(limitLevelMin);
      client.loop();

      delay(100);
    }
    Serial.println("물 비움 완료");
    TimerCheck(10);
    controlPin(hash6, false);
  }
  controlPin(hash2, false);
  Serial.println("디카페인 사이클 세정 종료");
  systemStatus = true;
  currentProcess = NONE;
}
// 콜드브루 본체 세정
void orderColdBrewCleaning() {
  Serial.println("콜드브루 본체 세정 시작");

  if (!systemStatus && currentProcess != NONE) {
    errorMessage = "이미 동작중입니다.";
    Serial.println("이미 동작중입니다");
    return;
  }
  systemStatus = false;
  currentProcess = COLD_BREW_CLEANING;
  while (cbCleanCurrentCount < cbCleanCount) {
    cbCleanCurrentCount++;
    Serial.print("목표 세정횟수");
    Serial.println(cbCleanCount);
    Serial.print("현재 반복횟수");
    Serial.println(cbCleanCurrentCount);

    controlPin(hash7, true);
    controlPin(hash12, true);

    TimerCheck(cbCleanTime);

    controlPin(hash12, false);
    controlPin(hash7, false);
  }
  Serial.println("콜드브루 본체 세정 종료");
  systemStatus = true;
  currentProcess = NONE;
  cbCleanCurrentCount = 0;
};

// 콜드브루 라인1 세정
void orderColdBrewLineCleaningOne() {
  Serial.println("콜드브루 라인1 세정 시작");

  if (!systemStatus && currentProcess != NONE) {
    errorMessage = "이미 동작중입니다.";
    Serial.println("이미 동작중입니다");
    return;
  }
  systemStatus = false;
  currentProcess = COLD_BREW_LINE_CLEANING1;

  controlPin(hash2, true);
  controlPin(hash3, true);
  controlPin(hash9, true);
  controlPin(hash8, true);

  controlPin(hash13, true);

  controlPin(hash14, true);

  TimerCheck(cbCleanTime);

  controlPin(hash13, false);

  TimerCheck(5);

  controlPin(hash14, false);

  controlPin(hash2, false);
  controlPin(hash3, false);
  controlPin(hash9, false);
  controlPin(hash8, false);

  Serial.println("콜드브루 라인1 세정 종료");
  systemStatus = true;
  currentProcess = NONE;
}
// 콜드브루 라인2 세정
void orderColdBrewLineCleaningTwo() {
  Serial.println("콜드브루 라인2 세정 시작");

  if (!systemStatus && currentProcess != NONE) {
    errorMessage = "이미 동작중입니다.";
    Serial.println("이미 동작중입니다");
    return;
  }
  systemStatus = false;
  currentProcess = COLD_BREW_LINE_CLEANING2;

  controlPin(hash2, true);
  controlPin(hash3, true);
  controlPin(hash8, true);

  controlPin(hash13, true);

  controlPin(hash14, true);
  TimerCheck(10);

  controlPin(hash13, false);
  TimerCheck(5);

  controlPin(hash14, false);

  controlPin(hash2, false);
  controlPin(hash3, false);
  controlPin(hash8, false);

  Serial.println("콜드브루 라인2 세정 종료");
  systemStatus = true;
  currentProcess = NONE;
};

// 브루드커피 추출
void orderBrewedExtraction() {
  if (!systemStatus || currentProcess != NONE) {
    errorMessage = "이미 동작중입니다.";
    Serial.println("이미 동작중입니다");
    return;
  }
  Serial.println("브루드커피 추출 시작");

  systemStatus = false;
  currentProcess = BREWED_EXTRACTION;

  controlPin(hash2, true);
  controlPin(hash3, true);

  controlPin(hash10, true);

  InflowFlowMeterCheck();
  controlPin(hash10, false);

  controlPin(hash14, true);
  TimerCheck(3);

  heaterStatus = true;

  WaitColdbrewHeating();

  heaterStatus = false;
  TimerCheck(3);

  controlPin(hash14, false);


  controlPin(hash9, true);

  controlPin(hash14, true);
  TimerCheck(3);
  heaterStatus = true;

  CirculatingFlowMeterCheck();

  heaterStatus = false;
  TimerCheck(5);
  controlPin(hash14, false);

  controlPin(hash9, false);

  Serial.println("브루드커피 추출 종료");
  systemStatus = true;
  orderBrewedCooling();
}

// 브루드커피 냉각
void orderBrewedCooling() {
  if (currentProcess != BREWED_EXTRACTION && currentProcess != BREWED_COOLING) {
    errorMessage = "추출된 브루드커피가 없습니다.";
    Serial.println("추출된 브루드커피가 없습니다.");
    return;
  }
  if (systemStatus == false) {
    errorMessage = "이미 동작중입니다.";
    Serial.println("이미 동작중입니다.");
    return;
  }

  Serial.println("브루드커피 냉각 시작");

  systemStatus = false;
  currentProcess = BREWED_COOLING;
  
  

  controlPin(hash14, true);
  TimerCheck(3);

  heaterStatus = true;

  WaitColdbrewCooling();

  // 알림신호 10초 발신

  // (300)초간 대기
  unsigned long startMillis = millis();
  while (millis() - startMillis < 300 * 1000 && !transferInterrupt) {
    setMqtt();
    setWifi();
    client.loop();
    CoolingControl(tmpCBInput, tmpSetCBP);
    delay(100);  // 100ms 동안 대기
  }
  if (transferInterrupt) {
    // 이송버튼이 눌른후에 이송이 종료됨
    transferInterrupt = false;
    Serial.println("브루드커피 추출/냉각/이송 종료");
  } else {
    // (300)초간 아무런 버튼이 눌리지않음
    heaterStatus = false;
    TimerCheck(3);
    controlPin(hash14, false);
    
    
    Serial.println("브루드커피 냉각 종료");
    systemStatus = true;
  }
};

// 브루드커피 이송
void orderBrewedTransfer() {
  if (currentProcess != BREWED_COOLING) {
    errorMessage = "추출된 브루드커피가 없습니다.";
    Serial.println("추출된 브루드커피가 없습니다.");
    return;
  }
  Serial.println("브루드커피 이송 시작");
  transferInterrupt = true;
  currentProcess = COLD_BREW_TRANSFER;

  heaterStatus = false;
  TimerCheck(3);
  controlPin(hash14, false);

  controlPin(hash11, true);

  controlPin(hash14, true);
  TimerCheck(3);

  heaterStatus = true;

  while (coldbrewLevel == 0) {
    setMqtt();
    setWifi();
    client.loop();
    delay(100);
  }
  Serial.println("브루드커피 이송 완료");
  heaterStatus = false;
  TimerCheck(3);
  controlPin(hash14, false);
  controlPin(hash11, false);
  Serial.println("브루드커피 냉각 종료");
  
  
  Serial.println("브루드커피 이송 종료");
  systemStatus = true;
  currentProcess = NONE;
};



// 콜드브루 추출
void orderColdBrewExtraction() {
  if (!systemStatus || currentProcess != NONE) {
    errorMessage = "이미 동작중입니다.";
    Serial.println("이미 동작중입니다");
    return;
  }
  Serial.println("콜드브루 추출 시작");
  systemStatus = false;
  currentProcess = COLD_BREW_EXTRACTION;

  
  

  controlPin(hash2, true);
  controlPin(hash3, true);

  controlPin(hash10, true);

  InflowFlowMeterCheck();
  controlPin(hash10, false);

  controlPin(hash14, true);
  TimerCheck(3);

  heaterStatus = true;

  WaitColdbrewCooling();

  heaterStatus = false;

  TimerCheck(3);
  controlPin(hash14, false);

  controlPin(hash9, true);

  controlPin(hash14, true);
  TimerCheck(3);

  heaterStatus = true;

  CirculatingFlowMeterCheck();

  heaterStatus = false;
  TimerCheck(3);
  controlPin(hash14, false);
  controlPin(hash9, false);

  // 
  Serial.println("콜드브루 추출 종료");
  systemStatus = true;
  orderColdBrewCooling();
};

// 콜드브루 냉각
void orderColdBrewCooling() {
  if (currentProcess != COLD_BREW_EXTRACTION && currentProcess != COLD_BREW_COOLING) {
    errorMessage = "추출된 콜드브루가 없습니다.";
    Serial.println("추출된 콜드브루가 없습니다.");
    return;
  }
  if (systemStatus == false) {
    Serial.println("이미 동작중입니다.");
    return;
  }

  Serial.println("콜드브루 냉각 시작");

  systemStatus = false;
  currentProcess = COLD_BREW_COOLING;
  // 
  // 

  controlPin(hash14, true);
  TimerCheck(3);

  heaterStatus = true;

  WaitColdbrewCooling();

  // 알림신호 10초 발신

  // (300)초간 대기
  unsigned long startMillis = millis();
  while (millis() - startMillis < 300 * 1000 && !transferInterrupt) {
    setMqtt();
    setWifi();
    CoolingControl(tmpCBInput, tmpSetCBP);
    delay(100);  // 100ms 동안 대기
  }
  if (transferInterrupt) {
    // 이송버튼이 눌른후에 이송이 종료됨
    transferInterrupt = false;
    Serial.println("콜드브루 추출/냉각/이송 종료");
  } else {
    // (300)초간 아무런 버튼이 눌리지않음
    heaterStatus = false;
    TimerCheck(3);
    controlPin(hash14, false);
    
    
    Serial.println("콜드브루 냉각 종료");
    systemStatus = true;
  }
};

// 콜드브루 이송
void orderColdBrewTransfer() {
  if (currentProcess != COLD_BREW_COOLING) {
    errorMessage = "추출된 콜드브루가 없습니다.";
    Serial.println("추출된 콜드브루가 없습니다.");
    return;
  }
  Serial.println("콜드브루 이송 시작");
  transferInterrupt = true;

  currentProcess = COLD_BREW_TRANSFER;


  heaterStatus = false;
  TimerCheck(3);
  controlPin(hash14, false);

  controlPin(hash11, true);

  controlPin(hash14, true);
  TimerCheck(3);

  heaterStatus = true;

  while (coldbrewLevel == 0) {
    Serial.println("콜드브루 레벨 체크중..");
    Serial.println(coldbrewLevel);
    client.loop();
    delay(100);
  }
  heaterStatus = false;
  TimerCheck(3);
  controlPin(hash14, false);
  controlPin(hash11, false);
  Serial.println("콜드브루 냉각 종료");
  
  

  Serial.println("콜드브루 이송 종료");
  transferInterrupt = false;
  systemStatus = true;
  currentProcess = NONE;
};

// 디카페인 추출
void orderCfExtraction() {
  if (!systemStatus || currentProcess != NONE) {
    errorMessage = "이미 동작중입니다.";
    Serial.println("이미 동작중입니다");
    return;
  }
  Serial.println("디카페인 추출 시작");
  systemStatus = false;
  currentProcess = COFFEE_EXTRACTION;
  // 콜드브루 #13, #14 3way밸브 잠금
  controlPin(hash2, false);
  controlPin(hash3, false);

  controlPin(hash1, true);

  
  
  Serial.println(cfLevel);
  Serial.println(limitLevel);
  while (cfLevel >= limitLevel) {
    Serial.println(cfLevel);
    Serial.println(limitLevel);
    getCoffeeMachineStatus();
    if (coffeeMachineStatus) {
      coffeeMachineStatus = false;
      Serial.println("디카페인 에스프레소 추출");
      client.publish(middleServer1, "coffeeMachine/cf/1", false, 2);
      TimerCheck(1);
    } else {
      Serial.println("디카페인 에스프레소 추출중");
      TimerCheck(1);
    }
  }
  Serial.println("디카페인 1차 추출 완료");
  controlPin(hash15, true);
  Serial.println(cfLevel);
  Serial.println(limitLevelMax);
  while (cfLevel >= limitLevelMax) {
    Serial.println(cfLevel);
    Serial.println(limitLevelMax);
    getCoffeeMachineStatus();
    if (coffeeMachineStatus) {
      coffeeMachineStatus = false;
      Serial.println("디카페인 에스프레소 추출");
      client.publish(middleServer1, "coffeeMachine/cf/1", false, 2);
      TimerCheck(1);
    } else {
      Serial.println("디카페인 에스프레소 추출중");
      TimerCheck(1);
    }
  }
  
  Serial.println("디카페인 최대 추출 완료");
  controlPin(hash1, false);

  
  

  Serial.println("디카페인 추출 종료");
  systemStatus = true;

  // 
  // 
  orderCfCooling();
};

// 디카페인 냉각
void orderCfCooling() {
  if (currentProcess != COFFEE_EXTRACTION && currentProcess != COFFEE_COOLING) {
    errorMessage = "추출된 디카페인이 없습니다.";
    Serial.println("추출된 디카페인이 없습니다.");
    return;
  }
  if (systemStatus == false) {
    Serial.println("이미 동작중입니다.");
    return;
  }

  Serial.println("디카페인 냉각 시작");
  systemStatus = false;
  currentProcess = COFFEE_COOLING;

  WaitCfCooling();

  // 알림신호 10초 발신

  unsigned long startMillis = millis();
  while (millis() - startMillis < 300 * 1000 && !transferInterrupt) {
    setMqtt();
    setWifi();
    CoolingControl(tmpCfInput, tmpSetCfP);
    delay(100);  // 100ms 동안 대기
  }
  if (transferInterrupt) {
    // 이송버튼이 눌른후에 이송이 종료됨
    transferInterrupt = false;
    Serial.println("디카페인 커피 추출/냉각/이송 종료");
  } else {
    // (300)초간 아무런 버튼이 눌리지않음
    controlPin(hash15, false);
    
    
    Serial.println("디카페인 냉각 종료");
    systemStatus = true;
  }
};
// 디카페인 이송
void orderCfTransfer() {
  if (currentProcess != COFFEE_COOLING) {
    errorMessage = "추출된 디카페인이 없습니다.";
    Serial.println("추출된 디카페인이 없습니다.");
    return;
  }
  Serial.println("디카페인 이송 시작");
  transferInterrupt = true;
  currentProcess = COFFEE_TRANSFER;

  controlPin(hash15, false);
  controlPin(hash4, true);
  controlPin(hash15, true);

  while (cfLevel <= limitLevelMin) {
    setMqtt();
    setWifi();
    client.loop();
    delay(100);  // 100ms 동안 대기
  }
  Serial.println("디카페인 이송 확인");
  ;
  controlPin(hash4, false);

  controlPin(hash15, false);

  
  

  Serial.println("디카페인 이송 종료");
  systemStatus = true;
  currentProcess = NONE;
};


// 디카페인 냉장고 보틀에서 이동
void orderBottleTransfer() {
  if (currentProcess != BOTTLE_TRANSFER) {
    if (!systemStatus && currentProcess != NONE) {
      errorMessage = "이미 동작중입니다.";
      Serial.println("이미 동작중입니다");
      return;
    }
    Serial.println("디카페인 보틀에서 이송 시작");

    systemStatus = false;
    currentProcess = BOTTLE_TRANSFER;

    controlPin(hash15, false);
    controlPin(hash5, true);
    controlPin(hash4, true);
    controlPin(hash15, true);
  } else {

    controlPin(hash15, false);
    controlPin(hash4, false);
    controlPin(hash5, false);

    systemStatus = true;
    currentProcess = NONE;

    Serial.println("디카페인 냉장고에서 이송 종료");
  }
};