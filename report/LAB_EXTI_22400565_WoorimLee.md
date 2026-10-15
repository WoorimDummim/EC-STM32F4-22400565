# LAB: EXTI & SysTick(eval board)

**Date:** 2026-10-04

**Author/Partner:** Woorim-Lee

**Demo Video:** [[EC 26-2] LAB (EXTI)](https://youtu.be/A2r5OTkyWjo)

**PDF version: **[LAB_EXTI.pdf](./LAB_EXTI_22400565_WoorimLee.pdf)



----

## Introduction

In this lab, you are required to create two simple programs using interrupt:

(1) Display the number counting from 0 to 9 with Button Press

(2) Counting at a rate of 1 second

You must submit

- LAB Report (*.md & *.pdf)
- Zip source files(main*.c, ecRCC2.h, ecGPIO2.h, ecSysTick2.c etc...).
  - Only the source files. Do not submit project files

#### Requirement

**Hardware**

- MCU
  - NUCLEO-F411RE
- Eval Board (JKIT)
- Actuator/Sensor/Others:

**Software**

- PlatformIO, CMSIS, EC_HAL library



--------

## Problem 0: STM-Arduino

We are going to create a simple program that turns LED(LD2) on triggered by **External Interrupt** of user button(BT1) (on NUCLEO-64, not on JKIT)



### Result

Pressing the User Button (BT1) triggers an external interrupt that immediately turns on the LED (LD2). Releasing the button turns the LED off.  

<img src="img/KakaoTalk_20261004_220339515.jpg" alt="KakaoTalk_20261004_220339515" style="zoom: 33%;" />

<img src="img/KakaoTalk_20261004_220339515_01.jpg" alt="KakaoTalk_20261004_220339515_01" style="zoom: 33%;" />



----------

## Problem 1: Counter on 7-Segment display using EXTI

### Problem

Create a code to display the counter-up from 0 to 9 and repeating.

- Count up at the rate of 1 sec.
  - Use `delay_ms()` in the main loop
- Pause the counting when SW2 is pressed
- Resets to zero when the push button is pressed: SW1
  - Must use External Interrupts for SW1, SW2

*** Challenge : Extend the count-up number : 0 to 59**



### Procedure

1. Connect the evaluation board [(JKIT-NUCLEO) ](https://ykkim.gitbook.io/ec/ec-course/hardware/stm32f-evaluation-board#reference-manual)to the MCU.
2. Make sure that your library are in `EC\include\`.
   - **ecRCC2.h, ecRCC2.c**
   - **ecGPIO2.h, ecGPIO2.c**
   - **ecSysTick2.h, ecSysTick2.c**
   - **ecEXTI2.h, ecEXTI2.c**
   - **ecSTM32F4v2.h**
3. Create a new project under the directory `EC\lab\`

- Environment: “**LAB_EXTI”.**
- Source File: “**LAB_EXTI.c”**

1. You must modify the `platformio.ini` **,** to add new environment.

   

### Configuration

Configure the MCU GPIO

| Function                         | Port - Pin                                                   | Configuration                                 |
| -------------------------------- | ------------------------------------------------------------ | --------------------------------------------- |
| **Button (SW1) on JKIT**         | PD_2                                                         | DIN, Pull-Up                                  |
| **Button (SW2) on JKIT**         | PA_4                                                         | DIN, Pull-Up                                  |
| **7-Segment DOUT**               | PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7<br />('a'~'g''dot', respectively) | Push-Pull, No Pull-up-Pull-down, Medium Speed |
| **Selection of 7-Segment Display | PA_10 (FND_0)                                                | DOUT, Push-Pull                               |



#### Code

The `MCU_init()` function initializes the basic microcontroller system environment. `SW1_PIN` and `SW2_PIN` are configured as input pins using `GPIO_init()`, and internal pull-up resistors (`EC_PU`) are enabled via `GPIO_pupd()`.  The `select_FND1` pin is configured as an output pin to control the digit selection of the 7-segment display. External interrupts (EXTI) for both switches are configured to trigger on the falling edge (`FALL`) with a priority level of 10. 

```c
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
```



Inside the infinite `while(1)` loop, `FND_select()` activates the specific digit, and `FND_display(count % 10)` outputs the ones digit of the current `count` value. The `count` variable increments by 1 only when the `is_paused` flag is equal to 0. A `delay_ms(1000)` function is utilized to create a 1-second interval for the counter.   

```c
/ MAIN  ----------------------------------------
int main(void) {
	setup();
	while (1){
        FND_select(select_FND1);
        FND_display(count % 10);

        if (is_paused == 0) count++;
        delay_ms(1000);
    }
}
```



The `EXTI2_IRQHandler()` processes the external interrupt from SW1 by resetting the `count` variable to 0 and clearing the pending interrupt flag.   

```c
void EXTI2_IRQHandler(void) {
	if (is_pending_EXTI(SW1_PIN)) {   
			count = 0;
			clear_pending_EXTI(SW1_PIN);
	}
}
```



The `EXTI4_IRQHandler()` processes the external interrupt from SW2 by toggling the `is_paused` state via a bitwise XOR operation (`is_paused ^= 1`) to pause or resume the counter, followed by clearing the pending interrupt flag.

```c
void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {   
            is_paused ^= 1;            // toggle is comparison is_paused(current) and 1
			clear_pending_EXTI(SW2_PIN);
	}
}
```



### Results and Discussion

#### Results

Images (a) to (j) demonstrate the basic 0 to 9 up-counting operation.

| ![KakaoTalk_20261004_212705926](img/KakaoTalk_20261004_212705926.jpg)(a) | ![KakaoTalk_20261004_212705926_01](img/KakaoTalk_20261004_212705926_01.jpg)(b) | ![KakaoTalk_20261004_212705926_02](img/KakaoTalk_20261004_212705926_02.jpg)(c) |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| **![KakaoTalk_20261004_212705926_03](img/KakaoTalk_20261004_212705926_03.jpg)(d)** | **![KakaoTalk_20261004_212705926_04](img/KakaoTalk_20261004_212705926_04.jpg)(e)** | **![KakaoTalk_20261004_212705926_05](img/KakaoTalk_20261004_212705926_05.jpg)(f)** |
| **![KakaoTalk_20261004_212705926_06](img/KakaoTalk_20261004_212705926_06.jpg)(g)** | **![KakaoTalk_20261004_212705926_07](img/KakaoTalk_20261004_212705926_07.jpg)(h)** | **![KakaoTalk_20261004_212705926_08](img/KakaoTalk_20261004_212705926_08.jpg)(i)** |
|                                                              | **![KakaoTalk_20261004_212705926_09](img/KakaoTalk_20261004_212705926_09.jpg)(j)** |                                                              |



#### Discussion

1. **Analyze the result and explain any other necessary discussion.**

While the figures illustrate the 1-second interval up-counting sequence from 0 to 9, the dynamic interrupt responses can be fully confirmed through the video demonstration linked at the top of this document. 

Specifically, the video shows that triggering SW2 pauses and plays the counter by toggling the current `is_paused` state, whereas triggering SW1 executes an immediate reset by clearing the `count` variable to 0.



2. **We can use two different methods to detect an external signal: polling and interrupt. What are the advantages and disadvantages of each approach?**

**Polling Method** 

In the polling approach, the CPU continuously checks the condition of an external signal within the main `while` loop until the specific condition is met.

- **Advantages:**
  - **Simplicity:** It is intuitive and straightforward to implement for simple programs.
- **Disadvantages:**
  - **Inefficient Code Structure:** Since all conditions must be checked sequentially, the main loop becomes long and complex.
  - **Resource Wasting (Busy-waiting):** The CPU continuously wastes resources and power checking for an event even when nothing is happening.
  - **Delayed Response (Latency):** If the main loop contains heavy computations or delays (e.g., `delay_ms()`), the system cannot detect and respond to the external signal immediately.

**Interrupt Method** 

In the interrupt approach, the main loop runs independently. When an external signal is triggered, the hardware pauses the main loop, saves the current location (context), jumps to an Interrupt Service Routine (ISR) to execute the task, clears the pending flag, and returns to the saved location.

- **Advantages:**
  - **Compact Main Loop:** By separating the condition-checking logic into handlers, the main loop becomes much more concise and focused on core algorithms.
  - **Immediate Response (Real-time control):** It guarantees an instantaneous, deterministic response to external signals regardless of the main loop's current state.
  - **High CPU and Power Efficiency:** The CPU does not waste resources checking for signals and can even enter a low-power sleep mode, waking up only when an interrupt occurs.
- **Disadvantages:**
  - **Overhead and Complexity:** It requires a context switching process (saving and restoring states) and a mandatory step to clear pending flags. Also, managing shared variables between the main loop and ISR requires careful design to prevent logic errors.



3. **What would happen if the EXTI interrupt handler does not clear the interrupt pending flag? Check with your code**

If the EXTI interrupt handler does not clear the interrupt pending flag, the microcontroller will assume the interrupt request is still active. Consequently, as soon as the Interrupt Service Routine (ISR) finishes, the CPU will immediately re-enter the handler, creating an infinite ISR loop. This prevents the system from ever returning to the main loop. As verified through actual code testing, pressing the button caused the 7-segment display to freeze immediately, and the up-counter never resumed its operation.