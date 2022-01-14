#include <8051.h>
__sbit __at (0x96) P1_6;
__xdata unsigned char * CSDR = (__xdata unsigned char *) 0xFF30; 
__xdata unsigned char * CSDS = (__xdata unsigned char *) 0xFF38;


void INIT(){

P1_6 = 1;
*CSDR = 0b00111111;
*CSDS = 0b11111111;
P1_6 != P1_6;
}


void main(){
     INIT();


     while(1){
	}
}