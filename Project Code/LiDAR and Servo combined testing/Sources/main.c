#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */

// need this for string functions
#include <stdio.h>
#include "pll.h"
#include "simple_serial.h"
#include "l3g4200d.h"
#include "servo.h"
#include "laser.h"
#include "LiDAR.h"

#define LaserBufferSize 40

void printErrorCode(IIC_ERRORS error_code) {
  char buffer[128];  
  switch (error_code) {
    case NO_ERROR: 
      sprintf(buffer, "IIC: No error\r\n");
      break;
    
    case NO_RESPONSE: 
      sprintf(buffer, "IIC: No response\r\n");
      break;
    
    case NAK_RESPONSE:
      sprintf(buffer, "IIC: No acknowledge\r\n");
      break;
    
    case IIB_CLEAR_TIMEOUT:
      sprintf(buffer, "IIC: Timeout waiting for reply\r\n");
      break;
    
    case IIB_SET_TIMEOUT: 
      sprintf(buffer, "IIC: Timeout not set\r\n");
      break;
    
    case RECEIVE_TIMEOUT:
      sprintf(buffer, "IIC: Received timeout\r\n");
      break;
    
    case IIC_DATA_SIZE_TOO_SMALL:
      sprintf(buffer, "IIC: Data size incorrect\r\n");
      break;

    default:
      sprintf(buffer, "IIC: Unknown error\r\n");
      break;
  }
    
  SerialOutputString(buffer, &SCI1);
}

void main(void) {
  
  IIC_ERRORS error_code = NO_ERROR;
  
  char buffer[128];  
  
  int laserRD[LaserBufferSize+1];
  int array_counter = 0;
  unsigned long RAW_LASER_VALUE;
  int ServoPos;
  int currentPos = 0;
               
  // make sure the board is set to 24MHz
  // this is needed only when not using the debugger
  PLL_Init();

  // initialise PWM
  PWMinitialise();
  
  // initialise the simple serial
  SerialInitialise(BAUD_9600, &SCI1);
  
  // initialise the sensor suite
  error_code = iicSensorInit();
  
  /*
  // write the result of the sensor initialisation to the serial
  if (error_code == NO_ERROR) {
    sprintf(buffer, "NO_ERROR\r\n");
    SerialOutputString(buffer, &SCI1);
  } else {
    sprintf(buffer, "ERROR %d\r\n");
    SerialOutputString(buffer, &SCI1);
  }*/

  laserInit();

  Init_TC6();
  
	EnableInterrupts;
  //COPCTL = 7;
  _DISABLE_COP();
    
  for(;;) {
    
    // Get the latest laser data
    GetLatestLaserSample(&RAW_LASER_VALUE);
    GetLatestServoPosition(&ServoPos);
    
    if (ServoPos == currentPos){
      if (array_counter >= LaserBufferSize){
        array_counter = 0;
        currentPos ++;
      } else{
        // Write the raw laser value to an array
        laserRD[array_counter] = (int)RAW_LASER_VALUE;
        array_counter ++;
      }  
    }
    
    // format the string of the sensor data to go the the serial    
    sprintf(buffer, "%lu\r\n", RAW_LASER_VALUE);
    // output the data to serial
    SerialOutputString(buffer, &SCI1); 
    
    
    
    
    //_FEED_COP(); /* feeds the dog */
  } /* loop forever */
  
  /* please make sure that you never leave main */
}