#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "app.h"

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3

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

int main ( void )
{
    SYS_Initialize();
    char reklama[50][16]={
        "                ",
        "   KOMPUTERY !  ",
        "   KOMPUTERY !  ",
        "                ",
        "                ",
        "               K",
        "              K ",
        "             K O",
        "            K O ",
        "           K O M",
        "          K O M ",
        "         K O M P",
        "        K O M P ",
        "       K O M P U",
        "      K O M P U ",
        "     K O M P U T",
        "    K O M P U T ",
        "   K O M P U T E",
        "  K O M P U T E ",
        " K O M P U T E R",
        "K O M P U T E R ",
        " O M P U T E R Y",
        "O M P U T E R Y ",
        " M P U T E R Y !",
        "M P U T E R Y ! ",
        " P U T E R Y !  ",
        "P U T E R Y !   ",
        " U T E R Y !    ",
        "U T E R Y !     ",
        " T E R Y !      ",
        "T E R Y !       ",
        " E R Y !        ",
        "E R Y !         ",
        " R Y !          ",
        "R Y !           ",
        " Y !            ",
        "Y !             ",
        " !              ",
        "!               ",
        "                ",
        "   KOMPUTERY !  ",
        "   KOMPUTERY !  ",
        "                ",
        "                ",
        "   SPRZEDAZ!!!  ",
        "   SPRZEDAZ!!!  ",
        "                ",
        "                ",
        "    NAPRAWA!!!  ",
        "    NAPRAWA!!!  ",
    };
    

    while ( 1 )
    {
        for(int i=0;i<50;i++)
        {
            LCD_PutString ( reklama[i] , 16) ;
            delay(500);
            LCD_ClearScreen();      
        }
        
    } ;
}