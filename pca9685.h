#ifndef _PCA9685_H
#define _PCA9685_H

void PCA9685_Init();
void PCA9685_SetChannelDuty(u8 channel, u32 on, u32 off);

#endif
