/**
  ******************************************************************************
  * 文件名程: contral.c
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


#include "Timer/Timer.h"
#include "delay/delay.h"
#include "uart/uart.h"
#include "Control.h"

/*
 * 参数初始化
 */
//高度:单位 MM
float  Real_Distance,Last_Real_Distance;
extern int Distance_Laser;


uint16_t Goal_XCoordinate,Goal_YCoordinate;
uint16_t Real_XCoordinate,Real_YCoordinate;
extern volatile uint8_t get_x, get_y;
uint8_t i = 0;

bool Control_Open = false;
void FloatToByte(float floatNum,unsigned char* byteArry)
{
    uint8_t t;
    char* pchar=(char*)&floatNum;
    for(t=0;t<sizeof(float);t++)
    {
        *byteArry=*pchar;
        pchar++;
        byteArry++;
    }
}
unsigned char remote[20];

void remotepr_package(float roll,float pitch)
{
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0x10;
    FloatToByte(roll,&remote[3]);
    FloatToByte(pitch,&remote[7]);
    for (i = 11; i < 20; i++)
    {
        remote[i]=0x00;
    }
    UART2Send(remote,20);//发送指令
}
void remoteyh_package(float yaw,float height)
{
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0x11;
    FloatToByte(yaw,&remote[3]);
    FloatToByte(height,&remote[7]);
    for (i = 11; i < 20; i++)
    {
        remote[i]=0x00;
    }
    UART2Send(remote,20);//发送指令
}


void Unlock(void)
{
    //发送解锁飞行指令
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0xFF;
    remote[3]=0x01;
    for (i = 4; i < 20; i++)
    {
        remote[i]=0x00;
    }
    UART2Send(remote,20);//发送指令
}
/**
  * 函 数 名:LockPixhawk
  * 函数功能: Pixhawk上锁函数函数
  * 输入参数:
  * 返 回 值: 无
  * 说    明: 无
  *   By Sw Young
  *   2017.7.6
  */
void Lock(void)
{
    //上锁命令
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0xFF;
    remote[3]=0x00;
    for (i = 4; i < 20; i++)
    {
        remote[i]=0x00;
    }
    UART2Send(remote,20);//发送指令
}
/**
  * 函 数 名:LandMode
  * 函数功能: 飞行器降落模式函数
  * 输入参数:
  * 返 回 值: 无
  * 说    明: 无
  *   By Sw Young
  *   2017.7.6
  */
void LandMode(void)
{
    //降落模式
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0xFF;
    remote[3]=0x02;
    for (i = 4; i < 20; i++)
    {
        remote[i]=0x00;
    }
    UART2Send(remote,20);//发送指令
}

void Get_Coordinate(void)
{
    get_x = Real_XCoordinate;
    get_y = Real_YCoordinate;
}
/**
  * 函 数 名:Get_Distance
  * 函数功能: 获取飞行器高度函数
  * 输入参数:
  * 返 回 值: 无
  * 说    明: 无
  *   By Sw Young
  *   2017.7.6
  */
void Get_Distance(void)
{
    Real_Distance = Distance_Laser*10;//转换为mm
    if(fabs(Real_Distance-Last_Real_Distance)>500)
        Real_Distance = Last_Real_Distance;
    Last_Real_Distance = Real_Distance;
}

void Set_Alltitute(float Roll,float Pitch,float Yaw,float Height)
{
    //发送调节函数
    remotepr_package(Roll,Pitch);
    remoteyh_package(Yaw,Height);
}

