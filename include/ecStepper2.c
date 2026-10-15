/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Woorim-Lee
Created          : 05-03-2021
Modified         : 10-14-2026
Language/ver     : C++ in VS Code

Description      : Stepper Library File
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "ecStepper2.h"


// Stepper Motor variable
static PinName_t stepperPins[4];
const uint32_t STEP_PER_REV[2] = {4096, 2048};
static volatile uint32_t _steps;
static volatile uint32_t _mode;
static volatile uint32_t _step_delay = 100;		
static const StateStepper_t *fsm;				// points at fsm_full or fsm_half (chosen in stepper_init)
static volatile uint32_t state = 0;				// current FSM state



// Output: A B A' B'
static const StateStepper_t fsm_Full[4] = {	
 {{S1,S3},{HIGH,HIGH,LOW,LOW}},	
 {{S2,S0},{HIGH,LOW,LOW,HIGH}},
 {{S3,S1},{LOW,LOW,HIGH,HIGH}},	
 {{S0,S2},{LOW,HIGH,HIGH,LOW}},
};


static const StateStepper_t fsm_Half[8] = {  
	// 1000 , 1010 , 0010 , 0110 , 0100 , 0101, 0001, 1001
	{{S1, S7}, {HIGH, LOW, LOW, LOW }}, // S0 
	{{S2, S0}, {HIGH, LOW, LOW, HIGH }}, // S1 
	{{S3, S1}, {LOW, LOW, LOW, HIGH }}, // S2 
	{{S4, S2}, {LOW, LOW, HIGH, HIGH }}, // S3 
	{{S5, S3}, {LOW, LOW, HIGH, LOW }}, // S4 
	{{S6, S4}, {LOW, HIGH, HIGH, LOW}}, // S5 
	{{S7, S5}, {LOW, HIGH, LOW, LOW}}, // S6 
	{{S0, S6}, {HIGH, HIGH, LOW, LOW}}
};


// Initialization of Stepper Motor
void stepper_init(uint32_t mode, PinName_t *pinStepper){
	if (mode == HALF) 
		fsm = fsm_Half;
	else
		fsm = fsm_Full;

	_mode = mode;                                               // Stores the selected operating mode (HALF or FULL)

	//  GPIO Digital Out Initiation
	// For A, B, AN, BN

	for (int i=0; i<4; i++){
		stepperPins[i] = pinStepper[i];                             
		GPIO_init(stepperPins[i], OUTPUT);						 // Initializes the assigned stepper motor pins as digital outputs
	}
}

// Converts Motor [rpm] to step delay in [msec]
void stepper_speed (uint32_t speedRPM){                          // rpm
		_step_delay = 60*1000/(STEP_PER_REV[_mode]*speedRPM);    //in [msec]	
		// [usec] can be used for a higher accuracy 
}		  

// Run Stepper Motor for given steps and direction
void stepper_step(uint32_t steps, uint32_t direction){
	// Exit if stepper_init() not called 
	if (fsm == 0) return;
	_steps = steps;												 // Stores the target number of steps

	// run for step size: 
	for (uint32_t i = 0; i < _steps; i++){
		// Update Present State
		state = fsm[state].next[direction];						 // Updates the FSM state based on the current row and target direction column
		
		// Output of Present State
		stepper_out(state);										 // Outputs the 4-bit sequence corresponding to the current state
	
		// Delay for steppermotor speed
		delay_ms(_step_delay);
	}
}

// Stepper Motor Output for given state
void stepper_out(uint32_t state){
	
	// stepperPins[0]=A, stepperPins[1]=B, ...
	// out[0]=A, out[1]=B, ...

	// Writes the corresponding FSM output logic to the stepper pins
	for (int i=0; i<4; i++) GPIO_write(stepperPins[i], fsm[state].out[i]); 
}


// Stop Stepper Motor
void stepper_stop(void) {
    _steps = 0;    
    // All pins DigitalOut '0'
	for (int i=0; i<4; i++) GPIO_write(stepperPins[i], 0); 		// Halts the motor by setting all stepper pins to LOW (0)
}



