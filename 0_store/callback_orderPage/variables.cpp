// variables.cpp
#include "variables.h"

// 와이파이
char wifi_ssid[] = "NNX2-2.4G";
char wifi_password[] = "$@43skshslrtm";
IPAddress wifiIP(192, 168, 0, 231);  // 접속할 고정 IP 주소
IPAddress gateway(192, 168, 0, 1);     // 게이트웨이 주소
IPAddress subnet(255, 255, 255, 0);    // 서브넷 마스크
IPAddress dns(192, 168, 0, 1);
// Centrex
const char *centrexHost = "centrex.uplus.co.kr";
const char *centrex_id = "00000000000";
const char *centrex_raw_password = "00000000";
const char *msg = "주문링크\r\nhttps://nanonix.help";


