// door.h
#ifndef DOOR_H
#define DOOR_H

void setOpenTime(); // 문 개방시간 받아오는 함수(없을시 기본값)
void OpenDoor(); // OpenDoor 함수 선언 추가
void closeDoor(); // 문 닫힘 함수 선언
void checkEmergencyButton(); // 문 비상용 버튼 눌림
void checkSensors(); // 센서 체크 함수 선언
#endif // DOOR_H
