/**
  ******************************************************************************
  * 文件名程: main.c
  * 作    者: By Sw Young
  * 版    本: V1.0
  * 功    能:
  * 编写日期: 2018.7.6
  ******************************************************************************
  * 说明：
  * 硬件平台：
  *   MCUc:TM4C123、Pixhawk、无线串口、无刷电机
  * 软件设计说明：
  *     测高、获取图像坐标在定时器中完成，左边按键开启定时器功能，右边按键关闭定时器功能。
  * Github：
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
  * 函 数 名:HardwareConfig
  * 函数功能: 硬件初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  *   By Sw Young
  *   2017.7.6
  */
void HardwareConfig(void)
{
    Uart0Iint();        //串口0初始化
    Uart1Iint();        //串口1初始化
    UART2Iint();        //串口2初始化
    UART3Iint();        //串口3初始化


    //Timer0_Config();    //定时器初始化
    Timer1_Config();
    Timer2_Config();

    LED_Config();    //LED初始化
    LED_Set(BLUE);

    Key_Configure();    //按键初始化
    Key_Interrupt();    //按键中断

    IntMasterEnable();

    PID_Init();

}

int main(void)
{
    FPUEnable();        //开启浮点运算
    FPULazyStackingEnable();

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //主频设置80M
    HardwareConfig();
    //UARTprintf("Hello\n");

    while(1)
    {
        Delay_ms(500);
    }
}
