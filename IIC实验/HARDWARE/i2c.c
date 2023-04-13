#include "i2c.h"

 /**
  * @brief  I2C初始化配置
  * @param  无
  * @retval	无
  */
void I2C_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure;
	
	/* 开启SCL和SDA时钟 */
	RCC_APB1PeriphClockCmd(SCL_PORT_CLK | SDA_PORT_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(I2Cx_CLK, ENABLE);
	
	/* 配置SCL对应的GPIO */
	GPIO_InitStructure.GPIO_Pin = SCL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SCL_GPIO_PORT, &GPIO_InitStructure);
	
	/* 配置SDA对应的GPIO */
	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SDA_GPIO_PORT, &GPIO_InitStructure);
	
	/* 配置I2C */
	I2C_InitStructure.I2C_ClockSpeed = I2C_CLK_SPEED;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = STM32_ADDR;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2Cx, &I2C_InitStructure);
	I2C_Cmd(I2Cx, ENABLE);
}


 /**
  * @brief  软件模拟EEPROM字节写入
  * @param  addr:要写入数据的地址
			data:要写入的数据
  * @retval	无
  */
void EEPROM_ByteWrite(uint8_t addr, uint8_t data)
{
	/* 产生起始信号 */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* 检测EV5事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	
	/* 发送7位从机地址 */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Transmitter);
	/* 检测EV6事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS );
	
	/* 发送要写入数据的地址 */
	I2C_SendData(I2Cx, addr);
	/* 检测EV8事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS );
	
	/* 发送要写入的数据 */
	I2C_SendData(I2Cx, data);
	/* 检测EV8_2事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS );
	
	/* 产生停止信号 */
	I2C_GenerateSTOP(I2Cx, ENABLE);	
	/* 重新使能ACK */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
}


/**
  * @brief  软件模拟EEPROM页写入
  * @param  addr:要写入数据的地址
			*data:容器首地址
			num:数据个数
  * @retval	无
  */
void EEPROM_PageWrite(uint8_t addr, uint8_t *data, uint8_t num)
{
	/* 产生起始信号 */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* 检测EV5事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	
	/* 发送7位从机地址 */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Transmitter);
	/* 检测EV6事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS );
	
	/* 发送要写入数据的地址 */
	I2C_SendData(I2Cx, addr);
	/* 检测EV8事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS );
	
	while(num--)
	{
		/* 发送要写入的数据 */
		I2C_SendData(I2Cx, *data);
		/* 检测EV8_2事件 */
		while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS );
		data++;
	}
	
	/* 产生停止信号 */
	I2C_GenerateSTOP(I2Cx, ENABLE);	
	/* 重新使能ACK */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
}


 /**
  * @brief  软件模拟EEPROM随机读取
  * @param  addr:要读取数据的地址
			*data:要接收数据的容器
  * @retval	无
  */
void EEPROM_RandomRead(uint8_t addr, uint8_t* data)
{
	/* 产生第一次起始信号 */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* 检测EV5事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	/* 发送7位从机地址 */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Transmitter);
	/* 检测EV6事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) != SUCCESS );
	/* 发送要读取数据的地址 */
	I2C_SendData(I2Cx, addr);
	/* 检测EV8事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS );
	
	/* 产生第二次起始信号 */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* 检测EV5事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	/* 发送7位从机地址 */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Receiver);
	/* 检测EV6事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS );
	
	/* 检测EV7事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS );
	/* 读取数据寄存器中的数据 */
	*data = I2C_ReceiveData(I2Cx);
	
	/* 产生停止信号 */
	I2C_GenerateSTOP(I2Cx, ENABLE);
	/* 重新使能ACK */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);	
}


 /**
  * @brief  软件模拟EEPROM连续读取
  * @param  addr:要读取数据的地址
			*data:要接收数据的容器
			num:数据个数
  * @retval	无
  */
void EEPROM_SeqRead(uint8_t addr, uint8_t* data, uint8_t num)
{
	/* 产生第一次起始信号 */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* 检测EV5事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	/* 发送7位从机地址 */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Transmitter);
	/* 检测EV6事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) != SUCCESS );
	/* 发送要读取数据的地址 */
	I2C_SendData(I2Cx, addr);
	/* 检测EV8事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS );
	
	/* 产生第二次起始信号 */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* 检测EV5事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	/* 发送7位从机地址 */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Receiver);
	/* 检测EV6事件 */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS );
	
	while(num--)
	{
		/* 检测EV7事件 */
		while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS );
		/* 读取数据寄存器中的数据 */
		*data = I2C_ReceiveData(I2Cx);
		data++;
	}
	
	/* 产生停止信号 */
	I2C_GenerateSTOP(I2Cx, ENABLE);
	/* 重新使能ACK */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);	
}


 /**
  * @brief  等待EEPROM写入完成
  * @param  无
  * @retval	无
  */
void EEPROM_WaitForWriteEnd(void)
{
	do{
		I2C_GenerateSTART(I2Cx, ENABLE);
		while( I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB) == RESET );
		/* EV5事件被检测到，发送设备地址 */
		I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Transmitter);
	}while( I2C_GetFlagStatus(I2Cx, I2C_FLAG_ADDR) == RESET );

	/* EEPROM内部时序完成传输完成 */
	I2C_GenerateSTOP(I2Cx, ENABLE);	
}

