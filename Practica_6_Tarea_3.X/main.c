/*
 * OSCAR IVAN MORENO GUTIERREZ
 * PRACTICA 6 TAREA 3
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/LCDMiniDrivers/lcd.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr1.h"

#define ROW_LEN 16
/*
    Main application
*/
uint16_t counterPrincipal = 0;
uint8_t row0_disp[ROW_LEN] = "------- 3 -------";    
uint8_t row1_disp[ROW_LEN] = "";

uint8_t* Prow0 = &row0_disp;
uint8_t* Prow1 = &row1_disp;

char fila0[ROW_LEN];
char fila1[ROW_LEN];
static bool elFlag = true;
static bool elFlagDos = true;

void __attribute__ ((weak)) SWITCH1_CallBack(void)
{
    
    if (_LATD7 == 1){
        _LATB14 = 1;
        _LATD7 = 0;
        elFlagDos = false;
        TMR1_Stop();
    }
    //_LATE0 = !_LATE0;// Aqui se cambia el led verde a led azul solo si se esta prendido el verde
}


void __attribute__ ((weak)) TMR1_CallBack(void)
{
    
    static uint8_t counterSegundos = 0;
    counterPrincipal++;
    if (counterPrincipal == 1000 && counterSegundos < 3){
        if (counterSegundos < 3){
            counterSegundos ++;
        }
        
        counterPrincipal = 0;

    }
    switch(counterSegundos){
        case 0:
            //prendemos el led 1
            sprintf(fila0, "------- 3 -------");
            _LATE0 = 1;

            break;
        case 1:
            // prendemos el led 2
            sprintf(fila0, "------- 2 -------");
            _LATE1 = 1;

            break;
        case 2:
            // prendemos el led rojo
            sprintf(fila0, "------- 1 -------");
            _LATD5 = 1;

            break;
        case 3:
            // cambiamos de rojo a verde y apagamos led 1 y 2
            sprintf(fila0, "------- YA! -------");
            _LATD7 = 1;
            _LATD5 = 0;
            _LATE0 = 0;
            _LATE1 = 0;
            elFlag = false;
            counterSegundos++;
            break;
        default:
            
            break;
    }

    
}

int main(void)
{
    SYSTEM_Initialize();
    lcd_setContrast(0x20);
    lcd_clearDisplay();
    while(1)
    {
        if (!elFlag){
            if(!elFlagDos){
            sprintf(fila0, "  <=> STOP <=>  ");
            }else{
            sprintf(fila0, "Tiempo: ");
            }
            sprintf(fila1, " %i ms", counterPrincipal);
        }
        Prow0 = (uint8_t*) &fila0;
        Prow1 = (uint8_t*) &fila1;
        lcd_writeString(Prow0, 0);
        lcd_writeString(Prow1, 1);
        

    }    
}


