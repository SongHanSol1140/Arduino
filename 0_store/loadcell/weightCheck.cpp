#include "weightCheck.h"

// 영점 잡기
void setZeroFactor(int repeatNumber) {
  // Serial.println("영점잡기");
  zeroFactor = scale.read_average(repeatNumber);
  tolerance = zeroFactor * 0.001;
}



// 무게 계산 및 MQTT로 전송
void calculate(int digitalValue) {
  // weight = (digitalValue - zeroFactor) / calibration_factor; // 원본무게
  // weight = round((digitalValue - zeroFactor) / calibration_factor * 5) / 5.0; // 0.2단위 계산
  weight = round((digitalValue - zeroFactor) / calibration_factor * 100) / 100.0;  // 0.1단위 계산
  // if (digitalValue > zeroFactor + (tolerance)) {
  if (weight > 2) {  // 2g보다 클경우
    sendWeightMQTT(weight);
  } else {
    sendWeightMQTT(0);
  }
}

// 캘리브레이션 값 조정 => 캘리브레이션 팩터 => 1g당
// 더 단순 나열식, 사용시에는 함수 최적화를 통해 로직시간을 줄일것 => ex : 400000 이상 / 이하로 나누고 분산시키기
// 현재는 큰 무게부터 작은무게 순으로 내려가지만 실사용시 반대로 작은 무게에서 큰무게순으로 가는게 좋을수도 있음
void checkCalibration(int weightValue) {
  if (useManual == true) {
    return;
  }
  if (weightValue > 800000) {
    calibration_factor = 1062.0;
  } else if (weightValue > 700000) {
    calibration_factor = 1062.5;
  } else if (weightValue > 600000) {
    calibration_factor = 1065.0;
  } else if (weightValue > 500000) {
    calibration_factor = 1065.5;
  } else if (weightValue > 450000) {
    calibration_factor = 1065.5;
  } else if (weightValue > 400000) {
    calibration_factor = 1065.5;
  } else if (weightValue > 300000) {
    calibration_factor = 1065.8;
  } else if (weightValue > 200000) {
    calibration_factor = 1065.7;
  } else if (weightValue > 190000) {
    calibration_factor = 1065.6;
  } else if (weightValue > 180000) {
    calibration_factor = 1065.7;
  } else if (weightValue > 170000) {
    calibration_factor = 1065.8;
  } else if (weightValue > 160000) {
    calibration_factor = 1065.9;
  } else if (weightValue > 150000) {
    calibration_factor = 1066.0;
  } else if (weightValue > 140000) {
    calibration_factor = 1067.0;
  } else {
    calibration_factor = 1068.0;
  }
}
// ====================================================================
// ====================================================================
// 이진탐색 - 내림차 순
struct CalibrationEntry {
  int threshold;
  float factor;
};

CalibrationEntry calibrationTable[] = {
  { 800000, 1062.0 },
  { 700000, 1062.5 },
  { 600000, 1065.0 },
  { 500000, 1065.5 },
  { 450000, 1065.5 },
  { 400000, 1065.5 },
  { 300000, 1065.8 },
  { 200000, 1065.7 },
  { 190000, 1065.6 },
  { 180000, 1065.7 },
  { 170000, 1065.8 },
  { 160000, 1065.9 },
  { 150000, 1066.0 },
  { 140000, 1067.0 }
};

const float defaultFactor = 1068.0;

int tableSize = sizeof(calibrationTable) / sizeof(calibrationTable[0]);

void checkCalibration2(int weightValue) {
  if (useManual == true) {
    return;
  }

  int left = 0;
  int right = tableSize - 1;
  int index = -1;

  // 내림차순 배열에서 weightValue가 어떤 임계값보다 큰지 확인
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (weightValue > calibrationTable[mid].threshold) {
      index = mid;  // 해당 조건을 만족하는 후보 갱신
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  if (index != -1) {
    calibration_factor = calibrationTable[index].factor;
  } else {
    calibration_factor = defaultFactor;
  }
}
