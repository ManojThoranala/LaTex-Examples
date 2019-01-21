/*
 * File:   sms.c
 * Author: ManojThoranala
 *
 * Created on 14 May, 2016, 5:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <xc.h>
#include<pic16f1786.h>
#include "sms.h"
#include "uart.h"
int a,b,c,d;
char B[4];
void SendSms();
void main(void)
{

OSCCON = 0x68;
ADCON1=0x81;
ANSELB=0x02;
TRISB=0x03;
TRISCbits.TRISC6=1;
TRISCbits.TRISC7=1;
L_I();
UART_Init();
L_Clr();
__delay_ms(3000);
SendSms();
L_S_C(1,1);
L_W_S("HelloWorld :)");

while(1)
{
    if(PORTBbits.RB0==1)
    {a=5;}
    if(a==5)
    {
        if(PORTBbits.RB0==0) 
        {c++;
        L_Clr();
        __delay_ms(3);}
        if(c==10)
        {c=0;
         L_I();
         L_Clr();
        }
               
         if(PORTBbits.RB0==0)
         {
             b++;
             a=0;
         }
        if(b>4)
        {b=0;}}
    itoa(B,b,10);
    L_S_C(2,1);
    L_W_S(B);
    if(b==1)
    {
        SendSms();
    }
    if(b==2)
    {
        SendSms();
        }
    if(b==3)
    {
        SendSms();
    }
    if(b==4)
    {
        SendSms();
    }        
    

}

}
void SendSms()
{
__delay_ms(2000);
UART_Write_Text("AT\r\n");   // AT command for Echo OFF
__delay_ms(1000);
UART_Write_Text("ATE0\r\n");
__delay_ms(1000);
UART_Write_Text("AT&W\r\n");
__delay_ms(1000);
UART_Write_Text("AT+CMGF=1\r\n");
UART_Write(0x0D);
__delay_ms(1000);

UART_Write_Text("AT+CNMI=1,2,0,0,0\r\n");
__delay_ms(1000);
UART_Write_Text("AT+CMGF=1\r\n");
UART_Write(0x0D);
__delay_ms(1000);
UART_Write_Text("AT+CSCS=\"GSM\"\r\n");
__delay_ms(1000);
UART_Write_Text("AT+CMGS =\"+91xxxxxxxxxx\"\r\n");
UART_Write(0x0D);
__delay_ms(1000);
UART_Write_Text("COSMIC :)\r\n");
UART_Write(0x0D);
UART_Write(0x1A);
__delay_ms(2000);
}