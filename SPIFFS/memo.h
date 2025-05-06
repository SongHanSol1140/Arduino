//<아두이노 2.0 이전버전 설치>
//    2.0 이후버전은 플러그인이 지원을 안함
//    
//<플러그인 설치>
//    https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/
//    ESP32FS-1.1.zip 버전을 받아서 documnet(내문서) - arduino - tools(해당 폴더를 만들어서) - 여기에 압축해제
//        Tools - ESP32FS - tool - esp32fs.jar 경로로 되었다면 완료
//        아두이노 2.0이전 버전을 재실행하면 도구(tools)에 ESP32 sketch Data Upload가 생길것임
//
//
//
//<추가보드 관리자 설치>
//    환경설정(기본설정) - 추가 보드 관리자 URL - https://dl.espressif.com/dl/package_esp32_index.json
//
//<ESP32 보드 설치>
//    도구 - 보드 -  보드매니저(Ctrl + shift + B) - ESP32 설치
//
//<ESP32 보드 세팅>
//    도구 - 보드 - ESP32 Aruduino- Esp32 dev module
//    upload Speed - 115200
//    port 설정 해주기(작성당시 COM5로 되어있음) - 포트 인식 못할시 CP210x usb드라이버를 다운로드해야된다는 말이있음
//
//
//<업로드할 데이터 파일 설정>
//    먼저 빈 스케치 저장을 누른뒤 업로드할 프로젝트 생성
//    ex) spiffs라는 프로젝트를 생성하면 spiffs.ino(코드파일)이 생김
//    해당 파일 경로에 data라는 폴더를 생성후 그안에 넣고싶은 파일을 넣음
//    이제 아두이노 IDE로 돌아와서 <ESP32 sketch Data Upload>를 실행
//    data 폴더 안에 있는 파일들이 ESP32의 SPIFFS공간으로 업로드됨
//    만약 비어잇는 폴더를 업로드한다면 이전에 업로드한 파일들도 모두 사라짐
//
//
//
//
//
//<ESP32 SPIFFS공간에 업로드된 파일들 파일코드들 확인>
//#include "SPIFFS.h"
//
//void setup() {
//    Serial.begin(9600);  // 시리얼 포트 초기화
//
//    // Mount SPIFFS
//    if (!SPIFFS.begin(true)) {
//    Serial.println("An error has occurred while mounting SPIFFS");
//    return;
//    }
//
//    // List all files
//    File root = SPIFFS.open("/");
//    File file = root.openNextFile();
//
//    while (file) {
//    Serial.print("File: ");
//    Serial.println(file.name()); // Print file name
//    file = root.openNextFile();
//    }
//}
//
//void loop() {
//    // put your main code here, to run repeatedly:
//}
//
//해당 코드를 실행시키면 SPIFFS공간에 파일이 존재할 시 파일명을 확인할 수 있음
//
//
//
//
//
//
