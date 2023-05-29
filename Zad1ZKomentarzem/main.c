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

typedef void (*function_ptr)(void); //definicja wskaźnika funkcji 

void BinaryCountUp(void); //deklaracje funkcji zdefiniowanych w późniejszym kodzie
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


void delay(unsigned int ms) //funkcja delay, która tworzy opóźnienie w programie
{
    unsigned int i; //deklaracje zmiennych
    unsigned char j;

    for (i = 0; i < ms; i++) { //pętla for która wykonuje się tyle razy ile milisekund podaliśmy w argumencie

        for (j = 0; j < 200; j++) { //pętla która wykonuje 200 iteracji
            Nop(); //no operation - funkcja która nie wykonuje operacji, w tym kodzie służy do tworzenia opóźnienia
            Nop();
            Nop();
            Nop();
            Nop();
        }
    }
}

void BinaryCountUp() //implementacja funkcji liczącej binarnie do góry od 0 do 255
{	
	for(int i=0; i<256; i++) //pętla która wykonuje 256 iteracji, jest licznikiem w funkcji i na podstawie iteracji wyświetlana jest aktualna liczba
	{
        LATA = i; //wyświetlenie aktualnego stanu licznika na interfejsie LATA - diody 
        delay(250); //opóźnienie 250 milisekund aby można było zauważyć stan licznika
        if (BUTTON_IsPressed(BUTTON_S6)) //warunek przerwania funkcji w dowolnym momencie jej działania przy naciśnięciu przycisku S6
        break; //przerwanie działania funkcji
	}  

}

void BinaryCountDown() //implementacja funkcji liczącej binarnie w dół od 255 do 0
{	
	for(int i=255; i>=0; i--) //pętla która wykonuje 256 iteracji, jest licznikiem w funkcji i na podstawie iteracji wyświetlana jest aktualna liczba
    {    
        LATA = i; //wyświetlenie aktualnego stanu licznika na interfejsie LATA - diody 
        delay(250); //opóźnienie 250 milisekund aby można było zauważyć stan licznika
        if (BUTTON_IsPressed(BUTTON_S6)) //warunek przerwania funkcji w dowolnym momencie jej działania przy naciśnięciu przycisku S6
        break; //przerwanie działania funkcji
	}  

}

void GrayCountUp() //implementacja funkcji liczącej w kodzie Graya do góry od 0 do 255
{	

    int x; //deklaracja zmiennej
	for(int i=0; i<256; i++) //pętla która wykonuje 256 iteracji
	{
		x = i; //przypisanie do zmiennej x wartości i z pętli liczącej
		x = x^x>>1; //obliczenie wartości w kodzie Graya za pomocą przesunięcia bitowego o 1 i porównanie wartości pierwotnej oraz przesuniętej za pomocą operacji XOR
		LATA = x; //wyświetlenie aktualnego stanu licznika na interfejsie LATA - diody 
        delay(250); //opóźnienie 250 milisekund aby można było zauważyć stan licznika
        if (BUTTON_IsPressed(BUTTON_S6)) //warunek przerwania funkcji w dowolnym momencie jej działania przy naciśnięciu przycisku S6
        break; //przerwanie działania funkcji
	}

}

void GrayCountDown() //implementacja funkcji liczącej w kodzie Graya w dół od 255 do 0
{	

    int x; //deklaracja zmiennej
	for(int i=255; i>=0; i--) //pętla która wykonuje 256 iteracji
	{
		x = i; //przypisanie do zmiennej x wartości i z pętli liczącej
		x = x^x>>1; //obliczenie wartości w kodzie Graya za pomocą przesunięcia bitowego o 1 i porównanie wartości pierwotnej oraz przesuniętej za pomocą operacji XOR
		LATA = x; //wyświetlenie aktualnego stanu licznika na interfejsie LATA - diody 
        delay(250); //opóźnienie 250 milisekund aby można było zauważyć stan licznika
        if (BUTTON_IsPressed(BUTTON_S6)) //warunek przerwania funkcji w dowolnym momencie jej działania przy naciśnięciu przycisku S6
        break; //przerwanie działania funkcji
	}

}

void BCDCountUp() //implementacja funkcji liczącej w górę w BCD od 0 do 99
{	

    int x; //deklaracja zmiennej
	for(int i=0; i<100; i++) //pętla która wykonuje 100 iteracji
	{
		x = ((i/10)*16)+(i%10); //obliczanie wartości zmiennej w kodzie BCD 
		LATA = x; //wyświetlenie aktualnego stanu licznika na interfejsie LATA - diody 
        delay(250); //opóźnienie 250 milisekund aby można było zauważyć stan licznika
        if (BUTTON_IsPressed(BUTTON_S6)) //warunek przerwania funkcji w dowolnym momencie jej działania przy naciśnięciu przycisku S6
        break; //przerwanie działania funkcji
	}

}

void BCDCountDown() //implementacja funkcji liczącej w dół w BCD od 99 do 0
{	

    int x; //deklaracja zmiennej
	for(int i=99; i>=0; i--) //pętla która wykonuje 100 iteracji
	{
		x = ((i/10)*16)+(i%10); //obliczanie wartości zmiennej w kodzie BCD 
		LATA = x; //wyświetlenie aktualnego stanu licznika na interfejsie LATA - diody 
        delay(250); //opóźnienie 250 milisekund aby można było zauważyć stan licznika
        if (BUTTON_IsPressed(BUTTON_S6)) //warunek przerwania funkcji w dowolnym momencie jej działania przy naciśnięciu przycisku S6
        break; //przerwanie działania funkcji
	}

}

