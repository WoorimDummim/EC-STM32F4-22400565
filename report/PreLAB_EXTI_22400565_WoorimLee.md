# PreLAB: External Interrupt

**Date:** 2026-09-030

**Author/Partner:** Woorim-Lee

**Demo Video:** [[EC 26-2] PreLAB (EXTI)](https://youtu.be/Kv9ZmeY8kb0)

**PDF version:**



------

## Introduction

In this tutorial, we will learn how to use External Interrupt. We will create functions that capture the falling edge trigger by pushing a button using an external interrupt.

The objectives of this tutorial are how to

- Configure External input (EXTI) interrupt with NVIC
- Create your own functions for configuration of interrupts

**Submit the Pre-Lab report**

#### Hardware

- NUCLEO -F411RE

#### Software

- VS code, CMSIS, EC_HAL

#### Documentation

- [STM32 Reference Manual](https://ykkim.gitbook.io/ec/stm32-m4-programming/hardware/nucleo-f411re#manual-documentation)



## Overview of External Interrupt (EXTI)

#### A. Register List

List of external interrupt (EXTI) registers

<img src="C:\Users\dldnf\source\repos\EC\PreLAB_EXTI_22400565\report\img\스크린샷 2026-09-30 221135.png" alt="스크린샷 2026-09-30 221135" style="zoom: 67%;" />

```c
typedef struct
{
  __IO uint32_t IMR;    // EXTI Interrupt mask register
  __IO uint32_t EMR;    // EXTI Event mask register
  __IO uint32_t RTSR;   // EXTI Rising trigger selection register
  __IO uint32_t FTSR;   // EXTI Falling trigger selection register
  __IO uint32_t SWIER;  // EXTI Software interrupt event register
  __IO uint32_t PR;     // EXTI Pending register
}EXTI_TypeDef
```



#### B. Register Setting

**1. GPIO:Select & Initialize GPIO Port*****y***Pin***x*** **for EXTIx**

- mode = INPUT

**2. EXTI Setting**

- Enable SYSCFG peripheral clock. **RCC->APB2ENR**
- Select GPIO Port *y* to EXTI: **SYSCFG->EXTICR**
- Configure the trigger edge. **EXTI->FTSR or RTSR**
- Enable EXTI: **EXTI->IMR**
  - Not-mask Interrupt request

**3. NVIC** 

- `NVIC_SetPriority()`
- `NVIC_EnableIRQ()`

**4. EXTI handler**

- is_pending ? Then `EXTIx_IRQHandler()`
- clear_pending when finished



## Exercise 

### A. Exercise 1: Register Configuration

Fill in the blanks below

**Assumption:**

```c
#define BUTTON_PIN PA_4 //EVAL board JKIT
```



#### EXTI GPIO Pin initialization

- Push-Button: Port A Pin 4 / Input / PU

```c
// Use your API library  GPIO
GPIO_mode(PA_4, 0);
GPIO_pupd(PA_4, 1);
```



#### EXTI Configuration

1. **Enable EXTI Clock with SYSCFG controller clock**

- **RCC_APB2ENR:** SYSCFGEN

  ```c
  // SYSCFG peripheral clock enable
  RCC->APB2ENR |= (0x1UL<<14UL);
  ```

  <img src="C:\Users\dldnf\source\repos\EC\PreLAB_EXTI_22400565\report\img\스크린샷 2026-09-30 221547.png" alt="스크린샷 2026-09-30 221547"  />



2. **Connect EXTI to the GPIO Port_y Pin_x**

- **SYSCFG_EXTICR2:** EXTIx

- Connect PA_4(push-button) to EXTI4 line (given code)

  ```c
  	// Button: PA_4 -> EXTICR2(EXTI4)
  	// Pin 4~7: EXTICR2 // EXTICR[1]
  
  	SYSCFG->EXTICR[1] &= ~(0xFUL << 4);
  	SYSCFG->EXTICR[1] |=  0UL<<4;
  
  	// These are the same as
  	SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI4;  
  	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PA;
  ```

<img src="C:\Users\dldnf\source\repos\EC\PreLAB_EXTI_22400565\report\img\스크린샷 2026-09-30 221651.png" alt="스크린샷 2026-09-30 221651"  />

- **Generalize of Connecting Port y, Pin x to EXTIx**

  ```c
      // Connect EXTI to the GPIO Port_y Pin_x	
  	// Pin 0~3: EXTICR1 // EXTICR[0]
  	// Pin 4~7: EXTICR2 // EXTICR[1]
  	// Pin 8~11: EXTICR3 // EXTICR[2]
  	// Pin 12~15: EXTICR4 // EXTICR[3]
  	uint32_t EXTICR_port=0;
  	if		(Port == GPIOA) EXTICR_port = 0;
  	else if	(Port == GPIOB) EXTICR_port = 1;
  	else if	(Port == GPIOC) EXTICR_port = 2;
  	else if	(Port == GPIOD) EXTICR_port = 3;
  	else					EXTICR_port = 4;
  	
  	SYSCFG->EXTICR[pin/4] &= ~(0xF<<(pin % 4)*4);			        // clear 4 bits
  	SYSCFG->EXTICR[pin/4] |= (EXTICR_port<<(pin % 4)*4);			// Set 4 bits	
  ```

> HINT 1 : mod(pin,4) * 4, (int)(pin/4)
>
> HINT 2 : Find the pattern in the binary representations



| **Bit Starting Position** | **Pin y**     |               |                |
| ------------------------- | ------------- | ------------- | -------------- |
|                           | **EXTICR[0]** | **EXTICR[1]** | **EXTICR[2]**  |
| Bit 0                     | 0 (b00**00**) | 4 (b01**00**) | 8 (b10**00**)  |
| Bit 4                     | 1 (b00**01**) | 5 (b01**01**) | 9 (b10**01**)  |
| Bit 8                     | 2 (b00**10**) | 6 (b01**10**) | 10 (b10**10**) |
| Bit 12                    | 3 (b00**11**) | 7 (b01**11**) | 11 (b10**11**) |



3. **Select Trigger Edge (RISE, FALL, BOTH)**

- **EXTI_FTSR:** TRx or **EXTI_RTSR:** TRx

  ```c
      // Select  Trigger edge (RISE, FALL, BOTH)
  	if (trig_type == FALL) 		EXTI->FTSR |= 1UL << pin;  // Falling trigger enable 
  	else if	(trig_type == RISE) EXTI->RTSR |= 1UL << pin;   // Rising trigger enable 
  	else if	(trig_type == BOTH) {			// Both falling/rising trigger enable
  		EXTI->RTSR |= 1UL << pin; 
  		EXTI->FTSR |= 1UL << pin;
  	} 
  ```

<img src="C:\Users\dldnf\source\repos\EC\PreLAB_EXTI_22400565\report\img\스크린샷 2026-09-30 223109.png" alt="스크린샷 2026-09-30 223109"  />



![스크린샷 2026-09-30 223041](C:\Users\dldnf\source\repos\EC\PreLAB_EXTI_22400565\report\img\스크린샷 2026-09-30 223041.png)



4. **Enable EXTI: Not-masking Interrupt request**

- **EXTI_IMR:** MRx
  - Enabling == not-masking

```
	// Enable EXTI, with Not-Masked Interrupt Request 
	// Not-mask (==Enable) EXTIx
 	EXTI->IMR |= 1UL << pin;
```

<img src="C:\Users\dldnf\source\repos\EC\PreLAB_EXTI_22400565\report\img\스크린샷 2026-09-30 223307.png" alt="스크린샷 2026-09-30 223307"  />



#### EXTI_NVIC

- Search for "**Vector table for STM32F411xC/E** " in Reference Manual
- Fill-in the blanks in the table for EXTI 0 to EXT 15

| EXTIx     | ISR (handler)          | IRQn (keyword, stm32f111xe.h) | IRQn |
| --------- | ---------------------- | ----------------------------- | ---- |
| EXTI0     | EXTI0_IRQHandler()     | EXTI0_IRQn                    | 6    |
| EXTI1     | EXTI1_IRQHandler()     | EXTI1_IRQn                    | 7    |
| EXTI2     | EXTI2_IRQHandler()     | EXTI2_IRQn                    | 8    |
| EXTI3     | EXTI3_IRQHandler()     | EXTI3_IRQn                    | 9    |
| EXTI4     | EXTI4_IRQHandler()     | EXTI4_IRQn                    | 10   |
| EXTI9_5   | EXTI9_5_IRQHandler()   | EXTI9_5_IRQn                  | 23   |
| EXTI15_10 | EXTI15_10_IRQHandler() | EXTI15_10_IRQn                | 40   |

- Fill-in the blanks

```c
	// NVIC(IRQ) Setting
	uint32_t EXTI_IRQn = 0;
	if (pin < 5) 		EXTI_IRQn = EXTI0_IRQn + pin;
	else if	(pin < 10) 	EXTI_IRQn = EXTI9_5_IRQn;
	else 				EXTI_IRQn = EXTI15_10_IRQn;
		
	NVIC_SetPriority(EXTI_IRQn, priority);	
	NVIC_EnableIRQ(EXTI_IRQn); 				
```



#### EXTI_handler

1. **Check for Pending Status**
   - **EXTI_PR:** PRx
   - Read the bit at PRx and returns either 1 or 0

```c
uint32_t is_pending_EXTI(PinName_t pinName) {
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	uint32_t EXTI_PRx = ((EXTI->PR >>pin) & 1);     // read PRx, EXTI pending bit.  Use  (REG>>k & 1) to read.
	return  EXTI_PRx; 	// Return only 0 or 1
}
```



2. **Clear Pending **
   - **EXTI_PR:** PRx
   - By writing '1', it clears the pending bit.

```c
void clear_pending_EXTI(PinName_t pinName){
	// Port, Pin Configuration
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);

	// clear by writing 1 to the pending bit
	EXTI->PR  |= (1UL << pin);     
}
```

<img src="C:\Users\dldnf\source\repos\EC\PreLAB_EXTI_22400565\report\img\스크린샷 2026-09-30 223459.png" alt="스크린샷 2026-09-30 223459"  />



### B. Exercise 2 : Programming

This is an example code for toggling LED on/off with the button input trigger (EXTI)

- Fill in the empty spaces in the downloaded library `ecEXTI2.c`
- Run the program and check your result.
- Your tutorial report must be submitted to LMS



**Procedure**

- Download the header library files and save under `include\`.

  - `ecEXTI2_student.h, ecEXTI2_student.c`: [Click here to download](https://github.com/ykkimhgu/EC-student/tree/main/include/lib-student)

- Rename the files as `ecEXTI2.h, ecEXTI2.c`

  > Write your name and modified date in the comment box

- Create a new project under the directory `EC\tutorial\`

  - Environment : `env:TU_EXTI`
  - Source file: `TU_EXTI_student.c`

- Modify the `platformio.ini` **,** to add new environment.

Complete the function  `led_toggle(void)`

```c
void led_toggle(PinName_t pinName){
	GPIO_TypeDef *Port;    
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);
    
	// YOUR CODE GOES HERE - Use XOR 
    Port->ODR ^= (1UL << pin);
}
```



##### Results

<img src="img/KakaoTalk_20261001_020436360_02.jpg" alt="KakaoTalk_20261001_020436360_02" style="zoom: 33%;" />

<img src="img/KakaoTalk_20261001_020436360_01.jpg" alt="KakaoTalk_20261001_020436360_01" style="zoom: 33%;" />

<img src="img/KakaoTalk_20261001_020436360.jpg" alt="KakaoTalk_20261001_020436360" style="zoom: 33%;" />



LED7 continuously toggles every 1 second within the main loop. Concurrently, pressing the button triggers an external interrupt that independently turns LED0 ON and OFF, without affecting the main loop's timing.