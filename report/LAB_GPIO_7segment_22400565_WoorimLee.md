# LAB: GPIO 7segment

**Date:** 2026-09-20

**Author/Partner:** WoorimLee

**Demo Video:** [[EC 26-2] LAB (GPIO 7segment)](https://youtu.be/reNBhPKHs8o)

**PDF version:** [LAB_GPIO_7segment.pdf](./LAB_GPIO_7segment_22400565_WoorimLee.pdf)



------

## Introduction

In this lab, you are required to create a simple program to control a 7-segment display to show a decimal number (0~9) that increases by pressing a push-button.

- LAB Report (*.pdf)
- Zip source files(lab***.c, ecRCC2.h, ecGPIO2.h etc...).
  - Only the source files. Do not submit project files

### **Requirement**

#### **Hardware**

- MCU
  - NUCLEO-F411RE
- Actuator/Sensor/Others:
  - eval board

#### **Software**

- PlatformIO, CMSIS, EC_HAL library

### Exercise

| **Port/Pin**   | **Description**              | **Register setting**           |
| -------------- | ---------------------------- | ------------------------------ |
| Port B Pin 5   | Clear Pin5 mode              | GPIOB->MODER &=~(3<<(5*2))     |
| Port B Pin 5   | Set Pin5 mode = Output       | GPIOB->MODER \|= (1<<(5*2))    |
| Port B Pin 6   | Clear Pin6 mode              | GPIOB->MODER &=~(3<<(6*2))     |
| Port B Pin 6   | Set Pin6 mode = Output       | GPIOB->MODER \|=(1<<(6*2))     |
| Port B Pin Y   | Clear PinY mode              | GPIOB->MODER &=~(3<<(Y*2))     |
| Port B Pin Y   | Set PinY mode = Output       | GPIOB->MODER \|=(1<<(Y*2))     |
| Port B Pin 5~9 | Clear Pin5~9 mode            | GPIOB->MODER &=~(0x3FF<<(5*2)) |
|                | Set Pin5~9 mode = Output     | GPIOB->MODER \|=(0x155<<(5*2)) |
| Port X Pin Y   | Clear Pin Y mode             | GPIOX->MODER &=~(3<<(Y*2))     |
|                | Set Pin Y mode = Output      | GPIOX->MODER \|=(1<<(Y*2))     |
| Port B Pin5    | Set Pin5 otype=push-pull     | GPIOB->OTYPER &=~(1<<5)        |
| Port B PinY    | Set PinY otype=push-pull     | GPIOB-> OTYPER &=~(1<<Y)       |
| Port B Pin5    | Set Pin5 ospeed=Fast         | GPIOB->OSPEEDR \|=(2<<(5*2))   |
| Port B PinY    | Set PinY ospeed=Fast         | GPIOB-> OSPEEDR \|=(2<<(Y*2))  |
| Port B Pin 5   | Set Pin5 PUPD=no pullup/down | GPIOB->PUPDR &=~(3<<(5*2))     |
| Port B Pin Y   | Set PinY PUPD=no pullup/down | GPIOB-> PUPDR &=~(3<<(Y*2))    |



-----

## Problem 1. Library for 7-segment display on JKIT Board

### Problem

There are four 7-Segment Displays on JKIT board.

- You need to select which one to use.
- There is no BCD decoder
- JKIT - Nucleo 64: [link](https://www.devicemart.co.kr/goods/view?no=14123215&srsltid=AfmBOooT3zgaxGXZ_q0fvy4uZxHesTbwpqNprE6P3YXMk9V0EGoGrhLM)

Complete the required functions that displays numbers on 7-segment FND.(JKIT - Nucleo 64)

These functions are defined and declared in `ecGPIO2.h,ecGPIO2.c`



### Procedure

1. Connect the evaluation board [(JKIT-NUCLEO) ](https://ykkim.gitbook.io/ec/ec-course/hardware/stm32f-evaluation-board#reference-manual)to the MCU.
2. Make sure that your library **ecGPIO2.h, ecGPIO2.c** are in `EC\include\`.
3. Create a new project under the directory `EC\lab\`

- Environment: “**LAB_GPIO_7segment”**
- Source File: ““**LAB_GPIO_7segment.c”**

4. You must modify the `platformio.ini` **,** to add new environment.



### **Configuration**

| Function                       | Port - Pin                                                   | Configuration                 |
| ------------------------------ | ------------------------------------------------------------ | ----------------------------- |
| Selection of 7-Segment Display | PA_10, PA_11, PC_4, PC_3<br />(FND_0~FND_3)                  | DOUT, Push-Pull               |
| 7-Segment LEDs                 | PB_0, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7<br />('a'~'g''dot', respectively) | DOUT, Push-Pull, Medium Speed |



### **Code**

`ecGPIO2.h`

```c
extern int numberFND[12][8];
```

A 2D array containing the HIGH/LOW logic patterns for the 8 segments (a-g, dp) to display numbers (0-9) and specific characters.

```c
void FND_init(PinName_t *pinFND);
void FND_display_init(PinName_t *pinFND);
```

Initializes the 8 GPIO pins connected to the individual segments of the display as output mode.

```c
void FND_select_init(PinName_t *selectFND);
```

Initializes the 4 GPIO pins used for digit selection (FND0 to FND3) as output mode.

```c
void FND_display(uint8_t num);
```

Outputs the corresponding segment pattern from `numberFND` to the display pins to show a specific number (0-9).

```c
void FND_select(uint8_t digit);
```

Selects and activates one of the four 7-segment modules (0 to 3) by controlling the digit select pins. Essential for multiplexing.



`ecGPIO2.c`

```c
//Each led that has to light up gets a 1, every other led gets a 0
//its in order  { (a,b,c,d,e,f,g,dp) }
int numberFND[12][8]={
                    {1,1,1,1,1,1,0,0},          // zero
                    {0,1,1,0,0,0,0,0},          // one
                    {1,1,0,1,1,0,1,0},          // two
                    {1,1,1,1,0,0,1,0},          // three
                    {0,1,1,0,0,1,1,0},          // four 
                    {1,0,1,1,0,1,1,0},          // five
					{1,0,1,1,1,1,1,0},          // six
					{1,1,1,0,0,1,0,0},          // seven
					{1,1,1,1,1,1,1,0},          // eight
					{1,1,1,0,0,1,1,0},          // nine
                    {0,0,0,0,0,0,0,1},          //dot
                   	{0,0,0,0,0,0,0,0}  	        //blank
                  };
```

A lookup table, structured like a spreadsheet, that predefines which LEDs to turn on (1) or off (0) to draw a number.

```c
// Initialize DOUT pins for 7 segment leds
void FND_init(PinName_t *pinFND){
	for (int i=0; i<8; i++){
		_fndPins[i] = pinFND[i];
		GPIO_init(_fndPins[i], OUTPUT);
	}
}
```

Copies the pin array (`PB_0` ~ `PB_7`) passed from the `main` function into the internal variable `_fndPins` and initializes all of these pins to OUTPUT mode.

```c
// Initialize select pins (FND0~FND3) as DOUT
void FND_select_init(PinName_t *selectFND){	
    for (int i=0; i<4; i++){
		_fndSel[i] = selectFND[i];
		GPIO_init(_fndSel[i], OUTPUT);
	}
}
```

Copies the pins used for digit selection (e.g., `PA_10`, `PA_11`) into the internal variable `_fndSel` and initializes them to OUTPUT mode.

```c
// Display a number 0 - 9 only
void FND_display(uint8_t num){
	for (int i=0; i<7; i++){
		GPIO_write(_fndPins[i], numberFND[num][i]);
	}
}
```

Receives the number to output (`num`) and writes the predefined pattern of 1s and 0s from the array to the actual physical pins using `GPIO_write()`.

```c
// Select display: FND0 to FND3
void FND_select(uint8_t digit){
	for(int i=0; i<3; i++)
		GPIO_write(_fndSel[i], LOW);
	GPIO_write(_fndSel[digit], HIGH);
}
```

To perform multiplexing, it first turns off all digit displays (LOW), then activates only the specific module by setting the pin of the passed `digit` to HIGH.



`LAB_GPIO_7segment.c`

```c
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
 
    uint8_t numDisplay1  = 0;
    uint8_t numDisplay2  = 5;
    uint8_t selectFND1  = 0;
    uint8_t selectFND2  = 1;
    
    // Problem 1
    while (1) {
        FND_select(selectFND1);
        FND_display(numDisplay1);
        delay_ms_HSI(1);             		
        FND_select(selectFND2);
        FND_display(numDisplay2);
        delay_ms_HSI(1);	
    }
}
```

**Setup:** Initializes GPIO pins for the 7-segment display and digit selection.

**Multiplexing:** Alternates between displaying '0' (first digit) and '5' (second digit).

**Result:** Uses a 1 [ms] delay to make both numbers appear simultaneously lit.



### Results and Discussion

#### Results

<img src="img/KakaoTalk_20260921_003617432.jpg" alt="KakaoTalk_20260921_003617432" style="zoom:15%;" />

<center>Verification of the 7-segment display operation.</center>

The 7-segment display successfully output the number "50".



#### Discussion

1. Analyze the result and explain any other necessary discussion.

**Analyze the result**

Through multiplexing with a 1 ms interval, the two-digit number "50" was stably output on the 7-segment display, appearing to be simultaneously illuminated without any visible flickering. A clear display output was confirmed, free from any afterimages or ghosting.



**Multiplexing and Persistence of Vision** 

The two-digit number "50" was successfully output on the 7-segment display, appearing as though both digits were illuminated simultaneously. In reality, this was achieved by rapidly alternating between the first and second digits at a very short interval of 1 ms. This demonstrates the principle of multiplexing, which switches the active displays faster than the human eye can detect, creating an optical illusion that multiple numbers are turned on at the same time.



--------

## Problem 2: Counter with Button Press

### Procedure

Create a code that increases the displayed number from 0 to 9 with each button press.

- After the number '9', it should start from '0' again.
- Modify from Problem 1 source code



### Configuration

Configure the MCU GPIO

| Function                       | Port - Pin                                                   | Configuration                                 |
| ------------------------------ | ------------------------------------------------------------ | --------------------------------------------- |
| Button (SW2) on JKIT           | PA_4                                                         | DIN, Pull-Up                                  |
| 7-Segment DOUT                 | PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7<br />('a'~'g''dot', respectively) | Push-Pull, No Pull-up-Pull-down, Medium Speed |
| Selection of 7-Segment Display | PA_10 (FND_0)                                                | DOUT, Push-Pull                               |



### **Code**

```c
PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};
PinName_t button_pin = PA_4;

int main(void) {
    setup();

    int Count = 0;
    int buttonState = 0;
    int prev_buttonState = 1;
    uint8_t selectFND = 0;

    // Problem 2
    while (1) {
        FND_select(selectFND);
        buttonState = GPIO_read(button_pin);
		if(buttonState == 0 && prev_buttonState == 1) {
            Count++;
            FND_display(Count % 10);
            prev_buttonState = buttonState;
        }
        else if(buttonState == 1) {
            FND_display(Count % 10);
            prev_buttonState = 1;
        }
    }
}
```

This code implements a single-digit counter controlled by a push-button. It utilizes falling-edge detection (`buttonState == 0 && prev_buttonState == 1`) to ensure the counter increments exactly once per physical button press, effectively handling potential bouncing issues. The counter value is restricted to a single digit (0-9) using the modulo operator (`Count % 10`) and is continuously displayed on the first 7-segment module.



### Results and Discussion

#### Results

| <img src="img/KakaoTalk_20260921_003617432_01.jpg" style="zoom:15%;" />(a) | <img src="img/KakaoTalk_20260921_003617432_02.jpg" alt="KakaoTalk_20260921_003617432_02" style="zoom:15%;" />(b) | <img src="img/KakaoTalk_20260921_003617432_03.jpg" style="zoom:15%;" />(c) |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| <img src="img/KakaoTalk_20260921_003617432_04.jpg" alt="KakaoTalk_20260921_003617432_04" style="zoom:15%;" />**(d)** | <img src="img/KakaoTalk_20260921_003617432_05.jpg" alt="KakaoTalk_20260921_003617432_05" style="zoom:15%;" />**(e)** | <img src="img/KakaoTalk_20260921_003617432_06.jpg" alt="KakaoTalk_20260921_003617432_06" style="zoom:15%;" />**(f)** |
| <img src="img/KakaoTalk_20260921_003617432_07.jpg" alt="KakaoTalk_20260921_003617432_07" style="zoom:15%;" />**(g)** | <img src="img/KakaoTalk_20260921_003617432_08.jpg" alt="KakaoTalk_20260921_003617432_08" style="zoom:15%;" />**(h)** | <img src="img/KakaoTalk_20260921_003617432_09.jpg" alt="KakaoTalk_20260921_003617432_09" style="zoom:15%;" />**(i)** |
| <img src="img/KakaoTalk_20260921_003617432_10.jpg" alt="KakaoTalk_20260921_003617432_10" style="zoom:15%;" />**(j)** | <img src="img/KakaoTalk_20260921_003617432_11.jpg" alt="KakaoTalk_20260921_003617432_11" style="zoom:15%;" />**(k)** | <img src="img/KakaoTalk_20260921_003617432_02.jpg" alt="KakaoTalk_20260921_003617432_02" style="zoom:15%;" />**(l)** |

<center>7-segment display incrementing from 0 to 9 with each button press.</center>

The sequence of images demonstrates the step-by-step operation of the counter. Each time the push-button is pressed, the 7-segment display successfully increments the number by one, counting sequentially from 0 to 9.



#### Discussion

1. Analyze the result and explain any other necessary discussion.

**Analyze the result**

It was verified that the number on the display accurately increments by 1, circulating from 0 to 9 each time the push-button is pressed. The falling-edge detection logic functioned correctly, ensuring that exactly one input was registered without malfunction, even during switch bouncing or when the button was held down continuously.

**Necessity of Edge Detection** 

The reason the number increments only once—rather than skyrocketing continuously while the button is held down—is due to the implementation of falling-edge detection logic. Instead of a simple polling method that merely checks if the pin state is LOW, the core of accurate counter control lies in comparing the previous state (`prev_buttonState`) with the current state to isolate the exact moment the button is pressed as a single, discrete event.

**State Circulation via Modulo Operation** 

A single 7-segment display can only represent values from 0 to 9. By applying a modulo operation (`Count % 10`) before passing the continuously increasing `Count` variable to the display function, a stable Finite State Machine (FSM) was implemented. This ensures that after reaching 9, the state naturally wraps around to 0 without causing overflow or outputting corrupted characters.



----

### Discussion

2. What are the common cathode and common anode of 7-segment display?

**Common Cathode**

The cathodes (-) of the 8 internal LEDs in the 7-segment display are all tied together to a single common pin connected to GND. The MCU must output a 'HIGH (1)' signal to the respective LED pin to turn it on. This is the configuration used in the current evaluation board (JKIT).

**Common Anode** 

The anodes (+) of the internal LEDs are tied together to a single common pin connected to VCC (5V or 3.3V). The MCU must output a 'LOW (0)' signal to allow current to flow and turn the LED on.



3. Does the LED of a 7-segment display (common anode) pin turn ON when 'HIGH' is given to the LED pin from the MCU?

**Answer:** No.

**Explanation:** In a Common Anode configuration, the common pin is already connected to VCC (high voltage). If the MCU also outputs a 'HIGH' signal to the LED pin, both ends will have the same voltage, resulting in a potential difference of 0V. Consequently, no current flows, and the LED remains off. To turn the LED on, the MCU must set the pin state to 'LOW' (acting as GND) to complete the circuit.



4. How can we display 4 digit-numbers on the 4 FNDS at the same time? How to remove ghosting of displaying a number?

**The Ghosting Phenomenon** 

Ghosting occurs during multiplexing when the data from the previously displayed digit is not fully cleared before transitioning to the next digit, leaving a faint afterimage or blur on the new position.

**How to Remove Ghosting**

To prevent this, a "blanking" process is required to temporarily turn off all FND selection pins right before switching to the next digit. In the lab code's `FND_select` function, the `for` loop that sets all pins to 'LOW' before pulling a specific pin 'HIGH' is the core logic designed to completely eliminate this ghosting effect.

**Displaying 4 Digits Simultaneously Method** 

The four FNDs are not physically turned on all at once. Instead, a Time Division Multiplexing technique is utilized. By rapidly and continuously repeating the cycle of turning on the 1s digit ➔ waiting briefly ➔ turning on the 10s digit ➔ waiting briefly ➔ and so forth, the human eye's Persistence of Vision creates the optical illusion that all four digits are illuminated simultaneously.