# LAB: GPIO Digital InOut

**Date:** 2026-09-18

**Author/Partner:** Woorim-Lee

**Demo Video:** [[EC 26-2] LAB (GPIO Digital InOut)](https://youtu.be/pcD9_yLGIN8)

**PDF Version:** [LAB_GPIO_Digital_InOut.pdf](./LAB_GPIO_Digital_InOut.pdf)




---


## Introduction


In this lab, you are required to create a simple program that toggles multiple LEDs using a push-button input.


You must create your own drivers for GPIO digital input and output control.


You must submit


- LAB Report (*.pdf)
- Zip source files(main.c, ecRCC.h, ecGPIO.h etc...).

  - Only the source files.
  - Do not submit project files

### Requirement


#### Hardware


- MCU
  - NUCLEO-F411RE
- Eval Board
- Actuator/Sensor/Others:


#### Software


- PlatformIO, CMSIS, EC_HAL library

  


---


## Problem 0: STM-Arduino

### Problem

We are going to create a simple program that turns LED(LD2) on and off by pressing the user button(BT1), using Arduino Syntax.



### Procedure

Create a new project under the directory `\repos\EC\lab\`

- The project folder name is “**\LAB_GPIO_DIO_LED”.**

Configures the specified pin to behave either as an input or an output.

```
pinMode(pin, mode)
```

- pin: the pin number to set the model of.
- mode: INPUT, OUTPUT or INPUT_PULLUP.

The user button pin is `PC13`, but this pin cannot be used in arduino. So, you should connect `PC13` to `pinName` `D3` by using wire.




### Code

```
const int btnPin = 3;				// Button pin
const int ledPin = 13;				// LED pin

int btnState = HIGH;				// Button state

void setup() {
  pinMode(ledPin, OUTPUT);			// Set LED as output
  pinMode(btnPin, INPUT);			// Set button as intput
}

void loop() {
  btnState = digitalRead(btnPin);	// Read button

  if (btnState == HIGH) 			// If not pressed
    digitalWrite(ledPin, LOW);		// LED OFF (Active Low)
  
  else 								// If pressed
    digitalWrite(ledPin, HIGH);		// LED ON (Active-Low)
}
```



### Results and Discussion

#### Results

Pressing the button successfully turned on LED2.

<img src="../../LAB_GPIO_Digital_InOut_22400565/report/img/KakaoTalk_20260920_020742679_01.jpg" alt="KakaoTalk_20260920_020742679_01" style="zoom:15%;" />

<img src="../../LAB_GPIO_Digital_InOut_22400565/report/img/KakaoTalk_20260920_020742679.jpg" alt="KakaoTalk_20260920_020742679" style="zoom:15%;" />

<center>Fig 1. Pressing BT1 turned ON LED0</center>




#### Consideration

**Arduino API Limitations:** Confirmed platform constraints where the PC13 pin could not be directly controlled via the provided library, requiring a physical bypass to the D3 pin using a jumper wire.

**Active-Low & Pull-up Resistor:** Verified the presence of a pull-up resistor in the circuit, as pressing the button generated a `LOW` input signal.

**Hardware Debouncing Verification:** Demonstrated the effectiveness of the NUCLEO board's built-in RC hardware filter, which successfully eliminated mechanical noise without requiring software-based delay logic.




---


## Problem 1: Create EC_HAL library


### Procedure

#### Prepare Library Files

The provided library files were saved in the `\repos\EC\include\` directory to prevent duplication across project folders. To construct a custom GPIO library, the downloaded `ecGPIO2_student.*` files were renamed to `ecGPIO2.c` and `ecGPIO2.h`, and their internal include paths were updated.



#### GPIO Library Implementation

The `ecGPIO2.c` library was implemented using register bitwise operations to configure and control the GPIO pins. The specific roles of each function are as follows:

- **`GPIO_mode`**: Configures the pin direction (Input, Output, Alternate Function, or Analog) by modifying the `MODER` register.

- **`GPIO_ospeed`**: Sets the output signal speed (Low, Medium, Fast, or High) through the `OSPEEDR` register.

- **`GPIO_otype`**: Configures the output type as either Push-Pull or Open-Drain using the `OTYPER` register.

- **`GPIO_pupd`**: Activates the internal pull-up or pull-down resistors via the `PUPDR` register.

- **`GPIO_write`**: Writes a digital HIGH (1) or LOW (0) state to the specific pin using the Output Data Register (`ODR`).

- **`GPIO_read`**: Reads the current digital input state of the pin from the Input Data Register (`IDR`).

  

**ecGPIO2.h**

```
void GPIO_init(PinName_t pinName, uint32_t mode);     
void GPIO_mode(PinName_t pinName, uint32_t mode);
void GPIO_ospeed(PinName_t pinName, uint32_t speed);
void GPIO_otype(PinName_t pinName, uint32_t type);
void GPIO_pupd(PinName_t pinName, uint32_t pupd);
void GPIO_write(PinName_t pinName, uint32_t Output);
uint32_t  GPIO_read(PinName_t pinName);
```



**ecGPIO2.c**

```
// GPIO Mode          : Input(00), Output(01), AlterFunc(10), Analog(11)
void GPIO_mode(PinName_t pinName, uint32_t mode){
   GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);

   Port->MODER &= ~(3UL<<(2 * pin));     
   Port->MODER |= mode<<(2 * pin);    
}

