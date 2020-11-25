
#include "pca9685.h"

int main(void) {
	PCA9685_Init();
	while(1){
		PCA9685_SetPWM(0, 0, (u32)(4096*(0.5/20));
    delay(80000000);
		PCA9685_SetPWM(0, 0, (u32)(4096*(1.5/20));
    delay(80000000);
	}
}
