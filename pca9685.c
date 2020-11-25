#include "stm32f10x.h"

#define PCA9685_I2C_ADDR 0x40

#define MODE1       0x00
#define MODE2       0x01
#define SUBADR1     0x02
#define SUBADR2     0x03
#define SUBADR3     0x04
#define ALLCALLADR  0x05
#define LED0_ON_L   0x06
#define LED0_ON_H   0x07
#define LED0_OFF_L  0x08
#define LED0_OFF_H  0x09
#define LED1_ON_L   0x0A
#define LED1_ON_H   0x0B
#define LED1_OFF_L  0x0C
#define LED1_OFF_H  0x0D
#define LED2_ON_L   0x0E
#define LED2_ON_H   0x0F
#define LED2_OFF_L  0x10
#define LED2_OFF_H  0x11
#define LED3_ON_L   0x12
#define LED3_ON_H   0x13
#define LED3_OFF_L  0x14
#define LED3_OFF_H  0x15
#define LED4_ON_L   0x16
#define LED4_ON_H   0x17
#define LED4_OFF_L  0x18
#define LED4_OFF_H  0x19
#define LED5_ON_L   0x1A
#define LED5_ON_H   0x1B
#define LED5_OFF_L  0x1C
#define LED5_OFF_H  0x1D
#define LED6_ON_L   0x1E
#define LED6_ON_H   0x1F
#define LED6_OFF_L  0x20
#define LED6_OFF_H  0x21
#define LED7_ON_L   0x22
#define LED7_ON_H   0x23
#define LED7_OFF_L  0x24
#define LED7_OFF_H  0x25
#define LED8_ON_L   0x26
#define LED8_ON_H   0x27
#define LED8_OFF_L  0x28
#define LED8_OFF_H  0x29
#define LED9_ON_L   0x2A
#define LED9_ON_H   0x2B
#define LED9_OFF_L  0x2C
#define LED9_OFF_H  0x2D
#define LED10_ON_L  0x2E
#define LED10_ON_H  0x2F
#define LED10_OFF_L 0x30
#define LED10_OFF_H 0x31
#define LED11_ON_L  0x32
#define LED11_ON_H  0x33
#define LED11_OFF_L 0x34
#define LED11_OFF_H 0x35
#define LED12_ON_L  0x36
#define LED12_ON_H  0x37
#define LED12_OFF_L 0x38
#define LED12_OFF_H 0x39
#define LED13_ON_L  0x3A
#define LED13_ON_H  0x3B
#define LED13_OFF_L 0x3C
#define LED13_OFF_H 0x3D
#define LED14_ON_L  0x3E
#define LED14_ON_H  0x3F
#define LED14_OFF_L 0x40
#define LED14_OFF_H 0x41
#define LED15_ON_L  0x42
#define LED15_ON_H  0x43
#define LED15_OFF_L 0x44
#define LED15_OFF_H 0x45

#define PRE_SCALE  0xFE

#define MODE1_RESTART 0x80
#define MODE1_EXTCLK  0x40
#define MODE1_AI      0x20
#define MODE1_SLEEP   0x10
#define MODE1_ALLCALL 0x01

static void void delay(int i) {
	while (i) {
		i--;
	}
}

void I2C2_Init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_initStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
	
	I2C_initStructure.I2C_ClockSpeed = 400000; // 400KHz
	I2C_initStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_initStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_initStructure.I2C_OwnAddress1 = 0x77;
	I2C_initStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_initStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C2, &I2C_initStructure);
	
	I2C_Cmd(I2C2, ENABLE);	
}

void PCA9685_WriteReg(u8 addr, u8 value) {
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C2, (PCA9685_I2C_ADDR<<1)&0xfe, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C2, addr);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, value);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C2, ENABLE);	
}

void PCA9685_ReadReg(u8 addr, u8 *value) {
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C2, (PCA9685_I2C_ADDR<<1)&0xfe, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C2, addr);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));	
	
	I2C_GenerateSTOP(I2C2, ENABLE);	
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2C2, (PCA9685_I2C_ADDR<<1)|0x01, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	I2C_AcknowledgeConfig(I2C2, DISABLE);
	
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
	*value = I2C_ReceiveData(I2C2);

	I2C_GenerateSTOP(I2C2, ENABLE);	
}

void PCA9685_SetChannelDuty(u8 channel, u32 on, u32 off) {
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C2, (PCA9685_I2C_ADDR<<1)&0xfe, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C2, LED0_ON_L+4*channel);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, on&0xff);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, (on>>8)&0xff);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, off&0xff);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_SendData(I2C2, (off>>8)&0xff);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C2, ENABLE);
}

void PCA9685_Init() {
	u8 value;
	I2C2_Init();
	
	// The PRE_SCALE register can only be set when the SLEEP bit of MODE1 register is set to logic 1.
	PCA9685_WriteReg(MODE1, MODE1_SLEEP);
	PCA9685_WriteReg(PRE_SCALE, 121); // (25000000/4096/50)-1
	PCA9685_WriteReg(MODE1, 0);
	PCA9685_WriteReg(MODE1, MODE1_RESTART|MODE1_AI|MODE1_ALLCALL);

	while (1) {
		PCA9685_ReadReg(MODE1, &value);
		if ((value&MODE1_RESTART)==0) {	// Restart OK.
			break;
		}
		delay(100000);
	}
}
