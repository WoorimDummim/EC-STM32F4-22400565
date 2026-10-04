/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Woorim-Lee
Created          : 05-03-2021
Modified         : 10-04-2026
Language/ver     : C++ in VS Code

Description      : LAB - External Interrupt(EXTI)
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"

#define SW1_PIN    PD_2         // EVAL board JKIT SW1
#define SW2_PIN    PA_4			// EVAL board JKIT SW2
#define select_FND1  0

int count = 0;
int is_paused = 0;

void led_toggle(PinName_t pinName);  // in ecGPIO2.h

// Initialiization 
void setup(void)
{
    MCU_init();

    GPIO_init(SW1_PIN, INPUT);
    GPIO_init(SW2_PIN, INPUT);

    GPIO_pupd(SW1_PIN, EC_PU);
    GPIO_pupd(SW2_PIN, EC_PU);

    GPIO_init(select_FND1, OUTPUT);

    // Initialize EXTI SW_PIN
    EXTI_init(SW1_PIN, FALL, 10);	
    EXTI_init(SW2_PIN, FALL, 10);	
}


// MAIN  ----------------------------------------
int main(void) {
	setup();
	while (1){
        FND_select(select_FND1);
        FND_display(count % 10);

        if (is_paused == 0) count++;
        delay_ms(1000);
    }
}

void EXTI2_IRQHandler(void) {
	if (is_pending_EXTI(SW1_PIN)) {   
			count = 0;
			clear_pending_EXTI(SW1_PIN);
	}
}

void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {   
            is_paused ^= 1;            // toggle is comparision is_paused(current) and 1
			//clear_pending_EXTI(SW2_PIN);
	}
}