// GPIO Speed          : Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
void GPIO_ospeed(PinName_t pinName, uint32_t speed){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	Port->OSPEEDR &= ~(3UL<<(2 * pin));
	Port->OSPEEDR |= (speed<<(2 * pin));
}

// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
void GPIO_otype(PinName_t pinName, uint32_t type){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	Port->OTYPER &= (type<<(pin));
}

// GPIO Push-Pull    : No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
void GPIO_pupd(PinName_t pinName, uint32_t pupd){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	Port->PUPDR &= ~(3UL << (2 * pin));
   	Port->PUPDR |= (pupd<<(2 * pin));
}

void GPIO_write(PinName_t pinName, uint32_t Output){
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);

	if(Output == 1)
		Port->ODR |= (1UL << pin);
	else
		Port->ODR &= ~(1UL << pin);
}

uint32_t GPIO_read(PinName_t pinName){
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	unsigned int val;
	   	val = (((Port->IDR) >> pin) & 1);
		return val;
}
```



#### Consideration

**Safe Bitwise Operations:** Learned the critical importance of the Read-Modify-Write sequence. It is essential to clear specific bits using `&= ~` before setting them with `|=` to prevent unintended modifications to adjacent pins sharing the same register.

**Code Modularity & Reusability:** Improved software maintainability by structuring the custom HAL as modular `.c` and `.h` files in a shared directory, preventing code duplication across future lab projects.




---


## Problem 2: Toggle a single LED with Digital Sensor(Photodetector)


### Problem


Toggle the LED by covering the photodetector sensor.


- Dark (LED ON), Bright (LED OFF) and repeat

- Connect the Photodetector sensor to PA_0 pin on Nucleo Board.

  


### Procedure


1. Connect the evaluation board (JKIT-NUCLEO) to the MCU.
2. Make sure that your library ecGPIO2.h, ecGPIO2.c are in EC\include\.
3. Create a new project under the directory EC\lab\


- Environment: “LAB_GPIO_DIO_LED_Photosensor”.
- Source File: “LAB_GPIO_DIO_LED_Photosensor.c”


1. You must modify the **platformio.ini** , to add new environment.

   


### Configuration


Configure the MCU GPIO


| Function | Port-Pin | Configuration |
| --- | --- | --- |
| Photodetector on JKIT | PA_0 | Digital IN, Pull-Up |
| LED_0 | PB_12 | Digital OUT, Pull-UP, Open-Drain, Medium Speed |



### Code

Code for hardware initialization.

```
#define LED_PIN PB_12								// LED pin
#define BUTTON_PIN PA_0								// Button pin

// Initialiization 
void setup(void) {
	RCC_HSI_init();									// Init clock
	// initialize the pushbutton pin as an input:	
	GPIO_init(BUTTON_PIN, INPUT);  					// Set button as input
	// initialize the LED pin as an output:
	GPIO_init(LED_PIN, OUTPUT);    					// Set LED as output
}
```

Main execution code for LED control.

```
int main(void) { 
 	setup();				// Init system
	int buttonState=0;		// Read whether press button
	
	while(1){
		// check if the pushbutton is pressed. Turn LED on/off accordingly:
		buttonState = GPIO_read(BUTTON_PIN);			// Read button
		if(buttonState)	GPIO_write(LED_PIN, LOW);		// If HIGH
		else 		GPIO_write(LED_PIN, HIGH);			// If LOW
		delay_ms_HSI(100);             					// delay 100 ms
	}
}
```



### Results and Discussion

#### Results

Blocking the light from the Photodetector successfully toggled LED0 on.

<img src="../../LAB_GPIO_Digital_InOut_22400565/report/img/EC_LAB1_Pr2_1.jpg" alt="EC_LAB1_Pr2_1" style="zoom:15%;" />

<img src="../../LAB_GPIO_Digital_InOut_22400565/report/img/EC_LAB1_Pr2_2.jpg" alt="EC_LAB1_Pr2_2" style="zoom:15%;" />

<center>Fig 2. LED0 turned ON when the photodetector is blocked.</center>



#### Consideration

**Digital Sensor Integration:** Confirmed that the photodetector module successfully converts analog environmental data (light intensity) into a discrete digital signal (HIGH/LOW) using its built-in comparator, allowing the MCU to process it via the PA_0 pin.

**Build Environment Management:** Modifying `platformio.ini` provided hands-on experience in managing multiple build environments and source files within a single project repository.




---


## Problem 3: Toggle multiple LEDs with a button


### Problem


Use the four LEDs (LED0 to LED3) on the JKIT evaluation board.


Each time Button B1 is pressed, turn on one LED at a time in a sequential loop


- e.g., LED0 -> LED1 -> LED2 -> LED3 -> LED0

  


### Procedure


1. Connect the evaluation board (JKIT-NUCLEO) to the MCU.
2. Make sure that your library ecGPIO2.h, ecGPIO2.c are in EC\include\.
3. Create a new project under the directory EC\lab\


- Environment: “LAB_GPIO_DIO_multiLED”
- Source File: ““LAB_GPIO_DIO_multiLED.c”

4. You must modify the **platformio.ini** , to add new environment.




### Configuration


| Function | Port-Pin | Configuration |
| --- | --- | --- |
| SW2 on JKIT | PA_4 | Digital IN, Pull-Up |
| LED_0~LED_3 | PB_12, PB_13, PB_14, PB_15 | Digital OUT, Pull-UP, Open-Drain, Medium Speed |



### Code

Code for initializing the button and 4 LEDs.

```
// Initialization 
void setup(void)
{
	RCC_HSI_init();								// Init clock

	// Configuration button pin
	GPIO_init(button_pin, INPUT);  				// Set button as input

	// Configuration LED pins
	for(int i=0; i<(sizeof(LED_PIN)/sizeof(LED_pin[0])); i++){
		GPIO_init(LED_pin[i], OUTPUT);			// Set LEDs as output
	}	
}
```

Main execution code for sequential LED toggling.


```
PinName_t LED_pin[4] = {PB_12, PB_13, PB_14, PB_15}; 	// LED pins
PinName_t button_pin = PA_4;							// Button pin

