// switch.cpp
#include "switch.h"
#include "variables.h"
#include "wifi_mqtt.h"
#include "pinControl.h"
#include "webPage.h"
#include "utils.h"
// 커피머신 세정
void orderCoffeeCleaning() {
  Serial.println("커피머신 세정 시작");
  if (!systemStatus && currentProcess != NONE) {
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
      server.handleClient();
      delay(100);
    }
    Serial.println("커피머신 세정 종료");
    systemStatus = true;
    currentProcess = NONE;

  } else {
    Serial.println("커피머신이 대기상태가 아닙니다.");
    systemStatus = true;
    currentProcess = NONE;
    return;
  }
}


// 커피머신 하단부 세정
void orderCoffeeLowerCleaning() {
  Serial.println("커피머신 하단부 세정 시작");
  if (!systemStatus && currentProcess != NONE) {
    Serial.println("이미 동작중입니다");
    return;
  }
  Serial.println("커피 잔량 확인");
  if (decafLevel < limitLevelMin) {
    Serial.println("커피가 남아있습니다");
    return;
  }
  systemStatus = false;
  currentProcess = COFFEE_LOWER_CLEANING;

  controlPin(hash12, true);
  controlPin(hash21, true);

  getCoffeeMachineStatus();

  if (coffeeMachineStatus) {
    Serial.println("커피머신 대기 확인 하단부 세정 시작");

    client.publish(middleServer1, "coffeeMachine/cleaningLower");
    getCoffeeMachineStatus();
    Serial.print("현재 확인된 커피머신 상태");
    Serial.println(coffeeMachineStatus);

    while (!coffeeMachineStatus) {
      client.loop();
      server.handleClient();
      delay(100);
    }
    TimerCheck(10);

    controlPin(hash12, false);
    controlPin(hash21, false);

    Serial.println("커피머신 하단부 세정 종료");
    systemStatus = true;
    currentProcess = NONE;

  } else {
    Serial.println("커피머신이 대기상태가 아닙니다.");
    systemStatus = true;
    currentProcess = NONE;
    return;
  }
}

// 디카페인 사이클 세정
void orderDecafCycleCleaning() {
  Serial.println("디카페인 사이클 세정 시작");

  if (!systemStatus && currentProcess != NONE) {
    Serial.println("이미 동작중입니다");
    return;
  }
  systemStatus = false;
  currentProcess = DECAF_CYCLE_CLEANING;

  controlPin(hash13, true);
  controlPin(hash14, false);

  TimerCheck(1);

  while (decafCleanCurrentCount < decafCleanCount) {
    decafCleanCurrentCount++;
    Serial.print("목표 세정횟수");
    Serial.println(decafCleanCount);
    Serial.print("현재 반복횟수");
    Serial.println(decafCleanCurrentCount);


    controlPin(hash22, true);

    while (decafLevel >= limitLevelMax) {
      Serial.print("현재 레벨 : ");
      Serial.println(decafLevel);
      Serial.print("목표 레벨 : ");
      Serial.println(limitLevelMax);
      client.loop();
      server.handleClient();
      delay(100);
    }
    Serial.println("물 충전 완료");
    controlPin(hash22, false);

    controlPin(hash15, true);
    // TimerCheck(decafCleanTime);
    TimerCheck(2);  // 테스트용
    controlPin(hash15, false);

    TimerCheck(1);

    controlPin(hash21, true);
    while (decafLevel <= limitLevelMin) {
      Serial.print("현재 레벨 : ");
      Serial.println(decafLevel);
      Serial.print("목표 레벨 : ");
      Serial.println(limitLevelMin);
      client.loop();
      server.handleClient();
      delay(100);
    }
    Serial.println("물 비움 완료");
    TimerCheck(10);
    controlPin(hash21, false);
  }
  Serial.println("디카페인 사이클 세정 종료");
  systemStatus = true;
  currentProcess = NONE;
}
// 콜드브루 본체 세정
void orderColdBrewCleaning() {
  Serial.println("콜드브루 본체 세정 시작");

  if (!systemStatus && currentProcess != NONE) {
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

    controlPin(hash3, true);

    TimerCheck(1);

    controlPin(hash6, true);

    // TimerCheck(cbCleanTime); 테스트용으로 주석처리
    TimerCheck(2);


    controlPin(hash6, false);

    TimerCheck(1);

    controlPin(hash3, false);
    TimerCheck(1);
  }
  Serial.println("콜드브루 본체 세정 종료");
  systemStatus = true;
  currentProcess = NONE;
};
// 콜드브루 라인1 세정
void orderColdBrewLineCleaningOne() {
  Serial.println("콜드브루 라인1 세정 시작");

  if (!systemStatus && currentProcess != NONE) {
    Serial.println("이미 동작중입니다");
    return;
  }
  systemStatus = false;
  currentProcess = COLD_BREW_LINE_CLEANING1;

  controlPin(hash13, true);
  controlPin(hash14, true);
  controlPin(hash5, true);
  controlPin(hash26, true);

  TimerCheck(1);

  controlPin(hash22, true);
  TimerCheck(1);

  controlPin(hash11, true);
  TimerCheck(1);

  // TimerCheck(cbCleanTime); 테스트용 주석처리
  TimerCheck(1);

  controlPin(hash22, false);

  TimerCheck(5);

  controlPin(hash11, false);
  TimerCheck(1);

  controlPin(hash13, false);
  controlPin(hash14, false);
  controlPin(hash5, false);
  controlPin(hash26, false);

  Serial.println("콜드브루 라인1 세정 종료");
  systemStatus = true;
  currentProcess = NONE;
}
// 콜드브루 라인2 세정
void orderColdBrewLineCleaningTwo() {
  Serial.println("콜드브루 라인2 세정 시작");

  if (!systemStatus && currentProcess != NONE) {
    Serial.println("이미 동작중입니다");
    return;
  }
  systemStatus = false;
  currentProcess = COLD_BREW_LINE_CLEANING2;

  controlPin(hash13, true);
  controlPin(hash14, true);
  controlPin(hash26, true);

  TimerCheck(1);

  controlPin(hash22, true);
  TimerCheck(1);

  controlPin(hash11, true);
  TimerCheck(10);

  controlPin(hash22, false);
  TimerCheck(5);

  controlPin(hash11, false);
  TimerCheck(1);

  controlPin(hash13, false);
  controlPin(hash14, false);
  controlPin(hash26, false);

  Serial.println("콜드브루 라인2 세정 종료");
  systemStatus = true;
  currentProcess = NONE;
};

