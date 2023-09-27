#include "lcd_1602.h"
 #include "time.h"

#define RS_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)
#define RS_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)

#define RW_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET)
#define RW_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET)

#define EN_W_1() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET)
#define EN_W_0() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET)

#define WRITE_DATA(data) GPIOA->ODR = data

 
// ��
void busy_check() {
	
}

// д����
void write_data(char d) {
	RS_W_1();
	RW_W_0();
	EN_W_0();
	WRITE_DATA(d);
	delay_us(1);// ���ﱣ��1us����
	EN_W_1();
	delay_us(1000); // ����ʱ��Ҫ���ó�Щ�����򲻻���ʾ����51����Щ��ͬ
	EN_W_0();
}

// д��ַ
void write_cmd(char cmd) {
	RS_W_0();
	RW_W_0();
	EN_W_0();
	WRITE_DATA(cmd);
	delay_us(1);	// ���ﱣ��1us����
	EN_W_1();
	delay_us(1000); // ����ʱ��Ҫ���ó�Щ�����򲻻���ʾ����51����Щ��ͬ
	EN_W_0();
}

void lcd_1602_init() {
	HAL_Delay(15);
	write_cmd(0x38);
	HAL_Delay(5);
	write_cmd(0x38);
	write_cmd(0x08);
	write_cmd(0x01);
	write_cmd(0x06);
	write_cmd(0x0c);
}

void show_line(char row, char col, char *string)
{
	switch(row){
		case 0:
				write_cmd(0x80+col);
				while(*string){
					write_data(*string);
					string++;
				}
				break;
		
		case 1:
				write_cmd(0x80+0x40+col);
				while(*string){
					write_data(*string);
					string++;
				}
				break;
	}
}
