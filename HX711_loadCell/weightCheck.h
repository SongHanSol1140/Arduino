// weightCheck.h
#include "HX711.h"
#include "mqttSetup.h"

#define DOUT  16 //데이터 핀 <DT>
#define CLK  17 // 클럭 핀 <CLK>
HX711 scale(DOUT, CLK);

// 보정값
float calibration_factor = 1068.1;
// 이동평균을 위한 배열
const int averageSize = 4; // 이동 평균을 위한 배열 크기
long array[averageSize]; // 값을 저장할 배열
int numElements  = 0; // 현재 배열 인덱스
int zeroFactor = 0;
bool checkZeroFactor = false;
float tolerance = 50;
// 평균값
int average = 0;
// 무게0 카운트
int weightCount = 0;
// 측정된 무게
float weight = 0.0;

void addArray();
void setZeroFactor();
void calculate();
void checkCalibration(int averageValue);
void getAverage();



// 영점 잡기
void setZeroFactor(int repeatNumber){
  // if(!checkZeroFactor){
  // }
  Serial.println("영점잡기");
  checkZeroFactor = true;
  zeroFactor = scale.read_average(repeatNumber);
  tolerance = zeroFactor * 0.0003;
}

// 새로운 값을 읽어 배열에 저장
void addArray(){
  long newValue = scale.read_average(5);

  // 배열이 가득 찼는지 확인
  if (numElements < averageSize) {
    // 배열이 아직 가득 차지 않았다면 값을 추가하고 numElements증가
    array[numElements] = newValue;
    numElements++;
  } else {
    // 배열이 가득 찼다면, 가장 오래된 값을 제거하고 모든 요소를 앞으로 이동
    for (int i = 1; i < averageSize; i++) {
      array[i - 1] = array[i];
    }
    // 배열의 마지막에 새로운 값을 추가
    array[averageSize - 1] = newValue;
  }
}
void getAverage(){
    int sum = 0;
    for (int i = 0; i < averageSize; i++) {
    sum += array[i];
    }
    // 이동 평균값
    average = sum / averageSize;
    
}
void calculate(){
// 배열이 가득 찼을 경우 평균 계산
    // 무게
    weight = round((average - zeroFactor) / calibration_factor * 2) / 2.0;
    float weight2 = (average - zeroFactor) / calibration_factor;

    // 영점에서 값이 tolerance이상일때만 무게값을 전송
    if(average > zeroFactor + (tolerance*2)){
      sendWeightMQTT(weight);
      // Serial.print("영점: "); //
      // Serial.println(zeroFactor); //
      // Serial.print("무게: "); //
      // Serial.print(weight); // 
      // Serial.print(" // ");
      // Serial.println(weight2, 4);
      // Serial.print("디지털값: "); // 
      // Serial.println(average); // 
      // Serial.print("무게 - 영점 :  "); // 
      // Serial.println(average - zeroFactor); //
      // Serial.print("0.01당 디지털값 : "); // 
      // Serial.println((average - zeroFactor)/(weight*100)); //
      weightCount = 0;
    }else{
      sendWeightMQTT(0);
      // Serial.print("영점: "); //
      // Serial.println(zeroFactor); //
      // Serial.print("무게: "); // 
      // Serial.println(weight);
      // Serial.print("디지털값: "); // 
      // Serial.println(average); //
      // Serial.print("무게 - 영점 : "); // 
      // Serial.println(average - zeroFactor); //
      // Serial.print("0.01당 디지털값 : "); // 
      // Serial.println((average - zeroFactor)/(weight*100)); //
      // Serial.println(0);

      // // 허용오차보다 클경우 영점을 다시잡아야함
      // if(average > zeroFactor + tolerance){
      //   weightCount++;
      //   if(weightCount > 20){
      //     weightCount = 0;
      //     checkZeroFactor = false;
      //     numElements = 0; // 배열 인덱스 초기화
      //     Serial.println("초기화");
      //   }
      // }else{
      //   weightCount = 0;
      // }
    }
    // Serial.println(scale.get_units());
    // Serial.println("================"); 

}

// =================================
void checkCalibration(int averageValue){
    // 캘리브레이션값 조정
    if(averageValue > 1050000){
      calibration_factor = 1062.5;
    }else if(averageValue > 950000){
      calibration_factor = 1063.0;
    }else if(averageValue > 850000){
      calibration_factor = 1063.5;
    }else if(averageValue > 750000){
      calibration_factor = 1064.0;
    }else if(averageValue > 550000){
      calibration_factor = 1064.5;
    }else if(averageValue > 400000){
      calibration_factor = 1065.0;
    }else if(averageValue > 300000){
      calibration_factor = 1065.5;
    }else if(averageValue > 150000){
      calibration_factor = 1066.0;
    }else if(averageValue > 140000){
      calibration_factor = 1067.0;
    }else{
      calibration_factor = 1068.0;
    }
}