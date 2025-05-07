#include "variables.h"
#include "weightCheck.h"
#include "wifi_mqtt.h"
#include "HX711.h"
void setup() {
  Serial.begin(115200);  // 시리얼 통신 초기화
  setWifi();             // Wi-Fi 설정
  setMqtt();             // MQTT 설정

  delay(1000);
  setZeroFactor(5);  // 영점 잡기
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setWifi();
  }
  if (!client.connected()) {
    setMqtt();
  }
  client.loop();




  // HX711 준비 대기(권장)
  while (!scale.is_ready()) {
    delay(1);
  }
  int newDigitalValue = scale.read();  // 현재 값 읽기
  // 이동 평균 계산
  sumOfValues -= averageValue[currentIndex];        // 이전 값 빼기
  averageValue[currentIndex] = newDigitalValue;     // 새로운 값 넣기
  sumOfValues += newDigitalValue;                   // 새로운 합 계산
  currentIndex = (currentIndex + 1) % averageSize;  // 인덱스 업데이트 (순환)

  int digitalValue = sumOfValues / averageSize;  // 이동 평균 값

  checkCalibration(digitalValue);                // 캘리브레이션 값 조정
  calculate(digitalValue);                       // 무게 계산 및 MQTT로 전송
  Serial.println(digitalValue);                  // 무게 디지털값
  Serial.println(weight);

  // 영점 자동잡기
  // 로드셀 무게가 5g 이하일때 이전값과 현재값이 0.1g이하 차이라면 20번 반복시 영점잡기
  // => 영점을 잡을때도 시간이걸림
  // => 이 영점 측정시간(약 0.3~0.5초)동안 무게 감지시(컵이 올라온다거나 하는상황)에서 영점 에러 발생
  // => 따라서 자동 영점잡기 기능은 빼야할 것으로 판단됨
  if (weight <= 5 && fabs(weight - previous_weight) <= 0.1) {
    calibration_count++;  // 조건 만족 시 카운트 증가
    if (calibration_count >= 20) {
      Serial.println("조건 만족 - 영점 재설정");
      setZeroFactor(4);       // 영점 재설정
      calibration_count = 0;  // 카운트 초기화
    }
  } else {
    calibration_count = 0;  // 조건 불만족 시 카운트 초기화
  }
  previous_weight = weight;  // 이전 무게 값 업데이트
  sendWeightMQTT(weight);
}
