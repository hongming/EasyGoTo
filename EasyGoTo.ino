/*
  使用Joystick控制两个步进电机
  参考http://www.schmalzhaus.com/EasyDriver/Examples/EasyDriverExamples.html的Example 5: Changing motor speed
*/

#include <AccelStepper.h>
//从A0读取数据，修改步进点击运转速度
#define SPEED_PIN 0
//X轴数据
#define RA_PIN  5
//Y轴数据
#define DEC_PIN  6
//按下数据
#define STOP_PIN 7

//运转速度上下限
#define MAX_SPEED 500
#define MIN_SPEED 0.1

//初始变量
AccelStepper stepper_RA(1,9,8);
AccelStepper stepper_DEC(1,7,6);

//JoyStick阈值


//初始配置
void setup(){
//初始速度
  stepper_RA.setMaxSpeed(3000);
  stepper_DEC.setMaxSpeed(2000);
//初始加速度
  stepper_RA.setAcceleration(1000);
  stepper_DEC.setAcceleration(800);
  pinMode(SPEED_PIN, INPUT);
  pinMode(RA_PIN, INPUT);
  pinMode(DEC_PIN, INPUT);
  pinMode(STOP_PIN, INPUT);
}

//控制
void loop(){
  static float current_speed_RA = 0.0;            //当前速度
  static float current_speed_DEC = 0.0;            //当前速度
  static int analog_read_count = 1000;        //倒计时
  static char sign_RA = 0;                       // -1,1,0用于控制开关和方向,速度可正可负
  static char sign_DEC = 0;                       // -1,1,0用于控制开关和方向,速度可正可负
  static int analog_value = 0;                //存储数值
//读取X轴数据
  if((analogRead(RA_PIN >=0))&&(analogRead(RA_PIN)<=512)&&(digitalRead(STOP_PIN)==1)){
    sign_RA = 1;
  }
  else if((analogRead(RA_PIN >512))&&(analogRead(RA_PIN)<=1023)&&digitalRead(STOP_PIN)==1)
  {
    sign_RA = -1;
  }
  else if (digitalRead(STOP_PIN) == 0) {
    sign_RA = 0;
  }
  
//读取Y轴数据
if((analogRead(DEC_PIN >=0))&&(analogRead(DEC_PIN)<=512)&&(digitalRead(STOP_PIN)==1)){
  sign_DEC = 1;
}
else if((analogRead(DEC_PIN >512))&&(analogRead(DEC_PIN)<=1023)&&digitalRead(STOP_PIN)==1)
{
  sign_DEC = -1;
}
  else if (digitalRead(STOP_PIN) == 0) {
    sign_DEC = 0;
  }

  if(analog_read_count>0){
    analog_read_count--;
  } else {
    analog_read_count=3000;
    analog_value = analogRead(SPEED_PIN);
    stepper_RA.runSpeed();
    current_speed_RA = sign_RA * ((analog_value/1023.0) * (MAX_SPEED - MIN_SPEED)) + MIN_SPEED;
    stepper_RA.setSpeed(current_speed_RA);
    stepper_DEC.runSpeed();
    current_speed_DEC = sign_DEC * ((analog_value/1023.0) * (MAX_SPEED - MIN_SPEED)) + MIN_SPEED;
    stepper_DEC.setSpeed(current_speed_DEC);
  }
  stepper_RA.runSpeed();
  stepper_DEC.runSpeed();
}

