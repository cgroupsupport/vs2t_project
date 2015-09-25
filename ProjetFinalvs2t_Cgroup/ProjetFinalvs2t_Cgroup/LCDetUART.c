/*---------------------------------------------------------------------------*/
/**
 * \file LCDetUART.c
 * \date 25/09/2015
 * \authors : C group, équipe surveillance
 * \copyright 	C group : Secuity Department
 * 
 * Composant : CY8C29466-24PXI
 * Réglage Pixymon : Arduini ICSP SPI
 *
 * Affichage et envoi des infomartions de Pixy
 */
/*----------------------------------------------------------------------------*/

#include "LCDetUART.h"
#include "capteur.h"

void printRS232(void){
	
	int i, j;
    char buf[128], sig[6], d;
	int flag;
		
    if (BlockCam.signature>PIXY_MAX_SIGNATURE) // color code! (CC)
	{
      // convert signature number to an octal string
      for (i=12, j=0, flag=0; i>=0; i-=3)
      {
        d = (BlockCam.signature>>i)&0x07;
        if (d>0 && !flag){
          flag = 1;
		}
        if (flag){
          sig[j++] = d + '0';
      	}
	 }
      sig[j] = '\0';
	  UART_1_CPutString("C");
	  UART_1_PutSHexInt(BlockCam.signature);
	  UART_1_CPutString("x");
	  UART_1_PutSHexInt(BlockCam.x);
	  UART_1_CPutString("y");
	  UART_1_PutSHexInt(BlockCam.y);
	  UART_1_CPutString("w");
	  UART_1_PutSHexInt(BlockCam.width);
	  UART_1_CPutString("h");
	  UART_1_PutSHexInt(BlockCam.height);
	  UART_1_CPutString("a");
	  UART_1_PutSHexInt(BlockCam.angle);
    }			
	else{ // regular BlockCam.  Note, angle is always zero, so no need to print
	  UART_1_CPutString("s");
	  UART_1_PutSHexInt(BlockCam.signature);
	  UART_1_CPutString("x");
	  UART_1_PutSHexInt(BlockCam.x);
	  UART_1_CPutString("y");
	  UART_1_PutSHexInt(BlockCam.y);
	  UART_1_CPutString("w");
	  UART_1_PutSHexInt(BlockCam.width);
	  UART_1_CPutString("h");
	  UART_1_PutSHexInt(BlockCam.height);
	  UART_1_CPutString("a");
	  UART_1_PutSHexInt(BlockCam.angle);
	}
	
}


 void printCoor(void )
  {
    int i, j;
    char buf[128], sig[6], d;
	int flag;
	const char * stringHexToUart;
	
	char C[]="C";
	char s[]="s";
	char x[]="x";
	char y[]="y";
	char w[]="w";
	char h[]="h";
	char a[] ="a";
		
    if (BlockCam.signature>PIXY_MAX_SIGNATURE) // color code! (CC)
	{
      // convert signature number to an octal string
      for (i=12, j=0, flag=0; i>=0; i-=3)
      {
        d = (BlockCam.signature>>i)&0x07;
        if (d>0 && !flag){
          flag = 1;
		}
        if (flag){
          sig[j++] = d + '0';
      	}
	 }
      sig[j] = '\0';
	  LCD_1_Position(0,0);
	  LCD_1_PrString(C);
	  LCD_1_PrHexInt(BlockCam.signature);
	  LCD_1_PrString(x);
	  LCD_1_PrHexInt(BlockCam.x);
	  LCD_1_PrString(y);
	  LCD_1_PrHexInt(BlockCam.y);
	  LCD_1_Position(1,0);
	  LCD_1_PrString(w);
	  LCD_1_PrHexInt(BlockCam.width);
	  LCD_1_PrString(h);
	  LCD_1_PrHexInt(BlockCam.height);
	  LCD_1_PrString(a);
	  LCD_1_PrHexInt(BlockCam.angle);
	  
    }			
	else{ // regular BlockCam.  Note, angle is always zero, so no need to print
	  LCD_1_Position(0,0);
	  LCD_1_PrString(s);
	  LCD_1_PrHexInt(BlockCam.signature);
	  LCD_1_PrString(x);
	  LCD_1_PrHexInt(BlockCam.x);
	  LCD_1_PrString(y);
	  LCD_1_PrHexInt(BlockCam.y);
	  LCD_1_Position(1,0);
	  LCD_1_PrString(w);
	  LCD_1_PrHexInt(BlockCam.width);
	  LCD_1_PrString(h);
	  LCD_1_PrHexInt(BlockCam.height);
	  LCD_1_PrString(a);
	  LCD_1_PrHexInt(BlockCam.angle);
	}
 }