// 브루드커피 추출
void orderBrewedExtraction() {
  if (!systemStatus && currentProcess != NONE) {
    Serial.println("이미 동작중입니다");
    return;
  }
  Serial.println("브루드커피 추출 시작");

  systemStatus = false;
  currentProcess = BREWED_EXTRACTION;

  controlPin(hash13, true);
  controlPin(hash14, true);

  TimerCheck(1);

  controlPin(hash20, true);

  InflowFlowMeterCheck();
  controlPin(hash20, false);
  TimerCheck(1);

  controlPin(hash11, true);
  TimerCheck(1);

  controlPin(hash9, true);

  WaitColdbrewHeating();

  controlPin(hash9, false);

  controlPin(hash11, false);

  TimerCheck(1);

  controlPin(hash5, true);

  controlPin(hash11, true);
  TimerCheck(1);

  controlPin(hash9, true);

  CirculatingFlowMeterCheck();

  controlPin(hash9, false);
  TimerCheck(5);
  controlPin(hash11, false);
  TimerCheck(1);

  controlPin(hash5, false);

  Serial.println("브루드커피 추출 종료");
  systemStatus = true;
  orderBrewedCooling();
}

// 브루드커피 냉각
void orderBrewedCooling() {
  if (currentProcess != BREWED_EXTRACTION && currentProcess != COLD_BREW_COOLING) {
    Serial.println("추출된 브루드커피가 없습니다.");
    return;
  }
  if (systemStatus == false) {
    Serial.println("이미 동작중입니다.");
    return;
  }

  Serial.println("브루드커피 냉각 시작");

  systemStatus = false;
  currentProcess = BREWED_COOLING;
  CoolingControl(true);
  coolingStatus = true;

  controlPin(hash11, true);
  TimerCheck(1);

  controlPin(hash9, true);

  WaitColdbrewCooling();

  // 알림신호 10초 발신

  // (timer1)초간 대기
  unsigned long startMillis = millis();
  while (millis() - startMillis < timer1 * 1000 && !buttonInterrupt) {
    setMqtt();
    setWifi();
    client.loop();
    server.handleClient();
    delay(100);  // 100ms 동안 대기
  }

  if (buttonInterrupt) {
    // 이송버튼이 눌른후에 이송이 종료됨
    buttonInterrupt = false;
  } else {
    // (timer1)초간 아무런 버튼이 눌리지않음
    controlPin(hash9, false);
    CoolingControl(false);
    coolingStatus = false;
    Serial.println("브루드커피 냉각 종료");
  }
};

