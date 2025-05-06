#include <Wire.h>

const int inputPin = 34;  // 온도 센서가 연결된 핀
const int numSamples = 5;  // 이동 평균을 위한 샘플 개수

double inputArray[numSamples];
int inputIndex = 0;
double sumInput = 0;

double adcMax = 4095.0;
double Vs = 3.3;
float R1 = 63000.0;  // 배선에 저항 => 이거 높이면 현재온도가 낮아지는데,
// 10k 온도계 => 실제저항 10k 12000~14000에 비슷한온도가 측정
// 50k 온도계 -> 실제저항 10k 60000~65000에 유사한 온도가 측정
// -> 되긴하는데 이거맞나?
float Beta = 3950.0;  // Beta 값
float To = 298.15;  // 25도의 켈빈 온도
// float Ro = 10000.0;  

float resistanceTable[] = {
  868567, 816579, 768089, 722838, 680550, 641119, 604228, 569730, 537454, 507241,
  478945, 452010, 426784, 403146, 380986, 360203, 340700, 322392, 305196, 289039,
  273850, 259462, 245930, 233198, 221213, 209927, 199294, 189272, 179823, 170910,
  162499, 154429, 146806, 139604, 132795, 126358, 120268, 114505, 109050, 103885,
  98992, 94355, 89961, 75795, 81843, 78095, 74538, 71162, 67957, 64913,
  62021, 59274, 56663, 54180, 51820, 50000, 48256, 46189, 44221, 42348,
  40564, 38865, 37246, 35703, 34233, 32831, 31494, 30219, 29020, 27841,
  26733, 25675, 24664, 23699, 22777, 21896, 21054, 20249, 19479, 18742,
  18034, 17363, 16718, 16100, 15508, 14941, 14398, 13878, 13379, 12901,
  12443, 12003, 11582, 11177, 10788, 10416, 10058, 9714, 9384, 9066,
  8761, 8468, 8187, 7916, 7655, 7404, 7163, 6931, 6708, 6493,
  6286, 6086, 5894, 5705, 5525, 5313, 5187, 5032, 4878, 4729,
  4586, 4447, 4313, 4184, 4060, 3939, 3823, 3711, 3602, 3497,
  3396, 3298, 3203, 3112, 3023, 2937
};

float temperatureTable[] = {
  -30, -29, -28, -27, -26, -25, -24, -23, -22, -21,
  -20, -19, -18, -17, -16, -15, -14, -13, -12, -11,
  -10, -9, -8, -7, -6, -5, -4, -3, -2, -1,
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
  10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
  20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
  30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
  40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
  50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
  60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
  70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
  80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
  90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
  100, 101, 102, 103, 104, 105
};

// 저항값을 이용해 온도를 보정하는 함수
float getCalibratedTemperature(float resistance) {
  for (int i = 0; i < sizeof(resistanceTable) / sizeof(resistanceTable[0]) - 1; i++) {
    if (resistance >= resistanceTable[i + 1] && resistance <= resistanceTable[i]) {
      float tempDiff = temperatureTable[i + 1] - temperatureTable[i];
      float resDiff = resistanceTable[i] - resistanceTable[i + 1];
      float ratio = (resistance - resistanceTable[i + 1]) / resDiff;
      return temperatureTable[i + 1] + (ratio * tempDiff);
    }
  }
  return -1; // 테이블 범위 밖의 저항값인 경우
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  double Vout, Rt = 0;
  double T, Tc, Tf = 0;
  double inputVolt = analogRead(inputPin) * (Vs / adcMax);  // ADC 값을 전압으로 변환
  Serial.println(analogRead(inputPin));
  Serial.println(inputVolt);

  // 기존 샘플의 값을 빼고 새로운 샘플 값을 더함
  sumInput = sumInput - inputArray[0] + inputVolt;

  // 배열의 값을 한 칸씩 앞으로 이동
  for (int i = 0; i < numSamples - 1; i++) {
    inputArray[i] = inputArray[i + 1];
  }
  // 새로운 값을 배열의 끝에 추가
  inputArray[numSamples - 1] = inputVolt;

  // 평균 계산
  double averageVolt = sumInput / numSamples;

  Rt = R1 * averageVolt / (Vs - averageVolt);
  
  Tc = getCalibratedTemperature(Rt);
  Serial.print("현재 온도 : ");
  Serial.println(Tc);

  delay(1000);  // 1초마다 업데이트
}
