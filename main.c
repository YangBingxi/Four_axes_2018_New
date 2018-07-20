/**
  ******************************************************************************
  * �ļ�����: main.c
  * ��    ��: By Sw Young
  * ��    ��: V1.0
  * ��    ��:
  * ��д����: 2018.7.6
  ******************************************************************************
  * ˵����
  * Ӳ��ƽ̨��
  *   MCUc:TM4C123��Pixhawk�����ߴ��ڡ���ˢ���
  * ������˵����
  *     ��ߡ���ȡͼ�������ڶ�ʱ������ɣ���߰���������ʱ�����ܣ��ұ߰����رն�ʱ�����ܡ�
  * Github��
  ******************************************************************************
**/

#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"
#include "math.h"

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "Timer/Timer.h"
#include "delay/delay.h"
#include "utils/uartstdio.h"
#include "driverlib/uart.h"
#include "uart/uart.h"
#include "uart/uartstdio.h"
#include "Control/Control.h"
#include "key/key.h"
#include "Pid/pid.h"
#include "head.h"
#include "colorful_LED.h"


/**
  * �� �� ��:HardwareConfig
  * ��������: Ӳ����ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void HardwareConfig(void)
{
    Uart0Iint();        //����0��ʼ��
    Uart1Iint();        //����1��ʼ��
    UART2Iint();        //����2��ʼ��
    UART3Iint();        //����3��ʼ��


    //Timer0_Config();    //��ʱ����ʼ��
    Timer1_Config();
    Timer2_Config();

    LED_Config();    //LED��ʼ��
    LED_Set(BLUE);

    Key_Configure();    //������ʼ��
    Key_Interrupt();    //�����ж�

    IntMasterEnable();

    PID_Init();

}

int main(void)
{
    FPUEnable();        //������������
    FPULazyStackingEnable();

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //��Ƶ����80M
    HardwareConfig();
    //UARTprintf("Hello\n");

    while(1)
    {
        Delay_ms(500);
    }
}
