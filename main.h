#include <STC8.H>
#include "pwm.h"
#include "uart2.h"
#include "oled.h"
#inlcude "oledfont.h"
#include "uart3.h"
#include "timer.h"
#define U8 unsigned char
#define U32 unsigned int
  
U8 T0_JS;
U8 FRONT_PWM,BACK_PWM;
U8 DIR_SERVO;
U8 ADC_LX, ADC_LY, ADC_RX, ADC_RY, ADC_SW1,ADC_SW2,ADC_SW3;
