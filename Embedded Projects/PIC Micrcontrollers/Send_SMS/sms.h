
// PIC16F1786 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (Vcap functionality is disabled on RA6.)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)






#define _XTAL_FREQ 4000000
#define RS RB2
#define EN RB3
#define D4 RB4
#define D5 RB5
#define D6 RB6
#define D7 RB7









void L_P( char a)
{
	if(a & 1)
		D4 = 1;
	else
		D4 = 0;

	if(a & 2)
		D5 = 1;
	else
		D5 = 0;

	if(a & 4)
		D6 = 1;
	else
		D6 = 0;

	if(a & 8)
		D7 = 1;
	else
		D7 = 0;
}
void L_C( char a)
{
	RS = 0;             // => RS = 0
	L_P(a);
	EN  = 1;             // => E = 1
    __delay_ms(4);
    EN  = 0;             // => E = 0
}

void L_Clr()
{
	L_C(0);
	L_C(1);
}

void L_S_C( char a, char b)
{
	  char z,y;
      char temp;
	if(a == 1)
	{
      #pragma warning push
      #pragma warning disable 752
	  temp = 0x80+b-1;
      #pragma warning pop
	  z = temp>>4;
	  y = temp & 0x0F;
	  L_C(z);
	  L_C(y);
	}
	else if(a == 2)
	{
        #pragma warning push
        #pragma warning disable 752
		temp = 0xC0+b-1;
        #pragma warning pop
		z = temp>>4;
		y = temp & 0x0F;
		L_C(z);
		L_C(y);
	}
}

void L_I()
{
  L_P(0x00);
   __delay_ms(20);
  L_C(0x03);
	__delay_ms(5);
  L_C(0x03);
	__delay_ms(11);
  L_C(0x03);
 
  L_C(0x02);
  L_C(0x02);
  L_C(0x08);
  L_C(0x00);
  L_C(0x0C);
  L_C(0x00);
  L_C(0x06);
}

void L_W_C( char a)
{
    char y;
    char temp;
   temp = a&0x0F;
   
   y = a&0xF0;
   RS = 1;             // => RS = 1
   L_P(y>>4);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
   L_P(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}

void L_W_S( const char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   L_W_C(a[i]);
}


