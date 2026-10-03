//ecSTM32F4v2.h

/**
******************************************************************************
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Woorim-Lee
Created          : 05-03-2021
Modified         : 10-01-2026
Language/ver     : C++ in VS Code

* @course   Embedded Controller- HGU
* @author	iiLAB
* @mod		2024-8-05 by YKKIM
* @brief	STM32F411 Library for EC
*
******************************************************************************
*/

//여기서 #difine LED_PIN, Button_PIN 같은 거 다 만들고 enum으로 해라


#ifndef __EC_STM_H
#define __EC_STM_H

// STM built-In Library
#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "math.h"

// EC course Library
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
//#include "ecTIM2.h"
//#include "ecPWM2.h"
//#include "ecStepper2.h"
//#include "ecADC2.h"
//#include "ecUART2.h"

PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};
PinName_t button_pin = PA_4;

void MCU_init(void){
    
     // Intialize System Clock
    RCC_HSI_init();    
    // Intialize FND pins and Others
    FND_init(pinFND);
    FND_select_init(selectFND);    

    RCC_PLL_init();                 // System Clock = 84MHz
	SysTick_init();                 // SysTick Timer Initialization

    // Button PC13
    //GPIO_init(PC_13, INPUT);

    // TU_EXTI
    GPIO_init(PB_12, OUTPUT);
    // GPIO_init(PC_3, OUTPUT);
    GPIO_init(PA_4, INPUT);

    GPIO_pupd(PA_4, EC_PU);    
    
    // LED PA5
    //GPIO_init(PA_5, OUTPUT);    

    // TIMx Default Initialization
    // ...
    // PWM Default Initialization
    // ...        
    // USART Default Initialization
    // ...
    // Others
}


#endif



 