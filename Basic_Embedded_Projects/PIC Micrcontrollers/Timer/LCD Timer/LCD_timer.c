/*
 * File:   RO_timer.c
 * Author: ManojThoranala
 *
 * Created on March 16, 2016, 6:46 PM
 */



#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f1503.h>
#include "timer_lcd.h"

const int str[16] @ 0x650={0x00, 0x00};
const int str2[16] @ 0x670={0x00, 0x00};
const int str3[16] @ 0x690={0x00, 0x00};

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
 
 int m,n,s,a,t1,t2,temp,i;
int min,min1,sec,sec1;  

 min=0;
 sec=0;
 sec1=0;
 min1=0;
 a=0;
 temp=0;
 i=0;
 ADRESH=0x00;
 ADRESL=0x00;
 L_I();
 L_Clr();
 __delay_ms(3000);
 F_R_R(str,&min);
 F_R_R(str2,&min1);
 F_R_R(str3,&sec);
 m=1;
 if(min==0)
     
 {
   min=118;}
 if(sec==0)
 {
  sec=30;
 }
 while(1)
 {  
 {L_S_C(1,1);
  L_W_S("T1:");
 mnt(min,1,4,5,6);
 L_S_C(1,9);
 L_W_S(" T:");
  mnt(min1,1,12,13,14);
 L_S_C(2,1);
 L_W_S("S1:");
  snd(sec,2,4,5,6);
 L_S_C(2,8);
 L_W_S("S:");
  snd(sec1,2,10,11,12);
  } 
     
      if(m==1)
     {
time: OPTION_REG=0x84;
      while(INTCONbits.TMR0IF==0);
      temp++;
      if(temp==4)
      {a++;
      temp=0;
      if(LATCbits.LATC3==1)
      { sec1--; }
      } 
      if(a>59)
      {min1++;
      a=0;
      }
      snd(a,2,14,15,16);
      mnt(min1,1,12,13,14);
      if(LATCbits.LATC3==0)
      {if(min1==min)
      {if(a<sec)
      {LATCbits.LATC3=1;
      sec1=sec;}}}
      if(LATCbits.LATC3==1)
      {if(sec1==0)
      {LATCbits.LATC3=0;
       min1=0;
       a=0;}}
       snd(sec1,2,10,11,12);
       F_E_R(str2);
       F_W_R(str2,&min1);}
 
 
   ADCON0 = 0x0D;
   __delay_ms(5);
   ADCON0bits.GO_nDONE=1;
   while(ADCON0bits.GO_nDONE == 1);
   t1 = ADRESL;
   t2 = ADRESH;
   t2 = ((t2<<8) | t1);
   s=t2;
  
  
     
    if(s==1023)
    {n=5;}
    if(n==5)
    {if((s>843)&(s<846))
    {__delay_ms(2);
    L_I();}
    if((s>843)&(s<846))
    {m++;
    n=0;}
    if(m>4)
    {m=1;
    L_Clr();}}
    
   
    if(m==2)
    
    {L_Clr();
    a=0;}         
         
    
    if(m==3)
    {mnt(min,1,4,5,6);
     if((s<514)&(s>510)) 
    {min++;
    mnt(min,1,4,5,6);}
    if(s==328)
    {min--;
    mnt(min,1,4,5,6);}
    F_E_R(str);
  F_W_R(str,&min);
    }
     
    if(m==4)
    {snd(sec,2,4,5,6);
    if((s<514)&(s>510)) 
    {sec++;
    snd(sec,2,4,5,6);}
    if(s==328)
    {sec--;
     snd(sec,2,4,5,6);
     }
    F_E_R(str3);
    F_W_R(str3,&sec);
    }
   if(s==705)
  {if(i==0)
  {i++;
   LATCbits.LATC3=1;
  sec1=sec;
  goto time;}}
   }
}


