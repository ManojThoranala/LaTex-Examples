/*
 * File:   sinemeasure.c
 * Author: ManojThoranala
 *
 * Created on 9 August, 2016, 4:46 PM
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include "sm.h"
int r,z,i,m,n,d,s,x,y,vria,vrib,vric,vroa,vrob,vroc;
unsigned long t2,t1; 
unsigned long max,min;
unsigned int v;
char R[4],VRIA[2],VRIB[2],VRIC[2],VROA[2],VROB[2],VROC[2],T[4],M[4];
unsigned int t[40];
unsigned long read_adc(int channel);

void main() 
{
     OSCCON=0x68;
    ANSELB=0x00;
    ANSELA=0X2F;
    ANSELC=0X3C;
    ANSELD=0X1F;
    TRISB=0;
    TRISA=0X2F;
    TRISC=0XBE;
    TRISD=0X3F;
    ADCON1=0x94;
    ADCON0=0x00;
    
    L_I();
    L_Clr();
    L_S_C(1,1);
    L_W_S("Hello");
    
    while(1)
    {r++;
    if(r>16)
    {r=0;}
    x=0;
    y=0;
    s=0;
    
 for(i=0; i<=39; i++)
 {LATBbits.LATB0=1;
 v= read_adc(1); //Digital value convert
 t[i]=v;
 }
    LATBbits.LATB0=0; 
 ADCON0bits.ADON=0;
 max=t[0];
 min=t[0];
 for(i=0; i<=39; i++)
 {
 if(max<t[i])
 {max=t[i];
 x=i;}
 if(t[i]==580)
 y=i;
 }
// if(min>t[i])
// {min=t[i];
// y=i;}
 
 if(x>y)
 {d=y;
     z=(x-y);}
 if(x<y)
 {d=x;
 z=(y-x);}
    for(i=d;i<z;i++) 
    {
    t1=abs(t[i]-508);
    t2=t2+t1;

    }
//    LATBbits.LATB1=0;    
 if(t2!=0)
 {
	t2=t2/z;
	n=(t2); }
	vria= (n%1000)/100;
	vrib= (n%100)/10;
	vric= (n%10);
	vroa= (max%1000)/100;
	vrob= (max%100)/10;
	vroc= (max%10);
	itoa(VRIA,vria,10);
	itoa(VRIB,vrib,10);
	itoa(VRIC,vric,10);
	itoa(VROA,vroa,10);
	itoa(VROB,vrob,10);
	itoa(VROC,vroc,10);
	itoa(T,x,10);
	itoa(M,y,10);
	itoa(R,s,10);
	L_S_C(2,1); 
	L_W_S(VRIA);
	L_S_C(2,2); 
	L_W_S(VRIB);
	L_S_C(2,3); 
	L_W_S(VRIC);
	L_S_C(2,10); 
	L_W_S(VROA);
	L_S_C(2,11); 
	L_W_S(VROB);
	L_S_C(2,12); 
	L_W_S(VROC);
	L_S_C(1,5);
	L_W_S(T);
	L_S_C(1,8);
	L_W_S(M);
	L_S_C(1,11);
	L_W_S(R);
	for(i=0;i<39;i++)
	{itoa(T,t[i],10);
	   L_S_C(2,10);
	   L_W_S(T);
	__delay_ms(2000);}
	__delay_ms(50);
	}
}
        




unsigned long read_adc(int channel)
{
     ADCON0 = channel;
              __delay_us(150);
              ADCON0bits.GO_nDONE=1;
              while(ADCON0bits.GO_nDONE == 1);
              t1=ADRESL;
              t2=ADRESH;
              t2=(t2<<8)+t1;
              return t2;
}

