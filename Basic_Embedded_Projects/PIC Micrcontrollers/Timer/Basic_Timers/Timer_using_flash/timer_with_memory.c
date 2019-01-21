 /*
 * File:   timer_with_memory.c
 * Author: ManojThoranala
 *
 * Created on March 12, 2016, 12:21 PM
 */



#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f1503.h>
#include "timer1.h"

const int str[8] @ 0x650={0x00};
//const uint16_t str2[16] @ 0x750={0x00, 0x00};
//const uint16_t str3[16] @ 0x550={0x00, 0x00};
//const uint16_t str4[16] @ 0x450={0x00,0x00};
//const uint16_t str5[16] @ 0x050={0x00,0x00};
void F_E_R( const void *add);
void F_W_R( const void *add, void *data );
 void F_R_R( const void *add, void *data ); 
 int main()
{
     
 OSCCON=0x68;
 ANSELA=0x10;
 ANSELC=0x00;
 CM1CON0=0x00;
 CM2CON0=0x00;
 CM1CON1=0x00;
 CM2CON1=0x00;
 APFCON=0x0A;
 SSP1CON1=0x00;
 PWM1CON=0X00;
 LATCbits.LATC3=0; 
 CLC2CON=0X00;
 NCO1CON=0X00;
 ADCON1=0x80;
 ADCON2=0x00;
 TRISA=0x18;
 TRISAbits.TRISA4=1;
 TRISC=0x00;  
 ANSELAbits.ANSA4=1;
 PORTAbits.RA4=1;
 INTCONbits.TMR0IF=0;
 
 int m,n,s,p,a,t1,t2,temp;
int hr,min,hr1,min1,sec;  
 m=5;
 hr=0;
 min=0;
 sec=0;
 ADRESH=0x00;
 ADRESL=0x00;
 L_I();
 L_Clr();
 __delay_ms(3000);
 F_R_R(str,&hr);
// F_R_R(str+2,&min);
// F_R_R(str+4,&sec);
// F_R_R(str+6,&hr1);
// F_R_R(str+8,&min1);
 
 while(1)
 { p++;
 if(p==100)
 {p=0;}

 {L_S_C(1,1);
  L_W_S("T1:");
  hour(hr,1,4,5);
 L_S_C(1,6);
 L_W_S(":");
  mnt(min,1,7,8);
 L_S_C(1,9);
 L_W_S(" T:");
  hour(hr1,1,12,13);
 L_S_C(1,14);
 L_W_S(":");
  mnt(min1,1,15,16);
 L_S_C(2,1);
 L_W_S("S1:");
  snd(sec,2,4,5);
 L_S_C(2,8);
 L_W_S("S:");
  snd(a,2,10,11);
  }
  
  if(s==0)
  {__delay_ms(5000);
   m=5;}
  
  
 
  
  ADCON0 = 0x0D;
   __delay_ms(5);
   ADCON0bits.GO_nDONE=1;
   while(ADCON0bits.GO_nDONE == 1);
   t1 = ADRESL;
   t2 = ADRESH;
   t2 = ((t2<<8) | t1);
   s=t2;
   
  if(m==5)
   {
   OPTION_REG=0x84;
   while(INTCONbits.TMR0IF==0);
   temp++;
   if(temp==18)
   {a++;
   temp=0;} 
   if(a>59)
   {min1++;
    a=0;
   }
   if(min1>59)
   {hr1++;
    min1=0;
  }
   
//   F_W_R(str+2,&min);
//    F_W_R(str+4,&sec);
//    F_W_R(str+6,&hr1);
//    F_W_R(str+8,&min1);
    hour(hr1,1,12,13);
    mnt(min1,1,15,16);
    snd(a,2,10,11);
    if((hr1)==(hr))
    {if((min1)==(min))
    {if(a<(sec))
    {LATCbits.LATC3=1;}
    if(a==sec)
    {LATCbits.LATC3=0;
    hr1=0;
    min1=0;}}}}
     
    if(s==1023)
    {n=5;}
    if(n==5)
    {if(s==844)
    {__delay_ms(2);}
    if(s==844)
    {m++;
    n=0;}
    if(m>5)
    {m=1;
    L_Clr();}}
    
   
    if(m==1)
    {if(p<50)
    {L_Clr();
    a=0;}}          
    
    if(m==2)
    {hour(hr,1,4,5);
    if(s==510)
    {hr++;
    if(hr>23)
    {hr=0;}
    hour(hr,1,4,5);}
    if(s==327)
    {hr--;
    if(hr<0)
    {hr=23;}
    hour(hr,1,4,5);}
    F_E_R(str);
  F_W_R(str,&hr);}
     
    if(m==3)
    {mnt(min,1,7,8);
    if(s==510) 
    {min++;
    if(min>59)
    {min=0;}
    mnt(min,1,7,8);}
    if(s==327)
    {min--;
    if(min<0)
    {min=59;}
    mnt(min,1,7,8);}
//    F_E_R(str2);
//  F_W_R(str2,&min);
    }
     
    if(m==4)
    {snd(sec,2,4,5);
    if(s==510)
    {sec++;
    if(sec>59)
    {sec=0;}
    snd(sec,2,4,5);}
    if(s==327)
    {sec--;
    if(sec<0)
    {sec=59;}
    snd(sec,2,4,5);
     }
//    F_E_R(st3);
//  F_W_R(str3,&sec);
    }
 
   }
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