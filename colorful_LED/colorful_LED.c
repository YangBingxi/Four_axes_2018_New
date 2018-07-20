/**
  ******************************************************************************
  * �ļ�����: ColorFulLed.c
  * ��    ��: By Sw Young
  * ��    ��: V1.0
  * ��    ��:
  * ��д����: 2018.7.6
  ******************************************************************************
  * ˵����
  * Ӳ��ƽ̨��TM4C123G
  *   *****
  * ������˵����
  *   *****
  * Github��
  ******************************************************************************
**/
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/fpu.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "utils/uartstdio.h"
#include "driverlib/pwm.h"
#include "delay/delay.h"
#include "colorful_LED.h"
/**
  * �� �� ��:LED_ColorInit
  * ��������: �ʵƳ�ʼ����PWM���ƣ�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void LED_ColorInit(void)
{
    // PWMʱ�����ã�4��Ƶ
    SysCtlPWMClockSet(SYSCTL_PWMDIV_4);
    //ʹ��PWM1ģ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    //ʹ��PWM�������GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinConfigure(GPIO_PF1_M1PWM5);  //�ú�����������λ����
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    //����GPIOΪPWM����
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    //����PWM������1���Ӽ�����
    PWMGenConfigure(PWM1_BASE,PWM_GEN_2,PWM_GEN_MODE_UP_DOWN| PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM1_BASE,PWM_GEN_3,PWM_GEN_MODE_UP_DOWN| PWM_GEN_MODE_NO_SYNC);
     //����PWM������1������
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 25500);        //f~1k
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 25500);        //f~1k
    //����GPIO�����������
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 00000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 00000);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 00000);
    //ʹ�����
    PWMOutputState(PWM1_BASE, (PWM_OUT_5_BIT|PWM_OUT_6_BIT|PWM_OUT_7_BIT), true);
    //ʹ��PWM������2��3
    PWMGenEnable(PWM1_BASE,PWM_GEN_2);
    PWMGenEnable(PWM1_BASE,PWM_GEN_3);

}
/**
  * �� �� ��:LED_Color
  * ��������: ��ɫ���ƺ���
  * �������: ������ɫ��RGBֵ
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void LED_Color(uint8_t r,uint8_t g,uint8_t b)
{
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, r*100);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, g*100);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, b*100);
}
/**
  * �� �� ��:LED_Config
  * ��������: LED��ʼ�����ߵ͵�ƽ���ƣ�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void LED_Config(void)
{
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
}
/**
  * �� �� ��:LED_Set
  * ��������: LED��ɫ����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void LED_Set(uint8_t color)
{
    if(color==0)//��
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0);
    }
    if(color==1)//��
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, GPIO_PIN_2);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0);
    }
    if(color==2)//��
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, GPIO_PIN_3);
    }
    if(color==3)//Ʒ��
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, GPIO_PIN_2);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0);
    }
    if(color==4)//��
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, GPIO_PIN_3);
    }
    if(color==5)//ǳ��
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, GPIO_PIN_2);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, GPIO_PIN_3);
    }
    if(color==6)//��
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, GPIO_PIN_2);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, GPIO_PIN_3);
    }
    if(color==7)
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0);
    }
}
/**
  * �� �� ��:Led_Twinkle
  * ��������:   LED��˸����
  * �������: ��ɫ����˸����
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void Led_Twinkle(uint8_t color,uint8_t times)
{
    uint8_t t=0;
    for(t=0;t<times;t++)
    {
        LED_Set(color);
        Delay_ms(30);
        LED_Set(LedOff);
    }
}
