/*
 * File:   pulse_main.c
 * Author: ManojThoranala
 *
 * Created on 5 May, 2016, 1:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "pic12f675.h"
#include <xc.h>
#include "pulse_header.h"

void main()
{
   unsigned int t1, t2,i=0,t;
  OPTION_REG = 0X80;  
  WPU=0X00;
 OSCCAL= 0xFC;
 ANSEL=0X21;
 TRISIObits.TRISIO0=1;
 TRISIObits.TRISIO1=0;
 TRISIObits.TRISIO2=0;
 t=0;
   GPIObits.GPIO1=0;  
  __delay_ms(2000);  
    
    while(1)
    {
        
        if(i==3000 | i==0)
        {
             GPIObits.GPIO1=0;
             ADCON0 = 0x81;
              __delay_ms(1);
              ADCON0bits.GO_nDONE=1;
              while(ADCON0bits.GO_nDONE == 1);
              t1=ADRESL;
              t2=ADRESH;
              t2=(t2<<8)+t1;
              i=0;
              
        }     
              if( t2>728 )
            
             {  
                 
                  GPIObits.GPIO1=1;
                  __delay_us(5);
                   GPIObits.GPIO1=0;
                   
                  __delay_us(395);
                  
                i++;  
              }
         t++;
        if(t>20010)
        {t=0;}
        if(t<10000)
        {if( t2 >728)
              {GPIObits.GPIO2=0;}}
        if((t>10005)&(t<20000))
        {
            
        if(t2 <852)
        {GPIObits.GPIO2=1;}}
        
    }
}
