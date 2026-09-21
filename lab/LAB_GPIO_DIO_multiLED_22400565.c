/**
******************************************************************************
* @author	WoorimLee
* @Mod		09.18.2026
* @brief	Embedded Controller:  LAB Digital In/Out
*					 - Toggle multiple LEDs by Button B1 pressing
* 
******************************************************************************
*/

#include "stm32f4xx.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"

PinName_t LED_pin[4] = {PB_12, PB_13, PB_14, PB_15};
PinName_t button_pin = PA_4;

void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	int count = 3;
	int buttonState = 0;
	int prev_buttonState = 0;
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		 buttonState = GPIO_read(button_pin);
		 if (buttonState == 0 && prev_buttonState == 1){
			GPIO_write(LED_pin[count % 4],LOW);
			count++;
			GPIO_write(LED_pin[(count % 4)],HIGH);
			prev_buttonState = buttonState;
		 }
		 else if(buttonState == 1){
			prev_buttonState = 1;
		 }
	}
}

// Initialization 
void setup(void)
{
	RCC_HSI_init();

	// Configuration button pin
	GPIO_init(button_pin, INPUT);  				// calls RCC_GPIOC_enable()

	// Configuration LED pins
	for(int i=0; i<(sizeof(LED_PIN)/sizeof(LED_pin[0])); i++){
		GPIO_init(LED_pin[i], OUTPUT);			// calls RCC_GPIOA_enable()
	}	
}