#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "app.h"

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3

void alarm ( void );
void SYS_Initialize ( void ) ;



APP_DATA appData = {
                    .messageLine1 = "Explorer 16 Demo" ,
                    .messageLine2 = "Press S3 to cont" ,
                    .messageTime = "Time 00: 00: 00 " ,
                    .messageADC = " Pot = 0.00 Vdc "
} ;


void delay(unsigned int ms)
{
    unsigned int i;
    unsigned char j;

    for (i = 0; i < ms; i++) {

        for (j = 0; j < 200; j++) {
            Nop();
            Nop();
            Nop();
            Nop();
            Nop();
        }
    }
}

void alarm(){

    for(int i = 0; i <= 3; i++)
    {
        i++;
        LATA = 1;
        delay(500);
        
        LATA = 0;
        delay(500);
    }
    LATA = 255;
}

int main ( void )
{
    SYS_Initialize();
    int power = 200;
    int time = 0;
    //char moc[5] = "Moc: ";
    //char czas[6] = "Czas: ";
    char str1[16] = "";
    char str2[16] = "";
    
    while ( 1 ){
        sprintf(str1, "MOC: %d", power);
        LCD_PutString ( str1 , sizeof(str1) ) ;
        LCD_PutString ( " W      " , 11 ) ;
        sprintf(str2, "CZAS: %d", time);
        LCD_PutString ( str2 , sizeof(str2) ) ;
        LCD_PutString ( " s" , 2 ) ;
        delay(500);
        LCD_ClearScreen();
        while((BUTTON_IsPressed(BUTTON_S3)))
        {
            if(power==200)
            {
                power=350;
                break;
            }
            if(power==350)
            {
                power=600;
                break;
            }
            if(power==600)
            {
                power=800;
                break;
            }
            if(power==800)
            {
                power=200;
                break;
            }   
        };
        if((BUTTON_IsPressed(BUTTON_S6)))
        {
            time+=60;
            delay(500);
        }
        if((BUTTON_IsPressed(BUTTON_S5)))
        {
            time+=10;
            delay(500);
        }
        if((BUTTON_IsPressed(BUTTON_S4))&&(time>0))
        {
            delay(1000);
            while(time>0)
            {
                if((BUTTON_IsPressed(BUTTON_S4)))
                {
                    delay(1000);
                    while(!(BUTTON_IsPressed(BUTTON_S4)))
                    {
                        sprintf(str1, "MOC: %d", power);
                        LCD_PutString ( str1 , sizeof(str1) ) ;
                        LCD_PutString ( " W      " , 11 ) ;
                        sprintf(str2, "CZAS: %d", time);
                        LCD_PutString ( str2 , sizeof(str2) ) ;
                        LCD_PutString ( " s" , 2 ) ;
                        delay(500);
                        LCD_ClearScreen();
                    };
                    while((BUTTON_IsPressed(BUTTON_S4)))
                    {
                        time = 1;
                        delay(500);
                        break;
                    };
                }
                time--;      
                sprintf(str1, "MOC: %d", power);
                LCD_PutString ( str1 , sizeof(str1) ) ;
                LCD_PutString ( " W      " , 11 ) ;
                sprintf(str2, "CZAS: %d", time);
                LCD_PutString ( str2 , sizeof(str2) ) ;
                LCD_PutString ( " s" , 2 ) ;
                delay(1000);
                LCD_ClearScreen();
            };
            alarm ();
        }
    };
}
