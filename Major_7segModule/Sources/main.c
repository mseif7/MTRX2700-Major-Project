//Displaying numbers on all 7-Seg LEDs of Dragon12+ Trainer Board 
//with HCS12 Serial Monitor Program installed. This code is for CodeWarrior IDE
//On Dragon12+ board we have 4-digit common cathode 7-Seg LEDs
//PORTB drives 7-Seg LEDs (anode) See Page 24 of Dragon12+ User's Manual
//and PTP0-PTP3 provide grounds (cathode) to 7-Seg LEDs 
 
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */




void main(void) 
{
  /* put your own code here */
        
        int SEG_FLAG = 1;
        int qty = 46;
        
        Init_7seg();
        displayQty(qty, SEG_FLAG);

        for(;;) {
          _FEED_COP(); /* feeds the dog */
        }

 
}

