#include "main.h"

void main()
{
  	Pwm_Init();
  	//Uart2Init();
  	Uart3Init();
	iicInit();
	OLED_Init(); 
	OLED_Clear(); 
  while(1)
  {
   		OLED_ShowString(0,0,"UART:",16);
		OLED_ShowNum(0,2,ADC_RX,3,16);
		OLED_ShowNum(40,2,ADC_RY,3,16);
		
		OLED_ShowNum(0,4,ADC_LX,3,16);
		OLED_ShowNum(40,4,ADC_LY,3,16);
		OLED_ShowNum(0,6,ADC_SW1,3,16);
		OLED_ShowNum(40,6,ADC_SW2,3,16);
		if(ADC_LY > 0x80)
		{
			FRONT_PWM = (ADC_LY - 0x80) * 0x80;
			BACK_PWM = (ADC_LY - 0X80) * 0x80;
			P0 |= 0xA0;
		}
		else if(ADC_LY < 0x80)
		{
			FRONT_PWM = (0x80 - ADC_LY) * 0x80;
			BACK_PWM = (0x80 - ADC_LY) * 0x80;
			P0 |= 0x50;
		}
		else 
		{
			FRONT_PWM = 0;
			BACK_PWM = 0;
			P0 &= 0x0F;
		}
		DIR_SERVO = ADC_LX * 0x80;
    
  }
}




void uart3_interrupt() interrupt 17 //uart3 17
{
	U8 TEMP;
  	U8 JS;
	if (S3CON & S3RI)
	{
		S3CON &= ~S3RI;
		TEMP = S3BUF;
    	if (TEMP == 0XFF)
		{
			JS = 0;
		}
		switch (JS)
		{
		case 0:
			JS++;
			break;
		case 1:
			ADC_RY = TEMP;
			JS++;
			break;
		case 2:
			ADC_RX = TEMP;
			JS++;
			break;
		case 3:
			ADC_LX = TEMP;
			JS++;
			break;
		case 4:
			ADC_LY = TEMP;
			JS++;
			break;
		case 5:
			ADC_SW1 = TEMP;
			JS++;
			break;
		case 6:
			ADC_SW2 = TEMP;
			JS++;
			break;
		case 7:
			ADC_SW3 = TEMP;
			JS++;
			break;
		}
		if (JS > 7)
			JS = 0;
	}
}

void PWM_Isr() interrupt 22
{
    char store;

    if (PWMCFG & 0x80)
    {
        store = P_SW2;
        P_SW2 |= 0x80;
        PWM0T2 = FRONT_PWM;
				PWM1T2 = BACK_PWM;
				PWM2T2 = DIR_SERVO;
        P_SW2 = store;
    }
}
