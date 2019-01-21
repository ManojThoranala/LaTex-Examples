#include <xc.h>


char UART_Init()
{
	TXSTAbits.CSRC=1;
    TXSTAbits.TX9=0;
    TXSTAbits.SYNC=0;
//    TXSTAbits.=1;
    TXSTAbits.BRGH=1;
    BAUDCON=0x00;
	  SPBRG = 25;
	  SYNC = 0;
	  RCSTAbits.SPEN = 1;
     TRISCbits.TRISC7 = 1;
          TRISCbits.TRISC6=1;
       RCSTAbits.CREN= 1;
       TXSTAbits.TXEN= 1;
	}

char UART_TX_Empty()
{
  return TRMT;
}

char UART_Data_Ready()
{
   return RCIF;
}
char UART_Read()
{
 
  while(!RCIF);
  return RCREG;
}

void UART_Read_Text(char *Output, unsigned int length)
{
	unsigned int i;
	for( i=0;i<length;i++)
		Output[i] = UART_Read();
}

void UART_Write(char da)
{
  while(!TRMT);
  TXREG = da;
}

void UART_Write_Text(char *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  UART_Write(text[i]);
}

