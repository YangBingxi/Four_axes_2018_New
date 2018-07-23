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
#include "0.96'OLED/OLED.h"


extern float  Real_Distance;
extern volatile uint8_t get_x, get_y;
extern bool Control_Open;


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

    /*
     * ��ʱ��1ִ��PID�㷨����pitch��roll
     * ��ʱ��2ִ�и߶ȷ���
     * ��ע����ʱ��2����
     */
    //Timer0_Config();    //��ʱ����ʼ��
    Timer1_Config();
    //Timer2_Config();

    LED_Config();           //LED��ʼ��
    LED_Set(BLUE);

    /*
     * ����ִ��һ������
     */
    Key_Configure();        //������ʼ��
    Key_Interrupt();        //�����ж�

    OLED_Init();            //��ʼ��OLED
    OLED_Clear();

    IntMasterEnable();
    /*
     * Pid����roll��pitch
     */
    PID_Init();

}

int main(void)
{
    FPUEnable();        //������������
    FPULazyStackingEnable();

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //��Ƶ����80M
    HardwareConfig();
    //UARTprintf("Hello\n");
    OledDisplayInit();  //��ʼ��OLED��ʾ����
    while(1)
    {
        if(Control_Open==false)
        {
            Get_Distance();//��ȡ�߶�
            Get_Coordinate();
            UARTprintf("RealDistance:%d\n",(int)Real_Distance);
            UARTprintf("GET_x=%d,GET_y=%d\n",get_x,get_y);
            Display();//��ʾ����
        }
        if(Real_Distance>1000)
        {
            //������ʱ��
            Timer2_Config();
        }
        Delay_ms(500);
    }
}
