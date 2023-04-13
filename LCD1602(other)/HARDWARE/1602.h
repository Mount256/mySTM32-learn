#define      LCD1602_RS0           GPIOC->BRR  = GPIO_Pin_0//0x00000004 //低电平  
#define      LCD1602_RW0           GPIOC->BRR  = GPIO_Pin_1//0x00000010 //低电平  
#define      LCD1602_EN0           GPIOC->BRR  = GPIO_Pin_2//0x00000040 //低电平  
 						    
//============================端口位设置/清除寄存器=========================================//
#define      LCD1602_RS1           GPIOC->BSRR = GPIO_Pin_0//0x00000004 //高电平  
#define      LCD1602_RW1           GPIOC->BSRR = GPIO_Pin_1//0x00000010 //高电平  
#define      LCD1602_EN1           GPIOC->BSRR = GPIO_Pin_2 //0x00000040 //高电平  
 
#define      lcd_data_port              GPIOD->ODR//数据端口 PD0-7
void lcd_char_write(unsigned int x_pos,unsigned int y_pos,unsigned char lcd_dat);
void lcd_system_reset(void);
void lcd_command_write( unsigned char command);
void lcd_busy_wait(void);
void lcd_delay( unsigned char ms);
void GPIO_InitStructReadtempCmd(void);
