#include "pca9685.h"

void SG90_Init() {
	PCA9685_Init();
}

void SG90_SetAngle(u8 id, u8 angle) {
	PCA9685_SetChannelDuty(id, 0, (u32)(4095*((angle/180.0)*2.0+0.5)/20.0));
}