void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();											  // Init system
	int count = 3;										  // LED index
	int buttonState = 0;								  // Current state
	int prev_buttonState = 0;							  // Previous state
	
	// Inifinite Loop ---------------------------------------------------------
	while(1){
		 buttonState = GPIO_read(button_pin);			  // Read button
		 if (buttonState == 0 && prev_buttonState == 1){  // If pressed (edge)
			GPIO_write(LED_pin[count % 4],LOW); 		  // Current LED OFF
			count++;									  // Init system
			GPIO_write(LED_pin[(count % 4)],HIGH);		  // Next LED ON
			prev_buttonState = buttonState;				  // Update state
		 }
		 else if(buttonState == 1){						  // If released
			prev_buttonState = 1;						  // Update state
		 }
	}
}
```



### Results and Discussion

#### Results

It was observed that the LEDs toggled sequentially in the order of LED0 -> LED1 -> LED2 -> LED3 -> LED0.

<img src="../../LAB_GPIO_Digital_InOut_22400565/report/img/pr3_1.jpg" alt="pr3_1" style="zoom:15%;" />

<img src="../../LAB_GPIO_Digital_InOut_22400565/report/img/pr3_2.jpg" alt="pr3_2" style="zoom:15%;" />

<img src="../../LAB_GPIO_Digital_InOut_22400565/report/img/pr3_3.jpg" alt="pr3_3" style="zoom:15%;" />

<img src="../../LAB_GPIO_Digital_InOut_22400565/report/img/pr3_4.jpg" alt="pr3_4" style="zoom:15%;" />

<img src="../../LAB_GPIO_Digital_InOut_22400565/report/img/pr3_5.jpg" alt="pr3_5" style="zoom:15%;" />

<center>Fig 3. Sequential LED toggling operation using user button B1.</center>



#### Consideration

**Cyclic State Management:** Successfully implemented sequential logic using a counter variable and the modulo operator (`count % 4`), which is an efficient and clean method to handle cyclical state transitions without complex `if-else` structures.

**Edge Detection Importance:** Realized that reading the button state requires detecting the exact moment of pressing (edge detection) rather than simply checking if it is held down (level detection). Otherwise, the rapid processing speed of the MCU would cause the LEDs to cycle uncontrollably fast.



---------

#### Discussion

**1. Find out a typical solution for software debouncing and hardware debouncing.**

**Bouncing Phenomenon:** 

Bouncing is a phenomenon where the metal contacts inside a switch rapidly bounce and make or break the connection multiple times due to micro-vibrations when pressed. While a human perceives it as a single press, a high-speed MCU incorrectly registers it as dozens of consecutive presses.

**Debouncing:** 

Debouncing refers to the technical measures taken to filter out this mechanical noise, ensuring the input is accurately recognized as a single press without malfunction.



**Hardware Debouncing:**

* It is a method of adding physical electronic components between the switch and the MCU pin to clean and smooth out the bouncing electrical signal before sending it to the MCU.

* **Typical Solution:** 

  The most common approach is implementing an RC filter circuit composed of a resistor and a capacitor. It utilizes the capacitor's charging and discharging characteristics to smoothly absorb sharp voltage spikes.

**Software Debouncing:**

* It is a method of programming the MCU to ignore noise purely through coding (algorithms) without adding any physical components to the board.

* **Typical Solution:** 

  When a button press is first detected, a short time delay (usually 10 to 50 ms) is introduced to ignore additional signals while the metal contacts bounce and stabilize. After this delay period, the logic checks again to see if the pin state remains pressed, validating it as a genuine input.



**2.  What method of debouncing did this NUCLEO board use for the push-button(B1)?**

The user button (B1) on the NUCLEO board utilizes **hardware debouncing**. Specifically, the board's internal schematic includes a built-in **RC filter circuit** connected to the button, which physically eliminates mechanical chattering before the electrical signal reaches the microcontroller pin.

