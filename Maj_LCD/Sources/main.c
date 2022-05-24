#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


char *full_msg = "Shelf full";
char *empty_msg = "Shelf empty";
char *refill_msg1 = "Refill ";
char *refill_msg2 = " items";
char *error_msg = "Scan Error";




void main(void) {

  int LCD_FLAG = 1;
  int full_qty = 25;
  int qty = 16;
  
 
  Init_LCD();
  /* put your own code here */
  
  EnableInterrupts;
  

  
  
  
  activateDisplayLCD(LCD_FLAG, qty, full_qty, full_msg, empty_msg, refill_msg1, refill_msg2, error_msg);


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
