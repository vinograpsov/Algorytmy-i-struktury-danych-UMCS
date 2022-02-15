#include <8051.h>

#define FALSE 0
#define TRUE 1

unsigned char PRESS = 0; 

__sbit __at (0x96) SEG_OFF;
__sbit __at (0x97) TLED;
__sbit __at (0xB5) KBD;


__xdata unsigned char * CS55B = (__xdata unsigned char *) 0xFF29;
__xdata unsigned char * CS55D = (__xdata unsigned char *) 0xFF2B;
__xdata unsigned char * CSKB0 = (__xdata unsigned char *) 0xFF21;	//klawisze 0...7
__xdata unsigned char * CSKB1 = (__xdata unsigned char *) 0xFF22;	//klawisze 8...

__xdata unsigned char * LCDWC = (__xdata unsigned char *) 0xFF80;  
__xdata unsigned char * LCDWD = (__xdata unsigned char *) 0xFF81;  
__xdata unsigned char * LCDRC = (__xdata unsigned char *) 0xFF82; 

__xdata unsigned char * CSDS = (__xdata unsigned char *) 0xFF30;



void lcd_init();
void lcd_wait_while_busy();
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_chage(unsigned char state);
void keybord(unsigned char *num_state);
void pwm();
void mul_keybord();
void to_char(int percent2);
void from_char();
void trans();

unsigned char MUL[6] = { 0b000001, 0b000010, 0b000100, 0b001000, 0b010000, 0b100000 };

__code unsigned char state[] = {'1','.',' ','C','H','A','N','G','E',' ','S','T','A','T','E', '\0'};
__code unsigned char settings[] = {'2','.',' ','S','E','T','T','I','N','G','S', '\0'};
__code unsigned char start[] = {'1','.','1',' ','S','T','A','R','T','\0'};
__code unsigned char stop[] = {'1','.','2',' ','S','T','O','P','\0'};
__code unsigned char pwn_line[] = {'2','.','2',' ','P','W','M', '\0'};
__code unsigned char reset[] = {'2','.','2',' ','R','E','S','E','T', '\0'};

__code unsigned char sel_state[] = {'>','1','.',' ','C','H','A','N','G','E',' ','S','T','A','T','E', '\0'};
__code unsigned char sel_settings[] = {'>','2','.',' ','S','E','T','T','I','N','G','S', '\0'};
__code unsigned char sel_start[] = {'>','1','.','1',' ','S','T','A','R','T','\0'};
__code unsigned char sel_stop[] = {'>','1','.','2',' ','S','T','O','P','\0'};
__code unsigned char sel_pwn_line[] = {'>','2','.','2',' ','P','W','M', '\0'};
__code unsigned char sel_reset[] = {'>','2','.','2',' ','R','E','S','E','T', '\0'};
unsigned char pwn030[] = {'>','2','.','1','.','1',' ','0','3','0','\0'};

float percent = 30;
int temp1,temp2,temp3,temp7;


int const tmpLOW = 18432 * 0.03;
int const tmpHIGH = 18432 - 18432 * 0.03;

int LOW;
int HIGH;
unsigned int min_b = 30;
unsigned int max_b = 750;


int TH0_LOW = (47104+tmpLOW)/256;
int TL0_LOW = (47104+tmpLOW)%256;

int TH0_HIGH = (47104+tmpHIGH)/256;
int TL0_HIGH =  (47104+tmpHIGH)%256;

__sbit __at (0x19) t0_flag; // kawo

int temp4,temp5,temp6;


unsigned char rec_index = 0;
unsigned char rec_buf[4];


__sbit __at (0x23) rec_flag;


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
	TMOD = 1 ;
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


void t0_int( void ) __interrupt( 1 ) // pwm
{
    t0_flag = !t0_flag;
    
    TF0=0;
    if(t0_flag)
    {
    	*(CS55B) = 0xFF;
		TLED = 0;
		
		TL0 = TL0_HIGH;
		TH0 = TH0_HIGH;
	}
    else
    {
        *(CS55B) = 0x00;
        TLED = 1;
        
		TL0 = TL0_LOW;
		TH0 = TH0_LOW;
    }
}



void main(){

	unsigned char num_state = 1;

	lcd_chage(num_state);
	// lcd_init();
	init();
	pwm();
	while (1)
	{
		if(rec_flag){
			if(rec_index == 3){
				from_char();
				rec_index = 0;
			}
            rec_flag = 0;
		}
		keybord(&num_state);
	}
}



void pwm(){
	// TMOD = 1;

    ET0=1;
    EA=1;

    TF0=0;
    TR0=1;

    *(CS55D) = 0x80;
}