void Snake() //implementacja funkcji wyświętlającej węża na interfejsie LATA
{	

	int x; //deklaracja zmiennej
	for(int i=1; i<=32; i*=2) //// pętla która wykonuje się od 1 do 32 z krokiem równym podwojeniu aktualnej wartości i
	{
		x = i*7; //obliczenie zmiennej x
		LATA=x; //wyświetlanie węża na interfejsie LATA
		delay(500); //opóźnienie 500 milisekund aby można było zauważyć ruch węża
        if (BUTTON_IsPressed(BUTTON_S6)) //warunek przerwania funkcji w dowolnym momencie jej działania przy naciśnięciu przycisku S6
        break; //przerwanie działania funkcji
	}
	for(int i=16; i>=1; i/=2) //Pętla która wykonuje się od 16 do 1 z krokiem równym podzieleniu aktualnej wartości i przez 2.
	{
		x = i*7; //obliczenie zmiennej x
		LATA=x; //wyświetlanie węża na interfejsie LATA
		delay(500); //opóźnienie 500 milisekund aby można było zauważyć ruch węża
        if (BUTTON_IsPressed(BUTTON_S6)) //warunek przerwania funkcji w dowolnym momencie 
                            //jej działania przy naciśnięciu przycisku S6
        break; //przerwanie działania funkcji
	}
	
}

void Stack()
{	
	
	int x = 0; //deklaracja zmiennej
    int y = 0; //deklaracja zmiennej
    int z = 6; //deklaracja zmiennej
    int count = 1; //deklaracja zmiennej
		
	for(int i=0; i<=7; i++) // Pętla for, która wykonuje się 8 razy dla wartości i od 0 do 7
	{	
		x=0; // Resetowanie wartości zmiennej x na 0 przed każdą iteracją zewnętrznej pętli
        
		for(int i=0; i<=z; i++) // Pętla for, która wykonuje się zależnie od wartości zmiennej z.
		{
            if(x==0){
                x++;
            }
            else{
                x *= 2;
            }
            // jeśli x jest równe 0, zwiększa się wartość x o 1
            // w przeciwnym przypadku, wartość x jest mnożona przez 2

            count = y + x;  // obliczanie wartości zmiennej count poprzez dodanie wartości y do x
            LATA= count; // wyświetlanie stosu na interfejsie LATA
            delay(250); //opóźnienie 250 milisekund aby można było zauważyć układanie stosu
		}
		z--; // zmniejszenie wartości zmiennej z o 1 po każdej iteracji zewnętrznej pętli
		y += x; // zwiększanie wartości zmiennej y o wartość x po każdej iteracji zewnętrznej pętli
        
        if (BUTTON_IsPressed(BUTTON_S6)){ //warunek przerwania funkcji w dowolnym 
            //momencie jej działania przy naciśnięciu przycisku S6//warunek przerwania funkcji w dowolnym momencie jej działania przy naciśnięciu przycisku S6
            break; //przerwanie działania funkcji
        }
	}	
}


void Random()
{
    
    unsigned char lcg(unsigned int x) //algorytm liniowego kongruentnego generatora liczb pseudolosowych
    {
        const unsigned int a = 251; // Wartość a w algorytmie LCG.
        const unsigned int c = 37; // Wartość c w algorytmie LCG.
        const unsigned int m = 256; // Wartość m w algorytmie LCG.
        return (a * x + c) % m; // oblicza nową wartość pseudolosową na podstawie wzoru LCG.
    }

    unsigned int x = 0b1110011; // Inicjalizacja zmiennej x jako binarnej wartości 1110011
    while(1){
        LATA = x; // wyświetlanie losowej wartości na interfejsie LATA
        delay(1000); //opóźnienie 1000 milisekund aby można było zauważyć różne wygenerowane wartości
        if (BUTTON_IsPressed(BUTTON_S6)){ //warunek przerwania funkcji w dowolnym momencie jej działania przy naciśnięciu przycisku S6//warunek przerwania funkcji w dowolnym momencie jej działania przy naciśnięciu przycisku S6
            break; //przerwanie działania funkcji
        }     
        x = lcg(x); // Generowanie nowej wartości pseudolosowej na podstawie aktualnej wartości x
        // za pomocą funkcji lcg, która implementuje algorytm LCG
    };
}

int main ( void )
{

    SYS_Initialize(); // Inicjalizacja systemu
    int program = 0; //deklaracja zmiennej program, która określa aktualny program

    function_ptr funcs[] = {BinaryCountUp, BinaryCountDown, GrayCountUp, GrayCountDown, BCDCountUp, BCDCountDown, Snake, Stack, Random};
    //deklaracja tablicy funkcji, która przechowuje wskaźniki do funkcji odpowiadającym różnym podprogramom
    while (1) { //nieskończona pętla
        while (!BUTTON_IsPressed(BUTTON_S3) && !BUTTON_IsPressed(BUTTON_S4));
        //pętla która swoim wykonywaniem blokuje przeskok programu i ponowne odpalenie się funkcji
        if (BUTTON_IsPressed(BUTTON_S3) && program < 9) //warunek który przy wciśnięciu przycisku S3 zmienia program na następny
            program++;
        else if (BUTTON_IsPressed(BUTTON_S3))
            program = 0;
        else if (BUTTON_IsPressed(BUTTON_S4) && program > 0) //warunek który przy wciśnięciu przycisku S4 zmienia program na poprzedni
            program--;
        else if (BUTTON_IsPressed(BUTTON_S4))
            program = 9;

        if (program > 0 && program <= 9) { //warunek który sprawdza czy zmienna program posiada właściwą wartość do odpalenia podprogramu
            funcs[program - 1](); //wywołanie funckji, która odpala aktualnie wybrany podprogram, -1 jest potrzebne aby ustawić zmienną program jako odpowiedni index dla wywoałania funkcji
        }
    }
}