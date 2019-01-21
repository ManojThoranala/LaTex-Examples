/*
 * File:   timer.c
 * Author: ManojThoranala
 *
 * Created on 14 June, 2016, 11:36 PM
 */

#include<stdio.h>
#include<stdlib.h>
#include <xc.h>
#include <pic16f886.h>

#include "_time.h"
int m,n,a,b,t1,t2,i,temp1,temp2,temp3,x,adr;
int min,min1,sec,sec1,t,hr12,min12,min22,min11;
int hr,min2,temp,a1;
unsigned char eeprom_read(unsigned char adr);
void eeprom_write(unsigned char adr, unsigned char val);

void main(void) 
{
    
    OSCCON=0x76;
    ANSELH=0x00;
    ANSEL=0x01;
    TRISC=0x00;
    
    TRISB=0x00;
    TRISAbits.TRISA0=1;
    TRISAbits.TRISA1=1;
    TRISAbits.TRISA2=0;
   
    ADCON1=0x80;
    PORTB=0x00;
    a1=0;
    t=0;
    b=0;
    i=0;
    hr=0;
    min1=0;
    min2=0;
    sec=0;
    sec1=0;
    n=0;
   
    while(1)
    {
        n++;
        if(n<2260)
        {
            n=0;
        }
        //send_seg(hr,min1,min2);
        if(PORTAbits.RA1==1)
        {
            b=5;
        }
        if(b==5)
        {
            if(PORTAbits.RA1==0)
            {
                i++;
                b=0;
            }
            if(i>4)
            {
                i=0;
            }
            
            }
        if(i==1)
        {  adr=0x06;
           hr=eeprom_read(adr);
           min1=eeprom_read(adr+16);
           min2=eeprom_read(adr+16);
           __delay_ms(1);
           send_seg(hr,min1,min2);
        }
        
          if(i==2)
        {  adr=0x06+32;
           hr=eeprom_read(adr);
           min1=eeprom_read(adr+16);
           min2=eeprom_read(adr+16);
           __delay_ms(1);
           send_seg(hr,min1,min2);
        }
        
          if(i==3)
        { adr=0x06+64;
           hr=eeprom_read(adr);
           min1=eeprom_read(adr+16);
           min2=eeprom_read(adr+16); 
           __delay_ms(1);
           send_seg(hr,min1,min2);
        }
        ADCON0=0x41;
        __delay_ms(5);
        ADCON0bits.GO=1;
        while(ADCON0bits.nDONE==1);
        temp1 = ADRESL;
        temp2 = ADRESH;
        temp2=(temp2*256)+temp1;
     
        if(t==0)
        {
            temp3=temp2;
        }
        t++;
        if((t>1)&(t<8))
        {
         if(temp2<temp3)
         {
             x++;
             OPTION_REG=0x87;
      while(INTCONbits.TMR0IF==0);
      temp++;
      if(temp==4)
      {a++;
      temp=0;
           } 
      if(a>59)
      {min++;
      a=0;
      }
    
    if(min>59)
    {
     hr++;
     min=0;
    }

min1=(min%100)/10;
min2=(min%10);
   send_seg(hr,min1,min2);
  PORTAbits.RA2=0;
           PORTCbits.RC4=0;
           PORTCbits.RC3=1; 
           PORTCbits.RC2=1;
           PORTCbits.RC1=1;
           PORTCbits.RC0=1;
           if((n>500)&(n<1000))
           {PORTCbits.RC3=0;}
           if((n>1001)&(n<1500))
           {PORTCbits.RC2=0;}
           if((n>1501)&(n<2000))
           {PORTCbits.RC1=0;}
           if((n>2001)&(n<2250))
           {PORTCbits.RC0=0;}
           
           temp3=temp2;
         }
         else if(temp2>temp3)
         {
             if(x==1) 
        {
           adr=0x06;    
           __delay_ms(1);
        eeprom_write(adr,hr);
        eeprom_write(adr+16,min1);
        eeprom_write(adr+16,min2);
          __delay_ms(1);
             }
             if(x==2)
             {  adr=0x06+32;
             __delay_ms(1);
                eeprom_write(adr+16,hr);
                eeprom_write(adr+16,min1);
                eeprom_write(adr+16,min2); 
                __delay_ms(1);
             }
             if(x==3)
             {
                 adr=0x06+64;
                 __delay_ms(1);
                eeprom_write(adr+16,hr);
                eeprom_write(adr+16,min1);
                eeprom_write(adr+16,min2);
                __delay_ms(1);
             }
              OPTION_REG=0x87;
      while(INTCONbits.TMR0IF==0);
      temp++;
      if(temp==4)
      {a1++;
      temp=0;
           } 
      if(a1>59)
      {min11++;
      a1=0;
      }
    
    if(min11>59)
    {
     hr12++;
     min11=0;
    }
      if(hr12==23)
      {  
       PORTAbits.RA2=1;
       __delay_ms(50);
       PORTAbits.RA2=0;
      }
      PORTAbits.RA2=0;
           PORTCbits.RC4=0;
           PORTCbits.RC3=0; 
           PORTCbits.RC2=0;
           PORTCbits.RC1=0;
           PORTCbits.RC0=0;
           PORTCbits.RC0=1; 
           if((n>500)&(n<1000))       
           {PORTCbits.RC1=1;}
           if((n>1001)&(n<1500))
           {PORTCbits.RC2=1;} 
           if((n>1501)&(n<2000))
           {PORTCbits.RC3=1;}
           temp3=temp2;
         }
         else if((temp3==temp2)|(temp3+1==temp2)|(temp3-1==temp2)|(temp3-2==temp2)|(temp3+2==temp2))
         {
             
          
                 if(temp2>774)
             { 
                     PORTAbits.RA2=0;
                 PORTCbits.RC4=0;
                 PORTCbits.RC3=1; 
                 PORTCbits.RC2=1;
                 PORTCbits.RC1=1;
                 PORTCbits.RC0=1;

            }
             else if((temp2>715)&(temp2<774))
             {
                 PORTAbits.RA2=0;
                PORTCbits.RC2=1;
                PORTCbits.RC1=1;
                PORTCbits.RC0=1;
                PORTCbits.RC4=0;
                 PORTCbits.RC3=0;
             }
             else if((temp2>657)&(temp2<715))
             {
                 PORTAbits.RA2=0;
                 PORTCbits.RC1=1;
                 PORTCbits.RC0=1;
                 PORTCbits.RC4=0;
                 PORTCbits.RC3=0; 
                 PORTCbits.RC2=0;
              
             } 
               else if((temp2>600)&(temp2<657))
             { 
                   if(temp2<632)
               {
                       PORTAbits.RA2=0;
               	 PORTCbits.RC4=1;
                 PORTCbits.RC0=1; 
                 PORTCbits.RC3=0; 
                 PORTCbits.RC2=0;
                 PORTCbits.RC1=0;
                }
                 PORTAbits.RA2=0;
                 PORTCbits.RC4=1;  
                 PORTCbits.RC0=1; 
                 PORTCbits.RC3=0; 
                 PORTCbits.RC2=0;
                 PORTCbits.RC1=0;
             } 
          
                 temp3=temp2;
         }
        

       
     }

        if(t>8)
        {
            t=0;
        }
    if(temp2<574)
    {
        PORTAbits.RA2=1;
        PORTCbits.RC4=1;  
        PORTCbits.RC0=0; 
        PORTCbits.RC3=0; 
        PORTCbits.RC2=0;
        PORTCbits.RC1=0;
    }
        
           
    }    

    }
