#include <8051.h>

__xdata unsigned char * LCDWC = (__xdata unsigned char *) 0xFF80;  
__xdata unsigned char * LCDWD = (__xdata unsigned char *) 0xFF81;  
__xdata unsigned char * LCDRC = (__xdata unsigned char *) 0xFF82; 


__sfr __at (0x87) PCON;
__sfr __at (0x98) SCON;
__sfr __at (0x89) TMOD;
__sfr __at (0x8D) TH1;
__sfr __at (0x8B) TL1;
__sfr __at (0x99) SBUF;
__sbit __at (0x99) TI;
__sbit __at (0x98) RI;
__sbit __at (0x8F) TF1;
__sbit __at (0x8E) TR1;
__sbit __at (0xAC) ES;
__sbit __at (0xAF) EA;
__sbit __at (0x97) TLED;


unsigned char rec_index;
unsigned char rec_buf[4];
unsigned char i;

__bit rec_flag;


void lcd_wait_while_busy(){
	while(*LCDRC & 0b10000000);
}

void lcd_cmd(unsigned char c){
	lcd_wait_while_busy();
	*LCDWC = c;
}

void lcd_data(unsigned char d){
	lcd_wait_while_busy();
	*LCDWD = d;
}

void lcd_init(){
	lcd_cmd(0b00111000);
	lcd_cmd(0b00001111);
	lcd_cmd(0b00000110);
	lcd_cmd(0b00000001);
}


void sio_int(void) __interrupt(4){
	if(!TI) {
		rec_buf[rec_index] = SBUF;
		++rec_index;
		RI = 0;
		rec_flag = 1;
	}
}

void init(){
	SCON = 0b01010000;
	TMOD &= 0b00101111;
	TMOD |= 0b00100000;
	TL1 = 0xFD;
	TH1 = 0xFD;
	PCON &= 0b01111111;
	TF1 = 0;
	TR1 = 1;
	ES = 1;
	EA = 1;
    rec_flag = 0;
	rec_index = 0;
}

void calculate(){
	unsigned char number1 = rec_buf[0] ;
	unsigned char number2 = rec_buf[1] ;
	unsigned char number3 = rec_buf[2] ;
	unsigned char result = 0;


	unsigned char num4 = number1 * 100 + number2 * 10 + number3;  	
	rec_buf[3] = '\0';
	rec_index = 0;

	

	for(i = 0; i < rec_buf[i] != '\0'; ++i){
		lcd_data(rec_buf[i]);
	}
	
	lcd_cmd(0b11000000);

}

void main(){

	unsigned char i = 0;
	
	lcd_init();
	init();
	
	
	while(1){
		if(rec_flag){
			if(rec_index == 3){
				calculate();
				rec_index = 0;
			}
            rec_flag = 0;
		}
	}
}

