/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Woorim-Lee
Created          : 05-03-2021
Modified         : 10-01-2026
Language/ver     : C++ in VS Code

Description      : LAB - External Interrupt(EXTI)
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"


#define LED0_PIN   PB_12 		//EVAL board JKIT LED0
#define SW2_PIN    PA_4			//EVAL board JKIT SW2

int Count = 0;
uint8_t selectFND = 0;

void led_toggle(PinName_t pinName);  // in ecGPIO2.h

// Initialiization 
void setup(void)
{
    // RCC_PLL_init();                 // System Clock = 84MHz
    // SysTick_init();                 // SysTick Timer Initialization
    // // Initialize GPIOB_12 for Output
    // GPIO_init(LED0_PIN, OUTPUT);    // LED0 for EVAL board	

    // // Initialize GPIOA_4 for Input Button
    // GPIO_init(SW2_PIN, INPUT);  // INPUT for EVAL board
    // GPIO_pupd(SW2_PIN, EC_PU);  // PULL-UP for EVAL board

    MCU_init();

    // Initialize EXTI PA_4
    EXTI_init(SW2_PIN, FALL, 10);		
}


// MAIN  ----------------------------------------
int main(void) {
	setup();
	while (1){
        delay_ms(5000);
        FND_select(selectFND);
        FND_display(Count % 10);
    }
}

//핸들러가 두개 들어가야해 Switch1 Switch2 !!

void EXTI4_IRQHandler(void) {


	if (is_pending_EXTI(SW2_PIN)) {   
			led_toggle(LED0_PIN);

            Count++;

			clear_pending_EXTI(SW2_PIN);
	}
}
