# LAB: GPIO 7segment

**Date:** 2026-09-20

**Author/Partner:** WoorimLee

**Demo Video:** [[EC 26-2] LAB (GPIO 7segment)](https://youtu.be/reNBhPKHs8o)

**PDF version:**



------

## Introduction

In this lab, you are required to create a simple program to control a 7-segment display to show a decimal number (0~9) that increases by pressing a push-button.

You must submit

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

4. You must modify the `**platformio.ini**` **,** to add new environment.



### **Configuration**

| Function                       | Port - Pin                                                   | Configuration                 |
| ------------------------------ | ------------------------------------------------------------ | ----------------------------- |
| Selection of 7-Segment Display | PA_10, PA_11, PC_4, PC_3<br />(FND_0~FND_3)                  | DOUT, Push-Pull               |
| 7-Segment LEDs                 | PB_0, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7<br />('a'~'g''dot', respectively) | DOUT, Push-Pull, Medium Speed |



### **Code**

```
// FND for JKIT board 
extern int numberFND[12][8];
void FND_init(PinName_t *pinFND);
void FND_select_init(PinName_t *selectFND);
void FND_display(uint8_t num);
void FND_select(uint8_t digit);

// Display a number 0 - 9 only
void FND_display_init(PinName_t *pinFND);
//void FND_display(uint8_t  num, PinName_t *pinFND)

// Select display: FND0 to FND3
void FND_select_init(PinName_t *selectFND);
//void FND_select(uint8_t select, PinName_t *selectFND);
```



```
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
                    {0,0,0,0,0,0,0,1},           //dot
                   	{0,0,0,0,0,0,0,0}  	        //blank
                  };

// Initialize DOUT pins for 7 segment leds
void FND_init(PinName_t *pinFND){
	for (int i=0; i<7; i++){
		_fndPins[i] = pinFND[i];
		GPIO_init(_fndPins[i], OUTPUT);
	}
}

// Initialize select pins (FND0~FND3) as DOUT
void FND_select_init(PinName_t *selectFND){	
    for (int i=0; i<3; i++){
		_fndSel[i] = selectFND[i];
		GPIO_init(_fndSel[i], OUTPUT);
	}
}

// Display a number 0 - 9 only
void FND_display(uint8_t num){
	for (int i=0; i<7; i++){
		GPIO_write(_fndPins[i], numberFND[num][i]);
	}
}

// Select display: FND0 to FND3
void FND_select(uint8_t digit){
	for(int i=0; i<3; i++)
		GPIO_write(_fndSel[i], LOW);
	GPIO_write(_fndSel[digit], HIGH);
}
```



```
PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};
PinName_t button_pin = PA_4;

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



### Results and Discussion

#### Results

<img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432.jpg" alt="KakaoTalk_20260921_003617432" style="zoom:15%;" />

#### Discussion



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

```
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





### Connection Diagram

Circuit diagram (if needed)



### Results and Discussion

#### Results

| <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_01.jpg" style="zoom:15%;" />(a) | <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_02.jpg" alt="KakaoTalk_20260921_003617432_02" style="zoom:15%;" />(b) | <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_03.jpg" style="zoom:15%;" />(c) |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_04.jpg" alt="KakaoTalk_20260921_003617432_04" style="zoom:15%;" />**(d)** | <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_05.jpg" alt="KakaoTalk_20260921_003617432_05" style="zoom:15%;" />**(e)** | <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_06.jpg" alt="KakaoTalk_20260921_003617432_06" style="zoom:15%;" />**(f)** |
| <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_07.jpg" alt="KakaoTalk_20260921_003617432_07" style="zoom:15%;" />**(g)** | <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_08.jpg" alt="KakaoTalk_20260921_003617432_08" style="zoom:15%;" />**(h)** | <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_09.jpg" alt="KakaoTalk_20260921_003617432_09" style="zoom:15%;" />**(i)** |
| <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_10.jpg" alt="KakaoTalk_20260921_003617432_10" style="zoom:15%;" />**(j)** | <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_11.jpg" alt="KakaoTalk_20260921_003617432_11" style="zoom:15%;" />**(k)** | <img src="../../LAB_GPIO_7segment_22400565/report/img/KakaoTalk_20260921_003617432_02.jpg" alt="KakaoTalk_20260921_003617432_02" style="zoom:15%;" />**(l)** |



#### Discussion





----

### Discussion

1. Analyze the result and explain any other necessary discussion.
2. What are the common cathode and common anode of 7-segment display?

> Answer discussion questions

1. Does the LED of a 7-segment display (common anode) pin turn ON when 'HIGH' is given to the LED pin from the MCU?

> Answer discussion questions

1. How can we display 4 digit-numbers on the 4 FNDS at the same time? How to remove ghosting of displaying a number?

> Answer discussion questions