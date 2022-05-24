
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

/////// 7 Seg Hex values of decimal numbers //////////
// Call for corresponding value of number when required

/*
char SEG0 = 0x3F;
char SEG1 = 0x06;
char SEG2 = 0x5B;
char SEG3 = 0x4F;
char SEG4 = 0x66;
char SEG5 = 0x6D;
char SEG6 = 0x7D;
char SEG7 = 0x07;
char SEG8 = 0x7F;
char SEG9 = 0x6F;

*/

/////////////////////

unsigned char segHex[10] = {
  0x3F,
  0x06,
  0x5B,
  0x4F,
  0x66,
  0x6D,
  0x7D,
  0x07,
  0x7F,
  0x6F
};

int SEG_FLAG;
//int qty;

void displayQty(int itemQty, int seg_flag);
// display the quantity of items left on the 7-seg display;
// qty is obtained from previous calculation module;
// displays when SEG_FLAG = 1.

void MSDelay(unsigned int);
// delays program by an amount of time (int milliseconds) 

void Init_7seg(void);
