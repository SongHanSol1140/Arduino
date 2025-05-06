/*
I2C 연결
  // 사용할 객체명 선언
  MCP23017 mcp1, mcp2, mcp3;
  // 연결
  Mcp23017_Init(&mcp1, 0x20); // mcp1에 0x20주소 연결
  Mcp23017_Init(&mcp2, 0x21); // mcp2에 0x20주소 연결

핀 개별설정
  Set_gpio_pin(&mcp1, PORTA, PIN0, MHIGH);
  Set_gpio_pin(&mcp1, PORTA, PIN0, MLOW);

핀 출력 한번에 설정
  Write_gpio(&mcp1, PORTA, 0XFF); A Pin을 전부 LOW로
  Write_gpio(&mcp1, PORTB, 0X00); B Pin을 전부 LOW로
  Write_gpio(&mcp2, PORTA, 0xFF); A Pin을 전부 LOW로
  Write_gpio(&mcp2, PORTB, 0xFF); B Pin을 전부 LOW로