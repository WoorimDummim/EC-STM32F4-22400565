/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Woorim-Lee
Created          : 05-03-2021
Modified         : 09-17-2026
Language/ver     : C++ in VS Code

Description      : GPIO 7segment
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"

PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};
PinName_t button_pin = PA_4;

void setup(void){
    // Intialize System Clock
    RCC_HSI_init();    
    // Intialize FND pins and Others
    FND_init(pinFND);
    FND_select_init(selectFND);    
    // Intialize  Others
    GPIO_init(button_pin, INPUT);
};

int main(void) {
    setup();

    int Count = 0;
    int buttonState = 0;
    int prev_buttonState = 1;
    uint8_t selectFND1 = 0;        // 0 = count / 10;
    uint8_t selectFND2 = 1;

    // // Problem 2
    // while (1) {
    //     FND_select(selectFND1);
    //     buttonState = GPIO_read(button_pin);
	// 	if(buttonState == 0 && prev_buttonState == 1) {
    //         Count++;
    //         FND_display(Count % 10);
    //         prev_buttonState = buttonState;
    //     }

    //     else if(buttonState == 1) {
    //         FND_display(Count % 10);
    //         prev_buttonState = 1;
    //     }
    // }

    // Problem 2-expend
    while (1) {

        FND_select(selectFND1);
        FND_display(Count % 10);
        delay_ms(5);

        FND_select(selectFND2);
        FND_display(Count / 10);
        delay_ms(5);

        buttonState = GPIO_read(button_pin);
    
		if(buttonState == 0 && prev_buttonState == 1) {
            Count++;
            prev_buttonState = buttonState;

            if (Count > 19) Count = 0;
        }

        else if(buttonState == 1) prev_buttonState = 1;
    }
}

