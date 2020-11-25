#ifndef _PCA9685_H
#define _PCA9685_H

#include "stm32f10x.h"

void PCA9685_Init();

// channel: 0 ~ 15
//      on: 0 ~ 4095
//     off: 0 ~ 4095
void PCA9685_SetChannelDuty(u8 channel, u32 on, u32 off);

#endif
