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
  * �������˵����
  *   *****
  * Github��
  ******************************************************************************
**/


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
    UART2Send(remote,20);//����ָ��
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
    UART2Send(remote,20);//����ָ��
}


void Unlock(void)
{
    //���ͽ�������ָ��
    remote[0]=0x55;
    remote[1]=0xAA;
    remote[2]=0xFF;
    remote[3]=0x01;
    for (i = 4; i < 20; i++)
    {
        remote[i]=0x00;
    }
    UART2Send(remote,20);//����ָ��
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
    for (i = 4; i < 20; i++)
    {
        remote[i]=0x00;
    }
    UART2Send(remote,20);//����ָ��
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
    for (i = 4; i < 20; i++)
    {
        remote[i]=0x00;
    }
    UART2Send(remote,20);//����ָ��
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
