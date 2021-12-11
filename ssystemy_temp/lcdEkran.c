#include <8051.h>

__xdata unsigned char * LCDRC = (__xdata unsigned char *) 0xFF82;  // 0x = h
__xdata unsigned char * LCDWC = (__xdata unsigned char *) 0xFF80;  
__xdata unsigned char * LCDRD = (__xdata unsigned char *) 0xFF83; 
__xdata unsigned char * LCDWD = (__xdata unsigned char *) 0xFF81;  

void LCD_INIT();
void LCD_CMD_R7(unsigned char r7);
void LCD_DATA_R7(unsigned char r7);
void LCD_WAIT();

void LCD_WAIT(){
    while (*LCDRC && 255); // ???
}
void LCD_CMD_R7(unsigned char r7){
    LCD_WAIT();
    *LCDWC = r7;
}
void LCD_DATA_R7(unsigned char r7){
    LCD_WAIT();
    *LCDWD = r7;
}
void INIT(){
    LCD_CMD_R7(0b00111000);
    LCD_CMD_R7(0b00011100);
    LCD_CMD_R7(0b00000111);
    LCD_CMD_R7(1);
}


void main(){
   // while (1)
    //{
     //   LCD_INIT();
    //}
    INIT();
    LCD_WAIT();
    while(1){}
}
