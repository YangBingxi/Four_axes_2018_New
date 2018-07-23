/**
  ******************************************************************************
  * �ļ�����: contral.c
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

#include <0.96'OLED/OLED.h>
#include <0.96'OLED/OLED.h>
#include "Timer/Timer.h"
#include "delay/delay.h"
#include "uart/uart.h"
#include "Control.h"

/*
 * ������ʼ��
 */
//�߶�:��λ MM
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
unsigned char remote[16];

void remotepr_package(float roll,float pitch)
{
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0x10;
    FloatToByte(roll,&remote[3]);
    FloatToByte(pitch,&remote[7]);
    for (i = 11; i < 15; i++)
    {
        remote[i]=0x00;
    }
    remote[15]=0xAA;
    UART2Send(remote,16);//����ָ��
    Delay_ms(1);
}
void remoteyh_package(float yaw,float height)
{
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0x11;
    FloatToByte(yaw,&remote[3]);
    FloatToByte(height,&remote[7]);
    for (i = 11; i < 15; i++)
    {
        remote[i]=0x00;
    }
    remote[15]=0xAA;
    UART2Send(remote,16);//����ָ��
    Delay_ms(1);
}


void Unlock(void)
{
    //���ͽ�������ָ��
    Delay_ms(1000);
    Delay_ms(1000);
    Delay_ms(1000);

    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0x02;
    remote[3]=0x05;
    for (i = 4; i < 15; i++)
    {
        remote[i]=0x00;
    }
    remote[15]=0xAA;
    UART2Send(remote,16);//����ָ��
    Delay_ms(500);
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0x02;
    remote[3]=0x05;
    for (i = 4; i < 15; i++)
    {
        remote[i]=0x00;
    }
    remote[15]=0xAA;
    UART2Send(remote,16);//����ָ��
    Delay_ms(50);

    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0xFF;
    remote[3]=0x01;
    for (i = 4; i < 15; i++)
    {
        remote[i]=0x00;
    }
    remote[15]=0xAA;
    UART2Send(remote,16);//����ָ��
    Delay_ms(5);
    UART2Send(remote,16);//����ָ��
}
/**
  * �� �� ��:LockPixhawk
  * ��������: Pixhawk������������
  * �������:
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void Lock(void)
{
    //��������
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0xFF;
    remote[3]=0x00;
    for (i = 4; i < 15; i++)
    {
        remote[i]=0x00;
    }
    remote[15]=0xAA;
    UART2Send(remote,16);//����ָ��
    UART2Send(remote,16);//����ָ��
}
/**
  * �� �� ��:LandMode
  * ��������: ����������ģʽ����
  * �������:
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void LandMode(void)
{
    //����ģʽ
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0xFF;
    remote[3]=0x02;
    for (i = 4; i < 15; i++)
    {
        remote[i]=0x00;
    }
    remote[15]=0xAA;
    UART2Send(remote,16);//����ָ��
    UART2Send(remote,16);//����ָ��

}

void Get_Coordinate(void)
{
    get_x = Real_XCoordinate;
    get_y = Real_YCoordinate;
}
/**
  * �� �� ��:Get_Distance
  * ��������: ��ȡ�������߶Ⱥ���
  * �������:
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void Get_Distance(void)
{
    Real_Distance = Distance_Laser*10;//ת��Ϊmm
    if(fabs(Real_Distance-Last_Real_Distance)>500)
        Real_Distance = Last_Real_Distance;
    Last_Real_Distance = Real_Distance;
}

void Set_Alltitute(float Roll,float Pitch,float Yaw,float Height)
{
    //���͵��ں���
    remotepr_package(Roll,Pitch);
    remoteyh_package(Yaw,Height);
}
/**
  * �� �� ��:OledDisplayInit
  * ��������: OLED��ʾ��ʼ������
  * �������:
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void OledDisplayInit(void)
{
    OLED_Clear();
    OLED_ShowString(16,0,"FourAxes2018",16);
    OLED_ShowString(6,3,"AxesState:",16);
    OLED_ShowString(90,3,"OFF",16);
    OLED_ShowString(6,6,"GoalDis:",16);
    OLED_ShowNum(50,6,150,4,16);
    OLED_ShowString(80,88,"CM",16);
}
/**
  * �� �� ��:Display
  * ��������: OLED��ʾ����
  * �������:
  * �� �� ֵ: ��
  * ˵    ��: ��
  *   By Sw Young
  *   2017.7.6
  */
void Display(void)
{
    OLED_ShowString(6,3,"AxesState:",16);
    if(Control_Open)
        OLED_ShowString(90,3,"ON ",16);
    else
        OLED_ShowString(90,3,"OFF",16);
    OLED_ShowString(6,6,"RealDis:",16);
    OLED_ShowNum(56,6,Real_Distance,4,16);
    OLED_ShowString(88,6,"MM",16);
}
