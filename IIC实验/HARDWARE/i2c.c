#include "i2c.h"

 /**
  * @brief  I2C��ʼ������
  * @param  ��
  * @retval	��
  */
void I2C_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef  I2C_InitStructure;
	
	/* ����SCL��SDAʱ�� */
	RCC_APB1PeriphClockCmd(SCL_PORT_CLK | SDA_PORT_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(I2Cx_CLK, ENABLE);
	
	/* ����SCL��Ӧ��GPIO */
	GPIO_InitStructure.GPIO_Pin = SCL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SCL_GPIO_PORT, &GPIO_InitStructure);
	
	/* ����SDA��Ӧ��GPIO */
	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SDA_GPIO_PORT, &GPIO_InitStructure);
	
	/* ����I2C */
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
  * @brief  ���ģ��EEPROM�ֽ�д��
  * @param  addr:Ҫд�����ݵĵ�ַ
			data:Ҫд�������
  * @retval	��
  */
void EEPROM_ByteWrite(uint8_t addr, uint8_t data)
{
	/* ������ʼ�ź� */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* ���EV5�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	
	/* ����7λ�ӻ���ַ */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Transmitter);
	/* ���EV6�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS );
	
	/* ����Ҫд�����ݵĵ�ַ */
	I2C_SendData(I2Cx, addr);
	/* ���EV8�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS );
	
	/* ����Ҫд������� */
	I2C_SendData(I2Cx, data);
	/* ���EV8_2�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS );
	
	/* ����ֹͣ�ź� */
	I2C_GenerateSTOP(I2Cx, ENABLE);	
	/* ����ʹ��ACK */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
}


/**
  * @brief  ���ģ��EEPROMҳд��
  * @param  addr:Ҫд�����ݵĵ�ַ
			*data:�����׵�ַ
			num:���ݸ���
  * @retval	��
  */
void EEPROM_PageWrite(uint8_t addr, uint8_t *data, uint8_t num)
{
	/* ������ʼ�ź� */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* ���EV5�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	
	/* ����7λ�ӻ���ַ */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Transmitter);
	/* ���EV6�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS );
	
	/* ����Ҫд�����ݵĵ�ַ */
	I2C_SendData(I2Cx, addr);
	/* ���EV8�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS );
	
	while(num--)
	{
		/* ����Ҫд������� */
		I2C_SendData(I2Cx, *data);
		/* ���EV8_2�¼� */
		while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS );
		data++;
	}
	
	/* ����ֹͣ�ź� */
	I2C_GenerateSTOP(I2Cx, ENABLE);	
	/* ����ʹ��ACK */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
}


 /**
  * @brief  ���ģ��EEPROM�����ȡ
  * @param  addr:Ҫ��ȡ���ݵĵ�ַ
			*data:Ҫ�������ݵ�����
  * @retval	��
  */
void EEPROM_RandomRead(uint8_t addr, uint8_t* data)
{
	/* ������һ����ʼ�ź� */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* ���EV5�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	/* ����7λ�ӻ���ַ */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Transmitter);
	/* ���EV6�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) != SUCCESS );
	/* ����Ҫ��ȡ���ݵĵ�ַ */
	I2C_SendData(I2Cx, addr);
	/* ���EV8�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS );
	
	/* �����ڶ�����ʼ�ź� */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* ���EV5�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	/* ����7λ�ӻ���ַ */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Receiver);
	/* ���EV6�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS );
	
	/* ���EV7�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS );
	/* ��ȡ���ݼĴ����е����� */
	*data = I2C_ReceiveData(I2Cx);
	
	/* ����ֹͣ�ź� */
	I2C_GenerateSTOP(I2Cx, ENABLE);
	/* ����ʹ��ACK */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);	
}


 /**
  * @brief  ���ģ��EEPROM������ȡ
  * @param  addr:Ҫ��ȡ���ݵĵ�ַ
			*data:Ҫ�������ݵ�����
			num:���ݸ���
  * @retval	��
  */
void EEPROM_SeqRead(uint8_t addr, uint8_t* data, uint8_t num)
{
	/* ������һ����ʼ�ź� */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* ���EV5�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	/* ����7λ�ӻ���ַ */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Transmitter);
	/* ���EV6�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) != SUCCESS );
	/* ����Ҫ��ȡ���ݵĵ�ַ */
	I2C_SendData(I2Cx, addr);
	/* ���EV8�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS );
	
	/* �����ڶ�����ʼ�ź� */
	I2C_GenerateSTART(I2Cx, ENABLE);
	/* ���EV5�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );
	/* ����7λ�ӻ���ַ */
	I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Receiver);
	/* ���EV6�¼� */
	while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS );
	
	while(num--)
	{
		/* ���EV7�¼� */
		while( I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS );
		/* ��ȡ���ݼĴ����е����� */
		*data = I2C_ReceiveData(I2Cx);
		data++;
	}
	
	/* ����ֹͣ�ź� */
	I2C_GenerateSTOP(I2Cx, ENABLE);
	/* ����ʹ��ACK */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);	
}


 /**
  * @brief  �ȴ�EEPROMд�����
  * @param  ��
  * @retval	��
  */
void EEPROM_WaitForWriteEnd(void)
{
	do{
		I2C_GenerateSTART(I2Cx, ENABLE);
		while( I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB) == RESET );
		/* EV5�¼�����⵽�������豸��ַ */
		I2C_Send7bitAddress(I2Cx, EEPROM_ADDR, I2C_Direction_Transmitter);
	}while( I2C_GetFlagStatus(I2Cx, I2C_FLAG_ADDR) == RESET );

	/* EEPROM�ڲ�ʱ����ɴ������ */
	I2C_GenerateSTOP(I2Cx, ENABLE);	
}

