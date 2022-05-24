#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LiDAR.h"






void main(void) {
  float vertical_distance;
  
  vertical_distance=distance_convert(30,60);
  
  //set breakpoint for testing
  vertical_distance++;

	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}

