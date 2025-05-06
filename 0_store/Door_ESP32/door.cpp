// door.cpp
#include "wifi_mqtt.h"
#include "variables.h"
#include "max98357.h"

void setOpenTime() {
  Serial.println("getDoorTimeConfig");
  mqttClient.publish(serverTopic, "getDoorTimeConfig");
}

void OpenDoor() {
  Serial.println("Entering door opening wait state...");
  doorWaitingForOpen = true;     // 개방 대기 상태로 전환
  doorWaitStartTime = millis();  // 개방 대기 시작 시간 기록
  doorIsOpen = false;
  doorIsClosing = false;
}

void closeDoor() {
  Serial.println("Door is closing...");
  digitalWrite(DOOR_PIN, LOW);  // 문 닫힘 (DOOR_PIN OFF)
  doorIsOpen = false;
  doorIsClosing = true;
  doorClosingStartTime = millis();  // 문이 닫히기 시작한 시간 기록
}

void checkSensors() {

  // 센서 상태 읽기
  int entrySensorState = !digitalRead(ENTRY_SENSOR_PIN);
  int exitSensorState = !digitalRead(EXIT_SENSOR_PIN);
  // Serial.print("센서감지 / ");
  // Serial.print("입장 감지 : ");
  // Serial.print(entrySensorState);
  // Serial.print(" / 퇴장 감지 : ");
  // Serial.println(exitSensorState);
  unsigned long currentTime = millis();

  if (doorWaitingForOpen) {
    // 개방 대기 상태에서 센서 감지 시 문 열기
    if (entrySensorState == HIGH || exitSensorState == HIGH) {

      
      Serial.println("대기 중 센서가 감지되었습니다. 문 개방.");
      digitalWrite(DOOR_PIN, HIGH);  // 문 개방
      doorOpenTime = currentTime;
      doorIsOpen = true;
      doorWaitingForOpen = false;  // 대기 상태 해제
    } else if (currentTime - doorWaitStartTime >= waitForOpenTime * 1000) {
      // 개방 대기 시간 초과 시 대기 상태 해제
      Serial.println("개방 대기 종료");
      doorWaitingForOpen = false;
    }
  } else if (doorIsOpen) {
    // 문이 열려 있는 동안 센서 감지 시 문 열림 시간 연장
    if (entrySensorState == HIGH || exitSensorState == HIGH) {
      doorOpenTime = currentTime;  // 문 열림 시간 초기화 (연장)
      Serial.println("문이 열려 있는 동안 센서가 감지되었습니다. 개방 시간 연장.");
    }
    // 문 열림 시간 경과 시 문 닫기
    if (currentTime - doorOpenTime >= openTime * 1000) {
      closeDoor();
    }
  } else if (doorIsClosing) {
    // 문이 닫히는 중에 센서 감지 시 문 다시 열기
    if (entrySensorState == HIGH || exitSensorState == HIGH) {
      Serial.println("도어가 닫히는 동안 센서가 감지되었습니다.문을 다시 여는 중입니다.");
      OpenDoor();                   // 개방 대기 상태로 돌아감
      digitalWrite(DOOR_PIN, LOW);  // 닫힘 중지
      doorIsClosing = false;
    } else {
      // 문 닫힘 완료 시간 계산
      if (currentTime - doorClosingStartTime >= closingTime) {
        doorIsClosing = false;  // 문 닫힘 완료
        Serial.println("출입문이 완전히 닫혔습니다.");
        audioPlay = false;
      }
    }
  } else {
    // 문이 닫혀 있는 상태에서 퇴장 센서 감지 시 문 열기
    if (exitSensorState == HIGH) {
      Serial.println("출구 센서 감지, 문이 열립니다.");
      digitalWrite(DOOR_PIN, HIGH);  // 문 개방
      doorOpenTime = currentTime;
      doorIsOpen = true;
    }
  }
}

void checkEmergencyButton() {
  if (digitalRead(Emergency_BUTTON_PIN) == LOW) {
    Serial.println("문의 비상 호출버튼이 눌림");
    mqttClient.publish(serverTopic, String("DoorButtonPress/") + branchCode);
  }
}
