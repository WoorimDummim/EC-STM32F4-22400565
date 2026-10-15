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
    // Initialize system clock and basic MCU settings
    MCU_init();                             // FND, PLL, SysTick

    // Configure switch pins as Input
    GPIO_init(SW1_PIN, INPUT);
    GPIO_init(SW2_PIN, INPUT);

    // Enable internal pull-up resistors for switches
    GPIO_pupd(SW1_PIN, EC_PU);
    GPIO_pupd(SW2_PIN, EC_PU);

    // Configure 7-segment digit selection pin as Output
    GPIO_init(select_FND1, OUTPUT);

    // Initialize EXTI SW_PIN
    EXTI_init(SW1_PIN, FALL, 10);	
    EXTI_init(SW2_PIN, FALL, 10);	
}


// MAIN  ----------------------------------------
int main(void) {
	setup();
	while (1){
        FND_select(select_FND1);             // Selection of 7segment display
        FND_display(count % 10);             // LED ON of 7segment display 

        if (is_paused == 0) count++;         // Increment counter if not paused
        delay_ms(1000);
    }
}

void EXTI2_IRQHandler(void) {
	if (is_pending_EXTI(SW1_PIN)) {   
			count = 0;                       // reset
			clear_pending_EXTI(SW1_PIN);     // clear pending
	}
}

void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {   
            is_paused ^= 1;                  // Toggle pause state (is_paused(current) <-> 1)
			clear_pending_EXTI(SW2_PIN);     // clear pending
	}
}
