#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <leds.h>
#include "app.h"

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3
#define SCALE 308L

typedef void (*function_ptr)(void);

void BinaryCountUp(void);
void BinaryCountDown(void);
void GrayCountUp(void);
void GrayCountDown(void);
void BCDCountUp(void);
void BCDCountDown(void);
void Snake(void);
void Stack(void);
void Random(void);
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

void BinaryCountUp()
{	
	for(int i=0; i<256; i++)
	{
        LATA = i;
        delay(250);
        if (BUTTON_IsPressed(BUTTON_S6))
        break;
	}  

}

void BinaryCountDown()
{	
	for(int i=255; i>=0; i--)
	{
        LATA = i;
        delay(250);
        if (BUTTON_IsPressed(BUTTON_S6))
        break;
	}  

}

void GrayCountUp()
{	

    int x;
	for(int i=0; i<256; i++)
	{
		x = i;
		x = x^x>>1;
		LATA = x;
        delay(250);
        if (BUTTON_IsPressed(BUTTON_S6))
        break;
	}

}

void GrayCountDown()
{	

    int x;
	for(int i=255; i>=0; i--)
	{
		x = i;
		x = x^x>>1;
		LATA = x;
        delay(250);
        if (BUTTON_IsPressed(BUTTON_S6))
        break;
	}

}

void BCDCountUp()
{	

    int x;
	for(int i=0; i<100; i++)
	{
		x = ((i/10)*16)+(i%10);
		LATA = x;
        delay(250);
        if (BUTTON_IsPressed(BUTTON_S6))
        break;
	}

}

void BCDCountDown()
{	

    int x;
	for(int i=99; i>=0; i--)
	{
		x = ((i/10)*16)+(i%10);
		LATA = x;
        delay(250);
        if (BUTTON_IsPressed(BUTTON_S6))
        break;
	}

}

void Snake()
{	

	int x;
	for(int i=1; i<=32; i*=2)
	{
		x = i*7;
		LATA=x;
		delay(500);
        if (BUTTON_IsPressed(BUTTON_S6))
        break;
	}
	for(int i=16; i>=1; i/=2)
	{
		x = i*7;
		LATA=x;
		delay(500);
        if (BUTTON_IsPressed(BUTTON_S6))
        break;
	}
	
}

void Stack()
{	
	
	int x = 0;
    int y = 0;
    int z = 6;
    int count = 1;
		
	for(int i=0; i<=7; i++)
	{	
		x=0;
        
		for(int i=0; i<=z; i++)
		{
            if(x==0){
                x++;
            }
            else{
                x *= 2;
            }

            count = y + x;
            LATA= count;
            delay(250);
		}
		z--;
		y += x;
        
        if (BUTTON_IsPressed(BUTTON_S6)){
            break;
        }
	}	
}


void Random()
{
    
    unsigned char lcg(unsigned int x) //algorytm liniowego kongruentnego generatora liczb pseudolosowych
    {
        const unsigned int a = 251;
        const unsigned int c = 37;
        const unsigned int m = 256;
        return (a * x + c) % m;
    }

    unsigned int x = 0b1110011;
    while(1){
        LATA = x;
        delay(1000);
        if (BUTTON_IsPressed(BUTTON_S6)){
            break;
        }     
        x = lcg(x);
    };
}

int main ( void )
{

    SYS_Initialize();
    int program = 0;

    function_ptr funcs[] = {BinaryCountUp, BinaryCountDown, GrayCountUp, GrayCountDown, BCDCountUp, BCDCountDown, Snake, Stack, Random};

    while (1) {
        while (!BUTTON_IsPressed(BUTTON_S3) && !BUTTON_IsPressed(BUTTON_S4));

        if (BUTTON_IsPressed(BUTTON_S3) && program < 9)
            program++;
        else if (BUTTON_IsPressed(BUTTON_S3))
            program = 0;
        else if (BUTTON_IsPressed(BUTTON_S4) && program > 0)
            program--;
        else if (BUTTON_IsPressed(BUTTON_S4))
            program = 9;

        if (program > 0 && program <= 9) {
            funcs[program - 1]();
        }
    }
}