void keybord(unsigned char *num_state){
	unsigned char i = 0; 
    unsigned char key = *CSKB1;		
	unsigned char key2 = 0b000000;
 		
	for (i = 0; i < 6; ++i){
     	*CSDS = MUL[i];
		if (KBD == 1){
			key2 = MUL[i];
			break;
		}
	}

	if(key == 0b11111111 && key2 == 0b000000 && PRESS == 1){
		PRESS = 0;
	}

	else if (PRESS == 0){
		//ENTER
		
		if(key2 == MUL[0]){
			TLED = !TLED;
			PRESS = 1;
		}
       	if(key == 0b01111111 ){
    		PRESS = 1;
			if(*num_state == 1){
				*num_state = 11;
				lcd_chage(*num_state);
			}
			else if(*num_state == 2){
				*num_state = 21;
				lcd_chage(*num_state);
				
			}
			else if (*num_state ==11){ // tr0 
				TR0=1;
			}
			else if(*num_state ==12){
    			TR0=0;
			}
			else if(*num_state ==21){
				*num_state = 211;
				lcd_chage(*num_state);
			}
			else if(*num_state ==22){
				percent = 30;
				
				LOW = 18432 * percent/1000;
				HIGH = 18432 - LOW;

				TH0_LOW = (47104+LOW)/256;
				TL0_LOW = (47104+LOW)%256;

			 	TH0_HIGH = (47104+HIGH)/256;
			 	TL0_HIGH =  (47104+HIGH)%256;

				to_char(percent); 
			}

		}
		//LEFT
        
		if(key2 == MUL[5]){
        	if (percent - 10 >= min_b){
				percent -= 10;
				
				LOW = 18432 * percent/1000;
				HIGH = 18432 - LOW;

				TH0_LOW = (47104+LOW)/256;
				TL0_LOW = (47104+LOW)%256;

			 	TH0_HIGH = (47104+HIGH)/256;
			 	TL0_HIGH =  (47104+HIGH)%256;

				to_char(percent);
				if(*num_state == 211){
					lcd_chage(*num_state);
				}
			}
        	PRESS = 1;
        }
		
		//RIGHT
		
		if(key2 == MUL[2]){
    		if (percent + 10 <= max_b){
				percent += 10;
				
				LOW = 18432 * percent/1000;
				HIGH = 18432 - LOW;

				TH0_LOW = (47104+LOW)/256;
				TL0_LOW = (47104+LOW)%256;

			 	TH0_HIGH = (47104+HIGH)/256;
			 	TL0_HIGH =  (47104+HIGH)%256;

				to_char(percent);
				if(*num_state == 211){
					lcd_chage(*num_state);
				}
			}
    		PRESS = 1;
    	}
		//UP

		if(key2 == MUL[3]){
        	if (percent + 1 <= max_b){
				percent += 1;
				
				LOW = 18432 * percent/1000;
				HIGH = 18432 - LOW;

				TH0_LOW = (47104+LOW)/256;
				TL0_LOW = (47104+LOW)%256;

			 	TH0_HIGH = (47104+HIGH)/256;
			 	TL0_HIGH =  (47104+HIGH)%256;

				to_char(percent);
				if(*num_state == 211){
					lcd_chage(*num_state);
				}
			}
        	PRESS = 1;
        }

       	if(key == 0b11101111 ){
    		PRESS = 1;
			if(*num_state == 1){
				*num_state = 2;
				lcd_chage(*num_state);
				
			}
			else if(*num_state == 2){
				*num_state = 1;
				lcd_chage(*num_state);
				
			}
			else if (*num_state ==11){
				*num_state = 12;
				lcd_chage(*num_state);
				
			}
			else if(*num_state ==12){
				*num_state = 11;
				lcd_chage(*num_state);
				
			}
			else if(*num_state ==21){
				*num_state = 22;
				lcd_chage(*num_state);
				
			}
			else if(*num_state ==22){
				*num_state = 21;
				lcd_chage(*num_state);
				
			}	
    	}
		//DOWN
		
		if(key2 == MUL[4]){
			if (percent - 1 >= min_b){
				percent -= 1;
				
				LOW = 18432 * percent/1000;
				HIGH = 18432 - LOW;

				TH0_LOW = (47104+LOW)/256;
				TL0_LOW = (47104+LOW)%256;

			 	TH0_HIGH = (47104+HIGH)/256;
			 	TL0_HIGH =  (47104+HIGH)%256;

				to_char(percent);
				if(*num_state == 211){
					lcd_chage(*num_state);
				}
			}
			PRESS = 1;
        }

    	if(key == 0b11011111 ){
    		PRESS = 1;
			if(*num_state == 1){
				*num_state = 2;
				lcd_chage(*num_state);
				
			}
			else if(*num_state == 2){
				*num_state = 1;
				lcd_chage(*num_state);
				
			}
			else if (*num_state ==11){
				*num_state = 12;
				lcd_chage(*num_state);
				
			}
			else if(*num_state ==12){
				*num_state = 11;
				lcd_chage(*num_state);
				
			}
			else if(*num_state ==21){
				*num_state = 22;
				lcd_chage(*num_state);
				
			}
			else if(*num_state ==22){
				*num_state = 21;
				lcd_chage(*num_state);
				
			}
    	}
		//ESC
		if(key2 == MUL[1]){
			TLED = !TLED;
        	PRESS = 1;
		}
        if(key == 0b10111111){
			PRESS = 1;
			if(*num_state == 1){
				
			}
			else if(*num_state == 2){
				
			}
			else if (*num_state ==11){
				*num_state = 1;
				lcd_chage(*num_state);
				
			}
			else if(*num_state ==12){
				*num_state = 1;
				lcd_chage(*num_state);
				
			}
			else if(*num_state ==21){
				*num_state = 2;
				lcd_chage(*num_state);
				
			}
			else if(*num_state ==22){
				*num_state = 2;
				lcd_chage(*num_state);
				
			}
			else if (*num_state == 211){
				*num_state = 21;
				lcd_chage(*num_state);
			}
		}
	}                                 
}









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


