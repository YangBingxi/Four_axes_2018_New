/*
 * Control.h
 *
 *  Created on: 2018Äê7ÔÂ10ÈÕ
 *      Author: Sw Young
 */

#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

void Unlock(void);
void Lock(void);
void LandMode(void);
void Get_Coordinate(void);
void Get_Distance(void);
void Set_Alltitute(float Roll,float Pitch,float yaw,float height);
void FloatToByte(float floatNum,unsigned char* byteArry);


#endif /* CONTROL_CONTROL_H_ */
