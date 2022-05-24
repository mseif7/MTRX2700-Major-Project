#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "led.h"




                   
void main(void)
{
  int led_num;
  int max_boxes = 9;
	int rem_boxes = 0; 
  progressbar(max_boxes, rem_boxes, &led_num);
  DDRB= 0xFF;
  DDRJ= 0xFF;
  PTJ= 0x00;  

  PORTB = led_num;
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
