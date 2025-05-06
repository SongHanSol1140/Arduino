// #include <ld3320.h>

// VoiceRecognition Voice;  //声明一个语音识别对象

// #define Led 8  //定义LED控制引脚

// void setup() {
//   pinMode(Led, OUTPUT);    //初始化LED引脚为输出模式
//   digitalWrite(Led, LOW);  //LED引脚低电平

//   Voice.init();                      //初始化VoiceRecognition模块
//   Voice.addCommand("kai deng", 0);  
//   Voice.addCommand("guan deng", 1); 
//   Voice.addCommand("a", 2); 
//   Voice.addCommand("i", 3); 
//   Voice.addCommand("u", 4); 
//   Voice.addCommand("e", 5); 
//   Voice.addCommand("o", 6); 
//   Voice.addCommand("xie xie", 7);  //添加指令，参数（指令内容，指令标签（可重复））
//   Voice.start();                     //开始识别
// }
// void loop() {
//   switch (Voice.read())  //判断识别
//   {
//     case 0:                     //若是指令“kai deng”
//       digitalWrite(Led, HIGH);  //点亮LED
//       break;
//     case 1:                    //若是指令“guan deng”
//       digitalWrite(Led, LOW);  //熄灭LED
//       break;
//     default:
//       break;
//   }
// }
// // 