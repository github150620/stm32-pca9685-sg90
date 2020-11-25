
#include "sg90.h"

void delay(int i) {
	while (i) {
		i--;
	}
}

int main(void) {
	SG90_Init();
	while(1){
		SG90_SetAngle(0, 0);
		delay(80000000);
		SG90_SetAngle(0, 90);
		delay(80000000);
		SG90_SetAngle(0, 180);
		delay(80000000);
	}
}