void lcd_chage(unsigned char num_state){
    if(num_state == 1){
	    unsigned char i = 0;
    
	    lcd_init();
    
    
	    for(i = 0; i < sel_state[i] != '\0'; ++i){
	    	lcd_data(sel_state[i]);
	    }
    
	    lcd_cmd(0b11000000);
    
	    for(i = 0; i < settings[i] != '\0'; ++i){
	    	lcd_data(settings[i]);
	    }
    }
    if(num_state == 2){
        unsigned char i = 0;
    
	    lcd_init();
    
    
	    for(i = 0; i < state[i] != '\0'; ++i){
	    	lcd_data(state[i]);
	    }
        
    
	    lcd_cmd(0b11000000);
    
	    for(i = 0; i < sel_settings[i] != '\0'; ++i){
	    	lcd_data(sel_settings[i]);
	    }
    }
    if(num_state == 11){
        unsigned char i = 0;
    
	    lcd_init();
    
    
	    for(i = 0; i < sel_start[i] != '\0'; ++i){
	    	lcd_data(sel_start[i]);
	    }
    
	    lcd_cmd(0b11000000);
    
	    for(i = 0; i < stop[i] != '\0'; ++i){
	    	lcd_data(stop[i]);
	    }
    }
    if(num_state == 12){
        unsigned char i = 0;
    
	    lcd_init();
    
    
	    for(i = 0; i < start[i] != '\0'; ++i){
	    	lcd_data(start[i]);
	    }
    
	    lcd_cmd(0b11000000);
    
	    for(i = 0; i < sel_stop[i] != '\0'; ++i){
	    	lcd_data(sel_stop[i]);
	    }
    }
    if(num_state == 21){
        unsigned char i = 0;
    
	    lcd_init();
    
    
	    for(i = 0; i < sel_pwn_line[i] != '\0'; ++i){
	    	lcd_data(sel_pwn_line[i]);
	    }
    
	    lcd_cmd(0b11000000);
    
	    for(i = 0; i < reset[i] != '\0'; ++i){
	    	lcd_data(reset[i]);
	    }        
    }
    if(num_state == 22){
        unsigned char i = 0;
    
	    lcd_init();
    
    
	    for(i = 0; i < pwn_line[i] != '\0'; ++i){
	    	lcd_data(pwn_line[i]);
	    }
    
	    lcd_cmd(0b11000000);
    
	    for(i = 0; i < sel_reset[i] != '\0'; ++i){
	    	lcd_data(sel_reset[i]);
	    }    
    }
	if (num_state == 211){
		unsigned char i = 0;
		lcd_init();
		for(i = 0; i < pwn030[i] != '\0'; ++i){
	    	lcd_data(pwn030[i]);
	    }
    
	    lcd_cmd(0b11000000);
	}
}

void to_char(int percent2){
	temp3 = percent2 % 10;
	temp2 = ((percent2 - temp3) % 100) / 10;
	temp1 = ((percent2 - temp3 - temp2) / 100);

	pwn030[7] = temp1 + 48;
	pwn030[8] = temp2 + 48 ;
	pwn030[9] = temp3 + 48;
}

void from_char(){
	unsigned int number1 = rec_buf[0] - 48;
	unsigned int number2 = rec_buf[1] - 48;
	unsigned int number3 = rec_buf[2] - 48;
	unsigned char i = 0;
	unsigned int number4 = number1 * 100 + number2 * 10 + number3;

	rec_index = 0;

	if(number4 <= max_b && number4 >= min_b){
		percent = number4;
		
		LOW = 18432 * percent/1000;
		HIGH = 18432 - LOW;

		TH0_LOW = (47104+LOW)/256;
		TL0_LOW = (47104+LOW)%256;
		
		TH0_HIGH = (47104+HIGH)/256;
		TL0_HIGH =  (47104+HIGH)%256;
		to_char(percent);

			rec_buf[3] = '\0';

	// 		for(i = 0; i < rec_buf[i] != '\0'; ++i){
	// 	lcd_data(rec_buf[i]);
	// }
	
	// lcd_cmd(0b11000000);
	}
}
