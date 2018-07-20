/*
 * Type_conversion.c
 *
 *  Created on: 2018Äê7ÔÂ20ÈÕ
 *      Author: wk
 */
#include "Type_conversion.h"
#include "uart/uart.h"
#include "Control/Control.h"

//void FloatToByte(float floatNum,unsigned char* byteArry)
//{
//    int t;
//    char* pchar=(char*)&floatNum;
//    for(t=0;t<sizeof(float);t++)
//    {
//        *byteArry=*pchar;
//        pchar++;
//        byteArry++;
//    }
//}

void arrycat(unsigned char *dst,unsigned char index,unsigned char *src,unsigned char len)
{
    unsigned char i=0;
    for(i=0;i<len;i++)
    {
        *(dst+index+i)=*(src+i);
    }
}

void SendToFlight(float Get_C_Distance)
{
    unsigned char floatToHex[4] = {0};
    unsigned char dataToFlight[16] = {0};
    float temp;
    int HeightData[7];

    dataToFlight[0]=0X55;
    dataToFlight[1]=0XAA;
    dataToFlight[2]=0X00;

    temp = 0;
    FloatToByte(temp,floatToHex);
    arrycat(dataToFlight,3,floatToHex,4);

    temp = 0;
    FloatToByte(temp,floatToHex);
    arrycat(dataToFlight,7,floatToHex,4);

    temp = Median_Filter(Get_C_Distance,7,HeightData)/1000;
    FloatToByte(temp,floatToHex);
    arrycat(dataToFlight,11,floatToHex,4);
    dataToFlight[15]=0XAA;
    UART3Send(dataToFlight,16);
}

float Median_Filter(int data,int measureNum,int *Filterdata)
{
  unsigned int i = 0;
    unsigned int j = 0;
    int temp;
    unsigned int MAX_error_targe = 0;
    int MAX_error1;
    Filterdata[measureNum-1] = data;
    for(i=0;i<measureNum-1;i++)
    {
     Filterdata[i]=Filterdata[i+1];
    }
    for(i = 0 ; i < measureNum-1 ; i++)
    {
            for(j = 0 ; j < measureNum-1-i; j++)
            {
                    if(Filterdata[j] > Filterdata[j+1] )
                    {
                            temp = Filterdata[j];
                            Filterdata[j] =  Filterdata[j+1];
                            Filterdata[j+1] = temp;
                    }
            }
    }
    MAX_error1 = Filterdata[1] - Filterdata[0];
    for(i = 1 ; i < measureNum-1 ; i++)
    {
            if(MAX_error1 < Filterdata[i+1] - Filterdata[i] )
            {
                    MAX_error1 =  Filterdata[i+1] - Filterdata[i];
                    MAX_error_targe = i;
            }
    }
    float Average_data=0;
    if(MAX_error_targe+1 > (measureNum+1)/2)
    {
            for(i = 0 ; i <= MAX_error_targe ; i++)
            {
                    Average_data += Filterdata[i];
            }
            Average_data /= (MAX_error_targe+1);
    }
    else
    {
            for(i = MAX_error_targe + 1 ; i < measureNum ; i++)
            {
                    Average_data += Filterdata[i];
            }
            Average_data /= (measureNum - MAX_error_targe -1);
    }
    return Average_data;
}


