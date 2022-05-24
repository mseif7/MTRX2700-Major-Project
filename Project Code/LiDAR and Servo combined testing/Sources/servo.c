
#include "derivative.h"
#include <math.h> 
#include "servo.h"

// Setting initial position of servos
#define ZERO_ELEVATION_DUTY 3800
#define ZERO_AZIMUTH_DUTY 3800

// PWM:
// - 0 deg = 1500 us
// - 1 deg = 10 us

// ZERO_ELEVATION_DUTY angles:
// - 4600 = max tilt up
// - 3800 = around middle
// - 3200 = 30 deg down from 3800
// - 2600 = 45 deg down from 3800
// - 2000 = 75 deg down from 3800
 

// ZERO_ELEVATION_DUTY angles:
// - 2000 is 45 degrees from horizontal
// - 2400 is 90 degrees from horizontal

// variables to make the servo move back and forth
long iterator_counter_azimuth = 0; 
long iterator_counter_elevate = 0;
int toggle = 0;
int rows = 0;
int lastServoPosition = 0;
int pos_counter = 1;

// Variables that can be changed to fit other shelves
// however, these values should be taken from the struct
int MAX_ROWS = 3;
int MAX_COLS = 3;
int MAX_TIME = 2600;

void PWMinitialise(void){
    // set PP5 and PP7 for pwm output 
    PWMCLK = 0; // select clock A
    PWMPOL = 0xA0; // PWM5 and PWM7 output start high
    PWMCTL = 0xC0; // 16-bit PWM: use PWM4 and PWM5 for PWM5, PWM6 and PWM7 for PWM7
    PWMCAE = 0; // Center aligned
    PWMPRCLK = 0x33; // PWM Clock prescaler to 8 

    // set the PWM period appropriate for servos
    PWMPER45 = 0xEA6A;
    PWMPER67 = 0xEA6A;

    // set the initial duty cycle for both servos
    PWMDTY45 = ZERO_ELEVATION_DUTY;
    PWMDTY67 = ZERO_AZIMUTH_DUTY;
    
    PWME  |= 0xFF;      // enable PWM0
}

void setServoPose(int azimuth, int elevation){  
    PWMDTY45 = (int)(ZERO_ELEVATION_DUTY + elevation);  // Sets elevation to duty cycle using PWM 45
    PWMDTY67 = (int)(ZERO_AZIMUTH_DUTY + azimuth);   // Sets azimuth to duty cycle using PWM 67
}


// initialise the timer and prescaler 
void Init_TC6 (void) {
  TSCR1_TEN = 1;
  
  TSCR2 = 0x00;   // prescaler 1, before 32 = 0x04
  TIOS_IOS6 = 1;   // set channel 6 to output compare
    
  TCTL1_OL6 = 1;    // Output mode for ch6
  TIE_C6I = 1;   // enable interrupt for channel 6

  TFLG1 |= TFLG1_C6F_MASK;
}

void GetLatestServoPosition(int *position){
 *position = lastServoPosition; 
}
  

                                  
// the interrupt for timer 6 which is used for cycling the servo
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TC6_ISR(void) { 

  int time_div = MAX_TIME / MAX_ROWS;
   
  TC6 = TCNT + 64000;   // interrupt delay depends on the prescaler
  TFLG1 |= TFLG1_C6F_MASK;

  // acts as a counter to determine where the servo will stop
  if (toggle == 0){
    iterator_counter_elevate = iterator_counter_elevate + 1;
  } else{
    iterator_counter_elevate = iterator_counter_elevate - 1;
  }
  
  // changing the toggle will change the direction of the row (left to right)
  if (iterator_counter_elevate > MAX_TIME) { // how long it goes for
    toggle = 1;
    rows ++;
    iterator_counter_azimuth = iterator_counter_azimuth + 1200; // every time it reaches this, it will change the angle by 1000 pwm
  } else if (iterator_counter_elevate < 0) {
    toggle = 0;
    rows ++;
    iterator_counter_azimuth = iterator_counter_azimuth + 1200;
  }
  
  // determining where the time div is will allow it to pause at a certain location
  if (iterator_counter_elevate == time_div * 0){
    setServoPose(iterator_counter_azimuth, iterator_counter_elevate);
    lastServoPosition ++;
  } else if (iterator_counter_elevate == time_div * 1){
    setServoPose(iterator_counter_azimuth, iterator_counter_elevate);
    lastServoPosition ++;
  } else if (iterator_counter_elevate == time_div * 2){
    setServoPose(iterator_counter_azimuth, iterator_counter_elevate);
    lastServoPosition ++;
  } else if (iterator_counter_elevate == time_div * 3 && toggle == 1){
    setServoPose(iterator_counter_azimuth, iterator_counter_elevate);
    lastServoPosition ++;
  }
  
  // after scanning all the rows, stop the servos from moving
  if (rows >= MAX_ROWS){
    iterator_counter_azimuth = 0;                                  // reset azimuth
    iterator_counter_elevate = 0;                                  // reset elevation
    setServoPose(iterator_counter_azimuth, iterator_counter_elevate); // reset servo position
    PWMinitialise();
  } 
}

