/**
  ******************************************************************************
  * �ļ�����: Timer.c
  * ��    ��: By Sw Young
  * ��    ��: V1.0
  * ��    ��:
  * ��д����: 2018.3.29
  ******************************************************************************
  * ˵����
  * Ӳ��ƽ̨��
  *   MCUc:TM4C123
  * ������˵����
  *
  * Github��
  ******************************************************************************
**/
#include "Timer.h"
#include "Control/Control.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "Type_conversion/Type_conversion.h"
#include "driverlib/gpio.h"
#include "delay/delay.h"
char Time_Flag = 0;
uint32_t Counter = 0;
uint8_t Beep_Flag = 0;
uint32_t Beep_Counter = 0;
uint32_t Beep_Fre = 40;
extern  float Real_Distance;
extern bool start_PID_X ;
extern bool start_PID_Y;
extern bool Control_Open;

/**
  * �� �� ��:MotorContolTimer.c
  * ��������:
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��:
  *   By Sw Young
  *   2018.03.29
  */
void Timer0_Config(void)
{
    //
    // The Timer0 peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    //
    // Configure Timer0A and Timer0B connect as a 32-bit periodic timer.
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC_UP);

    //
    // Set the load value to max value.
    //
    TimerLoadSet(TIMER0_BASE, TIMER_A, 0xFFFFFFFF);

    // Disable the timer0 interrupt.
    IntDisable(INT_TIMER0A);

    // Enable the timer.
    TimerEnable(TIMER0_BASE, TIMER_A);

    //
    // Enable processor interrupts.
    //
    IntMasterEnable();
}
/**
  * �� �� ��:Timer0IntHandler.c
  * ��������:
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��:
  *   By Sw Young
  *   2018.03.29
  */
uint8_t k=0;
void Timer0IntHandler(void)
{
    uint32_t ui32IntStatus;
    ui32IntStatus = TimerIntStatus(TIMER0_BASE, true);
    TimerIntClear(TIMER0_BASE, ui32IntStatus);//����жϱ�־λ
}
void Timer1_Config(void)
{
       //
       // Enable the peripherals used by this example.
       //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
       //
       // Enable processor interrupts.
       //
        IntMasterEnable();

       //
       // Configure the two 32-bit periodic timers.
       //
        TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);

        TimerLoadSet(TIMER1_BASE, TIMER_A,  4000000); //Fre = ��Ƶ/4000000 = 20HZ

       //
       // Setup the interrupts for the timer timeouts.
       //
        IntEnable(INT_TIMER1A);

        TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
       //
       // Enable the timers.
       //
        TimerEnable(TIMER1_BASE, TIMER_A);
}
/**
  * �� �� ��:Timer1IntHandler.c
  * ��������:
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��:
  *   By Sw Young
  *   2018.03.29
  */
/*
 * ��ʱ��1���жϷ�������PID.C��
 */
void Timer2_Config(void)
{
       //
       // Enable the peripherals used by this example.
       //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
       //
       // Enable processor interrupts.
       //
        IntMasterEnable();

       //
       // Configure the two 32-bit periodic timers.
       //
        TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);

        TimerLoadSet(TIMER2_BASE, TIMER_A,  8000000); //Fre = ��Ƶ/8000000 = 10HZ

       //
       // Setup the interrupts for the timer timeouts.
       //
        IntEnable(INT_TIMER2A);

        TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
       //
       // Enable the timers.
       //
        TimerEnable(TIMER2_BASE, TIMER_A);
}
uint32_t TimeCounter = 0;
uint8_t m=0,l=0;
void Timer2IntHandler(void)
{
    uint32_t ui32IntStatus;
    ui32IntStatus = TimerIntStatus(TIMER2_BASE, true);
    TimerIntClear(TIMER2_BASE, ui32IntStatus);//����жϱ�־λ

    TimeCounter++;
    if(TimeCounter>120)
    {
        start_PID_Y = false;
        for(l=0;l<10;l++)
        {
            //ǰ��ģʽ
            Set_Alltitute(      /*�����βε�roll��pitchλ���෴*/                    \
                                                                                 40,\
                                                                                  0,\
                                                                                  0,\
                                                                                  0);
            Delay_ms(100);
        }
        start_PID_Y = true;
        // ��������ý���ģʽ
        //   LandMode();
        TimerDisable(TIMER2_BASE, TIMER_A);
    }
    m =~ m;
    if(m)
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, GPIO_PIN_1);
    else
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1, 0);
}