// 브루드커피 이송
void orderBrewedTransfer() {
  if (currentProcess != BREWED_COOLING) {
    Serial.println("추출된 브루드커피가 없습니다.");
    return;
  }
  Serial.println("브루드커피 이송 시작");
  buttonInterrupt = true;

  currentProcess = COLD_BREW_TRANSFER;
  controlPin(hash9, false);
  controlPin(hash11, false);
  TimerCheck(1);

  controlPin(hash8, true);

  controlPin(hash11, true);
  TimerCheck(1);

  controlPin(hash9, true);

  while (coldbrewLevel == 0) {
    client.loop();
    server.handleClient();
    delay(100);
  }
  controlPin(hash9, false);
  controlPin(hash11, false);
  TimerCheck(1);
  controlPin(hash8, false);
  Serial.println("브루드커피 냉각 종료");
  CoolingControl(false);
  coolingStatus = false;

  Serial.println("브루드커피 이송 종료");
  systemStatus = true;
  currentProcess = NONE;
};



// 콜드브루 추출
void orderColdBrewExtraction() {
  if (!systemStatus && currentProcess != NONE) {
    Serial.println("이미 동작중입니다");
    return;
  }
  Serial.println("콜드브루 추출 시작");
  systemStatus = false;
  currentProcess = COLD_BREW_EXTRACTION;

  CoolingControl(true);
  coolingStatus = true;

  controlPin(hash13, true);
  controlPin(hash14, true);

  TimerCheck(1);

  controlPin(hash20, true);

  InflowFlowMeterCheck();
  controlPin(hash20, false);
  TimerCheck(1);

  controlPin(hash11, true);
  TimerCheck(1);

  controlPin(hash9, true);

  WaitColdbrewCooling();

  controlPin(hash9, false);

  controlPin(hash11, false);
  TimerCheck(1);

  controlPin(hash5, true);

  controlPin(hash11, true);
  TimerCheck(1);

  controlPin(hash9, true);

  CirculatingFlowMeterCheck();

  controlPin(hash9, false);
  TimerCheck(5);
  controlPin(hash11, false);
  TimerCheck(1);

  controlPin(hash5, false);

  // CoolingControl(false));
  // coolingStatus = false;
  Serial.println("콜드브루 추출 종료");
  systemStatus = true;
  orderColdBrewCooling();
};

