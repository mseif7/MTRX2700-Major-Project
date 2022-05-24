#include "led.h"

// include the register/pin definitions
#include "derivative.h"      /* derivative-specific definitions */





void progressbar(int max_boxes, int rem_boxes, int *led_num) {

	double ratio = (double)rem_boxes / (double)max_boxes;
	
  if (ratio == 0)
  {
    *led_num = 0b00000000;
  }
	else if ((0 < ratio) && (ratio <= 0.125))
	{
	  *led_num = 0b00000001;
	}
	else if ((0.125 < ratio) && (ratio <= 0.25))
	{
	  *led_num = 0b00000011;
	}
	else if ((0.25 < ratio) && (ratio <= 0.375))
	{
	  *led_num = 0b00000111;
	}
	else if ((0.375 < ratio) && (ratio <= 0.5))
	{
	  *led_num = 0b00001111;
	}
	else if ((0.5 < ratio) && (ratio <= 0.625))
	{
	  *led_num = 0b00011111;
	}
	if ((0.625 < ratio) && (ratio <= 0.75))
	{
	  *led_num = 0b00111111;
	}
	if ((0.75 < ratio) && (ratio <= 0.875))
	{
	  *led_num = 0b01111111;
	}
	if ((0.875 < ratio) && (ratio <= 1))
	{
	  *led_num = 0b11111111;
	}
}