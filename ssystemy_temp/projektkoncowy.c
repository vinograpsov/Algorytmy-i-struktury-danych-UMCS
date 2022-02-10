#include <8051.h>

#define FALSE 0
#define TRUE 1

unsigned char PRESS = 0; 

__sbit __at (0x96) SEG_OFF;
__sbit __at (0x97) TLED;
__sbit __at (0xB5) KBD;

__xdata unsigned char * CSKB0 = (__xdata unsigned char *) 0xFF21;	//klawisze 0...7
__xdata unsigned char * CSKB1 = (__xdata unsigned char *) 0xFF22;	//klawisze 8...
__xdata unsigned char * LCDWC = (__xdata unsigned char *) 0xFF80;  
__xdata unsigned char * LCDWD = (__xdata unsigned char *) 0xFF81;  
__xdata unsigned char * LCDRC = (__xdata unsigned char *) 0xFF82; 




void lcd_init();
void lcd_wait_while_busy();
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_chage(unsigned char state);
unsigned char mat_keybord(unsigned char num_state);



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



void main(){
	unsigned char num_state = 1;
	lcd_chage(num_state);
	while (1)
	{
		mat_keybord(num_state);
	}
	
}





 void mat_keybord(unsigned char num_state){
	unsigned char i = 0; 
    unsigned char key;//zmienna w której trzymam wciœniêty klawisz klawiatury matrycowej    
	key = *CSKB1;
	
	if(key == 0b11111111 && PRESS == 1){
		PRESS = 0;
	}
	
	else if (PRESS == 0){
		//ENTER
       	if(key == 0b01111111 ){
    		PRESS = 1;
			if(num_state == 1){
				num_state = 11;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state == 2){
				num_state = 21;
				lcd_chage(num_state);
				return num_state;
			}
			else if (num_state ==11){
				return num_state;
			}
			else if(num_state ==12){
				return num_state;
			}
			else if(num_state ==21){
				// num_state = 22; потом поменять
				// lcd_chage(num_state);
				return num_state;
			}
			else if(num_state ==22){
				return num_state;
			}
		}
		//UP
       	if(key == 0b11101111 ){
    		PRESS = 1;
			if(num_state == 1){
				num_state = 2;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state == 2){
				num_state = 1;
				lcd_chage(num_state);
				return num_state;
			}
			else if (num_state ==11){
				num_state = 12;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state ==12){
				num_state = 11;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state ==21){
				num_state = 22;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state ==22){
				num_state = 21;
				lcd_chage(num_state);
				return num_state;
			}
			
			
    	}
		//DOWN
    	if(key == 0b11011111 ){
    		PRESS = 1;
			if(num_state == 1){
				num_state = 2;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state == 2){
				num_state = 1;
				lcd_chage(num_state);
				return num_state;
			}
			else if (num_state ==11){
				num_state = 12;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state ==12){
				num_state = 11;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state ==21){
				num_state = 22;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state ==22){
				num_state = 21;
				lcd_chage(num_state);
				return num_state;
			}
    	}
		// //LEFT
   		// if(key == 0b11111011 ){
		// 	PRESS = 1;
		// }
		// //RIGHT
		// if(key == 0b11110111){
  		// 	PRESS = 1;
  		// }
		//ESC
        if(key == 0b10111111){
			PRESS = 1;
			if(num_state == 1){
				return num_state;
			}
			else if(num_state == 2){
				return num_state;
			}
			else if (num_state ==11){
				num_state = 1;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state ==12){
				num_state = 1;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state ==21){
				num_state = 2;
				lcd_chage(num_state);
				return num_state;
			}
			else if(num_state ==22){
				num_state = 2;
				lcd_chage(num_state);
				return num_state;
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
}