// 콜드브루 냉각
void orderColdBrewCooling() {
  if (currentProcess != COLD_BREW_EXTRACTION && currentProcess != COLD_BREW_COOLING) {
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
  // CoolingControl(true);
  // coolingStatus = true;

  controlPin(hash11, true);
  TimerCheck(1);

  controlPin(hash9, true);

  WaitColdbrewCooling();

  // 알림신호 10초 발신

  // (timer1)초간 대기
  unsigned long startMillis = millis();
  while (millis() - startMillis < timer1 * 1000 && !buttonInterrupt) {
    setMqtt();
    setWifi();
    client.loop();
    server.handleClient();
    delay(100);  // 100ms 동안 대기
  }

  if (buttonInterrupt) {
    // 이송버튼이 눌른후에 이송이 종료됨
    buttonInterrupt = false;
  } else {
    // (timer1)초간 아무런 버튼이 눌리지않음
    controlPin(hash9, false);
    CoolingControl(false);
    coolingStatus = false;
    Serial.println("콜드브루 냉각 종료");
  }
};

// 콜드브루 이송
void orderColdBrewTransfer() {
  if (currentProcess != COLD_BREW_COOLING) {
    Serial.println("추출된 콜드브루가 없습니다.");
    return;
  }
  Serial.println("콜드브루 이송 시작");
  buttonInterrupt = true;

  currentProcess = COLD_BREW_TRANSFER;

  controlPin(hash9, false);

  controlPin(hash11, false);
  TimerCheck(1);


  controlPin(hash8, true);

  controlPin(hash11, true);
  TimerCheck(1);

  controlPin(hash9, true);

  while (coldbrewLevel == 0) {
    Serial.println(coldbrewLevel);
    client.loop();
    server.handleClient();
    delay(100);
  }
  controlPin(hash9, false);
  controlPin(hash11, false);
  TimerCheck(1);
  controlPin(hash8, false);
  Serial.println("콜드브루 냉각 종료");
  CoolingControl(false);
  coolingStatus = false;

  Serial.println("콜드브루 이송 종료");
  systemStatus = true;
  currentProcess = NONE;
};


// 디카페인 추출
void orderDecafExtraction() {
  if (!systemStatus && currentProcess != NONE) {
    Serial.println("이미 동작중입니다");
    return;
  }
  Serial.println("디카페인 추출 시작");
  systemStatus = false;
  currentProcess = DECAF_EXTRACTION;

  controlPin(hash12, true);

  CoolingControl(true);
  coolingStatus = true;

  while (decafLevel >= limitLevel) {
    getCoffeeMachineStatus();
    if (coffeeMachineStatus) {
      Serial.println("디카페인 에스프레소 추출");
      client.publish(middleServer1, "coffeeMachine/decaf/1", false, 2);
      TimerCheck(1);
    } else {
      Serial.println("디카페인 에스프레소 추출중");
      TimerCheck(1);
    }
  }
  Serial.println("디카페인 1차 추출 완료");
  controlPin(hash15, true);

  while (decafLevel >= limitLevelMax) {
    getCoffeeMachineStatus();
    if (coffeeMachineStatus) {
      Serial.println("디카페인 에스프레소 추출");
      client.publish(middleServer1, "coffeeMachine/decaf/1", false, 2);
      TimerCheck(1);
    } else {
      Serial.println("디카페인 에스프레소 추출중");
      TimerCheck(1);
    }
  }
  controlPin(hash12, false);

  CoolingControl(true);
  coolingStatus = true;

  Serial.println("디카페인 추출 종료");
  systemStatus = true;

  // CoolingControl(false);
  // coolingStatus = false;
  orderDecafCooling();
};

// 디카페인 냉각
void orderDecafCooling() {
  if (currentProcess != DECAF_EXTRACTION && currentProcess != DECAF_COOLING) {
    Serial.println("추출된 디카페인이 없습니다.");
    return;
  }
  if (systemStatus == false) {
    Serial.println("이미 동작중입니다.");
    return;
  }

  Serial.println("디카페인 냉각 시작");

  systemStatus = false;
  currentProcess = DECAF_COOLING;
  // CoolingControl(true);
  // coolingStatus = true;

  WaitDecafCooling();

  // 알림신호 10초 발신

  // (timer1)초간 대기
  unsigned long startMillis = millis();
  while (millis() - startMillis < timer1 * 1000 && !buttonInterrupt) {
    setMqtt();
    setWifi();
    client.loop();
    server.handleClient();
    delay(100);  // 100ms 동안 대기
  }

  if (buttonInterrupt) {
    // 이송버튼이 눌른후에 이송이 종료됨
    buttonInterrupt = false;
  } else {
    // (timer1)초간 아무런 버튼이 눌리지않음
    controlPin(hash15, false);
    TimerCheck(1);
    CoolingControl(false);
    coolingStatus = false;
    systemStatus = true;
    Serial.println("디카페인 냉각 종료");
  }
};
// 디카페인 이송
void orderDecafTransfer() {
  if (currentProcess != DECAF_COOLING) {
    Serial.println("추출된 디카페인이 없습니다.");
    return;
  }
  Serial.println("디카페인 이송 시작");
  buttonInterrupt = true;
  currentProcess = DECAF_TRANSFER;



  controlPin(hash15, false);
  TimerCheck(1);

  controlPin(hash16, true);
  TimerCheck(1);

  controlPin(hash15, true);
  TimerCheck(1);

  while (decafLevel >= limitLevelMin) {
    setMqtt();
    setWifi();
    client.loop();
    server.handleClient();
    delay(100);  // 100ms 동안 대기
  }

  controlPin(hash16, true);
  TimerCheck(1);

  controlPin(hash15, false);
  TimerCheck(1);

  CoolingControl(false);
  coolingStatus = false;

  TimerCheck(1);
  Serial.println("디카페인 이송 종료");
  systemStatus = true;
  currentProcess = NONE;
};
// 디카페인 냉장고에서 이동
void orderDecafTransferFromFridge() {
  if (currentProcess != DECAF_TRANSFER_FROM_FRIDGE) {
    if (!systemStatus && currentProcess != NONE) {
      Serial.println("이미 동작중입니다");
      return;
    }
    Serial.println("디카페인 냉장고에서 이송 시작");

    systemStatus = false;
    currentProcess = DECAF_TRANSFER_FROM_FRIDGE;

    controlPin(hash15, false);
    TimerCheck(1);
    controlPin(hash24, true);
    controlPin(hash16, true);
    TimerCheck(1);
    controlPin(hash15, true);
    TimerCheck(1);
  } else {

    controlPin(hash15, false);
    TimerCheck(1);
    controlPin(hash16, false);
    controlPin(hash24, false);

    systemStatus = true;
    currentProcess = NONE;

    Serial.println("디카페인 냉장고에서 이송 종료");
  }
};