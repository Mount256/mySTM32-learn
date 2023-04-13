#include "sys.h"
#include <stdio.h>
#include "1602.h" 
#include "usart.h"
#include "delay.h"
unsigned int i,j;
unsigned char temp_table[] ={"TempNow:    .  C"};
unsigned char temp_set_table[]={"MAX:70C IN:     "}; 
void zq(void);
int main(void)
{
	  delay_init();
	  GPIO_InitStructReadtempCmd();    //GPIO∂Àø⁄≈‰÷√≥ı ºªØ
	  lcd_system_reset();													  
	  for(i=0;i<16;i++) 
	  lcd_char_write(i,0,temp_table[i]);  
	  for(j=0;j<16;j++) 
	  lcd_char_write(j,1,temp_set_table[j]);
	  while(1);
}
