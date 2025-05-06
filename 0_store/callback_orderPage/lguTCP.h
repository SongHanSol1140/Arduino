#ifndef LGUTCP_H
#define LGUTCP_H
#include <Arduino.h> 
// TCP 서버 초기화 함수
void initTCPServer();

// TCP 서버 루프 함수 (클라이언트 처리)
void handleTCPClients();

#endif // LGUTCP_H
