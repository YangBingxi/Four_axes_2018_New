/**
  ******************************************************************************
  * 文件名程: key.c
  * 作    者: By Sw Young
  * 版    本: V1.0
  * 功    能:
  * 编写日期: 2018.7.6
  ******************************************************************************
  * 说明：
  * 硬件平台：TM4C123G
  *   *****
  * 软件设计说明：
  *   *****
  * Github：
  ******************************************************************************
**/
#include <0.96'OLED/OLED.h>
#include <0.96'OLED/OLED.h>

#include "key.h"
#include "Control/Control.h"
uint32_t ReadPin0;
uint32_t ReadPin4;
int KeyPress4=0;
extern bool Control_Open;
extern float volatile Real_Distance ;
extern uint16_t  Goal_Distance;//默认定高值800mm
void Key_Configure(void)
{
    //使能GPIO外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //解锁PF0,直接对寄存器进行操作
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    //输入GPIO配置
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);
    //  GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

}

void Key_Interrupt(void)
{//注意，在使用此函数时，请在初始化表里面添加    void Int_Handler_GPIOF(void)   中断服务程序
    //中断配置
       /****初始化外部中断并且设置外部中断为低电平触发方式********/
       GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);                     //打开外部中断
       GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0, GPIO_LOW_LEVEL);//PF4&PF1下降沿触发
       //GPIOIntRegister(GPIO_PORTF_BASE, Int_Handler_GPIOF);
       IntEnable(INT_GPIOF);
       //IntPrioritySet(INT_GPIOF, 0);                                   //中断优先级
       IntMasterEnable();

}

int Key_Scan(int PF)
{      //PF=0  -->PF0
       //PF=4  -->PF4
   int  KeyFlag=0;
    if(PF==0)
    {
        ReadPin0=GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0);
               if((ReadPin0&GPIO_PIN_0)  != GPIO_PIN_0)
                   {
                           Delay_ms(100);//delay 100ms
                           ReadPin0=GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0);
                               if((ReadPin0&GPIO_PIN_0)  != GPIO_PIN_0)
                               {
                                   KeyFlag=1;
                                   while(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0));
                               }


                   }
    }
    if(PF==4)
    {
        KeyFlag=0;
        ReadPin4=GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4);
               if((ReadPin4&GPIO_PIN_4)  != GPIO_PIN_4)
                   {
                           Delay_ms(100);//delay 100ms
                           ReadPin4=GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4);
                               if((ReadPin4&GPIO_PIN_4)  != GPIO_PIN_4)
                               {
                                   if(KeyPress4>=0&&KeyPress4<=4)
                                            KeyPress4=(1+KeyPress4);
                                     KeyFlag=1;
                                   while(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4));
                               }

                   }
    }
       return KeyFlag;
}

void Int_Handler_GPIOF(void)
{
    uint32_t ui32IntStatus;
    ui32IntStatus = GPIOIntStatus(GPIO_PORTF_BASE, true);
    GPIOIntClear(GPIO_PORTF_BASE, ui32IntStatus);//清除中断标志位
    if((ui32IntStatus & GPIO_PIN_4)  == GPIO_PIN_4)//PF4
    {
        GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_4);                     //打开外部中断
        UART1Send("Key2 Is OK\n",11);
        Control_Open = true;
        OLED_ShowString(90,3,"ON ",16);
        Unlock();
        while(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4));
    }
     if((ui32IntStatus & GPIO_PIN_0)  == GPIO_PIN_0)//PF0
    {
         GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_0);                     //打开外部中断
         UART1Send("Key1 Is OK\n",11);

         while(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0));
    }
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4 | GPIO_PIN_0);                     //打开外部中断

}
