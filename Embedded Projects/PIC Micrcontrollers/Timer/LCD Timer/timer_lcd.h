    
// PIC16F1503 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = ON        // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)


#define _XTAL_FREQ 4000000
#define D7 RC2
#define D6 RC1
#define D5 RC0
#define D4 RA2
#define EN RA1
#define RS RA0
 
extern const int str[16],str2[16],str3[16];


void L_P(char a)
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
void L_C(char a)
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


 
void mnt(unsigned int min,char a,char b,char b1,char b2)
{ int m1,m2,m3;
char M1[2],M2[2],M3[2];
 m1=(min%1000)/100;
 m2=(min%100)/10;
 m3=(min%10);
itoa(M1,m1,10);
itoa(M2,m2,10);
itoa(M3,m3,10);
L_S_C(a,b);
L_W_S(M1);
L_S_C(a,b1);
L_W_S(M2);
L_S_C(a,b2);
L_W_S(M3);}

 void snd(int sec,char a,char b,char b1,char b2)
  {
      int bs,cs,ds;
      char BS[2],CS[2],DS[2];
      bs=(sec%1000/100);
     cs=(sec%100)/10;
     ds=(sec%10);
     itoa(BS,bs,10);
     itoa(CS,cs,10);
     itoa(DS,ds,10);
    L_S_C(a,b);
      L_W_S(BS);
     L_S_C(a,b1);
     L_W_S(CS);    
     L_S_C(a,b2);
     L_W_S(DS);    
 }

void F_E_R( const void *add)
{
    INTCONbits.GIE = 0;
    PMCON1bits.WREN = 1;
    PMCON1bits.FREE = 1;            // erasing
    PMCON1bits.CFGS = 0;            // program memory space
    PMADR = (unsigned short) add;
    PMCON2 = 0x55;
    PMCON2 = 0xAA;
    PMCON1bits.WR = 1;
    NOP();
    NOP();
    PMCON1bits.WREN = 0;
}

void F_W_R( const void *add, void *data )
{
    unsigned char i;
    INTCONbits.GIE = 0;
    PMCON1bits.WREN = 1;
    PMCON1bits.FREE = 0;            // writing
    PMCON1bits.CFGS = 0;            // program memory space
    for( i = 0; i < 16; i++ )
    {
        PMADR = (unsigned short) add + i;
        PMDAT = ((unsigned char *) data)[i];
        PMCON1bits.LWLO = i != 15;        // clear on final iteration, set otherwise
        PMCON2 = 0x55;
        PMCON2 = 0xAA;
        PMCON1bits.WR = 1;
        NOP();
        NOP();
    }
    PMCON1bits.WREN = 0;
}

void F_R_R( const void *add, void *data )
{
    unsigned char i;
    PMCON1bits.CFGS = 0;            
    for( i = 0; i < 16; i++ )
    {
        PMADR = (unsigned short) add + i;
        PMCON1bits.RD = 1;
        NOP();
        NOP();
        ((unsigned char *) data)[i] = PMDAT;
    }
} 
