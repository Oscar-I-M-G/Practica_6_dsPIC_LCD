/*
 * OSCAR IVAN MORENO GUTIERREZ
 * PRACTICA 6 TAREA 1
*/
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/tmr1.h"
/*
    Main application
*/
static uint16_t counterPrincipal = 0;
static uint8_t counterSegundos = 0;

int main(void)
{
    SYSTEM_Initialize();
    
    
    while(1)
    {
        
    }    
}

void __attribute__ ((weak)) TMR1_TimeoutCallback( void )
{ 
    counterPrincipal++;
    if (counterPrincipal == 1000){
        if (counterSegundos < 3){
            counterSegundos ++;
        }
        
        counterPrincipal = 0;

    }
    switch(counterSegundos){
        case 0:
            //prendemos el led 1
            _LATE0 = 1;
            break;
        case 1:
            // prendemos el led 2
            _LATE1 = 1;
            break;
        case 2:
            // prendemos el led rojo
            _LATD5 = 1;
            break;
        case 3:
            // cambiamos de rojo a verde y apagamos led 1 y 2
            _LATD7 = 1;
            _LATD5 = 0;
            _LATE0 = 0;
            _LATE1 = 0;
            TMR1_Stop();
            break;
        default:
            // regresamos
            counterSegundos = 3;
            
            break;
    }

} 



