#include "7seg.h"




void Init_7seg(void){

        DDRA = 0xFF;
        DDRB = 0xFF;        // Configure PORTB to be used as output
        DDRP = 0xFF;        // Configure PORTP to be used as output

}

void displayQty(int itemQty, int seg_flag) {

    int dig1 = itemQty/10;
    int dig2 = itemQty%10;
        //////////////
        /*
        For simulation testing, the RIGHTMOST digit of 7-seg is set to PORTA,
        and LEFTMOST digit is set to PORTB;
        IRL this is set by PTP value, and alternating between digits with 1ms delay.
        */
    if (seg_flag == 1) {
              //////////////
        PORTB = segHex[dig1];
        PTP = 0x0B;
        // 0x0B: 2nd digit form the right of 7-seg display
                               
        MSDelay(1);            
        
        PORTB = segHex[dig2];
        PTP = 0x07;  
        // 0x07: rightmost digit of 7-seg display    
        MSDelay(1);
              
        // 7-seg will display a 2-digit dumber as BA.
  
    }
    
  

}


void MSDelay(unsigned int itime) {   // millisecond delay
    unsigned int i; 
    unsigned int j;
    for(i=0;i<itime;i++)
      for(j=0;j<4000;j++);
  }
