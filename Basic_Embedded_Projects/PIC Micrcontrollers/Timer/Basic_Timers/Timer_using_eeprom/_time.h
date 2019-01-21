
// PIC16F886 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#define _XTAL_FREQ 8000000

#define cm1 RC5
#define cm2 RC6
#define cm3 RC7
unsigned char  const SEGMENT_MAP[10] = {0b01111110, 0b00001100, 0b10110110, 0b10011110, 0b11001100, 0b11011010, 0b11111010, 0b00001110, 0b11111110, 0b11001110};
                                                                                                                                                                             
                                                                                                                                                                                            
void send_seg(unsigned char hun,unsigned char ten,unsigned char digit)
 
 {
     int n=1;
   
     PORTB=0x00;
    
          
          if(n==1)
          {
          
      cm1=0;
     cm2=1;
      cm3=1;
  PORTB=SEGMENT_MAP[digit];
     n=2;
          
        __delay_ms(5);
          }  
           
      if(n==2)
      { 
       
     cm1=1;
     cm2=0;
     cm3=1;
  PORTB=SEGMENT_MAP[ten];
     n=3;
 
          __delay_ms(5);  
      }
    if(n==3)
    {  
        
         cm1=1;
        cm2=1;
       cm3=0;
    PORTB=SEGMENT_MAP[hun];
   n=1;
      
           __delay_ms(5);

          
    }
    
   }
