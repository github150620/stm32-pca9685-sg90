
#include "pca9685.h"

void delay(int i) {
	while (i) {
		i--;
	}
}

int main(void) {
	PCA9685_Init();
	while(1){
		PCA9685_SetChannelDuty(0, 0, (u32)(4095*(0.5/20)); // 0 degree
		delay(80000000);
		PCA9685_SetChannelDuty(0, 0, (u32)(4095*(2.5/20)); // 180 degree
		delay(80000000);
	}
}
