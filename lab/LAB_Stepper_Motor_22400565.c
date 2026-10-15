/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Woorim-Lee
Created          : 05-03-2021
Modified         : 10-14-2026
Language/ver     : C++ in VS Code

Description      : LAB - Stepper Motor)
/----------------------------------------------------------------*/

#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"

#include "ecStepper2.h"

// ( A, B,  AN,  BN)
PinName_t pinStepper[4]    = {PB_10,PB_4,PB_5,PB_3};
uint32_t steps = 0; 

StepperMode_t current_mode = FULL;                  // Select mode(HALF or FULL)  
uint32_t rev = 1;
int speed = 14;               

// Initialiization 
void setup(void){	
	RCC_PLL_init();                                 // System Clock = 84MHz
	SysTick_init();                                 // Systick init
	
	GPIO_init(BUTTON_PIN, INPUT);           		// GPIOC pin13 initialization
    EXTI_init(BUTTON_PIN, FULL, 0);           		// External Interrupt Setting

	stepper_init(current_mode, pinStepper); 				// Stepper GPIO pin initialization
	stepper_speed(speed);                          		//  set stepper motor speed
}

int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();

	steps = STEP_PER_REV[current_mode]*rev;
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		stepper_step(steps, DIR_CCW);     // (Step : 2048, Direction : 0, Mode : FULL or HALF)
		delay_ms(1000);
		stepper_step(steps, DIR_CW);    // (Step : 2048, Direction : 1, Mode : FULL or HALF)
		delay_ms(1000);
	}
}

void EXTI15_10_IRQHandler(void) {  
	if (is_pending_EXTI(BUTTON_PIN)) {
		stepper_stop();
		clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
	}
}