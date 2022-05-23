# MTRX2700-ASSIGNMENT-3
<div id="top"></div>




# MTRX2700-Major-Project
<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#group-details">Group Details</a>
    </li>
    <li>
      <a href="#module-1---user-input">Module 1</a>
      <ul>
        <li>About Module 1 Code</a></li>
        <li>Instructions for Module 1</a></li>
        <li>Details about Testing Procedures for Module 1</a></li>
      </ul>
    </li>
    <li>
      <a href="#module-2---lidar-camera">Module 2</a>
      <ul>
        <li>About Module 2 Code</a></li>
        <li>Instructions for Module 2</a></li>
        <li>Details about Testing Procedures for Module 2</a></li>
      </ul>
    </li>
    <li>
      <a href="#module-3---pan-and-tilt">Module 3</a>
      <ul>
        <li>About Module 3 Code</a></li>
        <li>Instructions for Module 3</a></li>
        <li>Details about Testing Procedures for Module 3</a></li>
      </ul>
    </li>
    <li>
      <a href="#module-4---box-detection">Module 4</a>
      <ul>
        <li>About Module 4 Code</a></li>
        <li>Instructions for Module 4</a></li>
        <li>Details about Testing Procedures for Module 4</a></li>
      </ul>
    </li>
    <li>
      <a href="#module-5---7-seg-display">Module 5</a>
      <ul>
        <li>About Module 5 Code</a></li>
        <li>Instructions for Module 5</a></li>
        <li>Details about Testing Procedures for Module 5</a></li>
      </ul>
    </li>
    <li>
      <a href="#module-6---sound">Module 6</a>
      <ul>
        <li>About Module 6 Code</a></li>
        <li>Instructions for Module 6</a></li>
        <li>Details about Testing Procedures for Module 6</a></li>
      </ul>
    </li>
    <li>
      <a href="#module-7---led-lights">Module 7</a>
      <ul>
        <li>About Module 7 Code</a></li>
        <li>Instructions for Module 7</a></li>
        <li>Details about Testing Procedures for Module 7</a></li>
      </ul>
    </li>
    <li>
      <a href="#module-8---lcd-display">Module 8</a>
      <ul>
        <li>About Module 8 Code</a></li>
        <li>Instructions for Module 8</a></li>
        <li>Details about Testing Procedures for Module 8</a></li>
      </ul>
    </li>
    <li><a href="#references">References</a></li>
  </ol>
</details>



<!-- Group details -->
## Group Details

For this assignment, we had 3 group members in person and 3 group members on discord with one major project to complete. This project involved observing how the future of supermarkets could be impacted by new technologies. The specific hardware in question are the Dragon12 board and the Pan/Tilt unit (PTU). The objective was to implement a proof-of-concept technology to improve the operation of a certain part within the supermarket. Our groups idea involved using these new technologies to scan the shelves and constantly keep track of the amount of the product remaining, and to relay this information to the staff of the supermarket. However this was a very large task and thus needed to be split into numerous smaller modules for each person to work on.
The modules and member allocation are explained in the sections below.; 


<p align="right">(<a href="#top">back to top</a>)</p>
 

<!-- Module 1 info -->
## Module 1 - User Input
Module 1 is for taking user inputs from serial port and store them as variables for later use. 
The variables needed to be stored are: total rows; total coloumns; height of the shelf; width of the shelf; height of the the box; width of the box; and length of the box. 
No output message needed for this module.

### About Module 1 Code
The code includes 1 interrupt and 5 functions to perform: input taken from serial port, input spilt into 7 variables; input conversion from char arrary to int and stored in 1 struct (struct input, name as "inputs"). 



### Instructions for Module 1
User input: \<total rows\> \<total coloumns\> \<height of the shelf\> \<width of the shelf\> \<height of the the box\> \<width of the box\> \<and length of the box\> \<?\>   
With input '?' detected, the system will stop receiving, and start to transfer the inputs as ints.   

### Details about Testing Procedures for Module 1  
To test the module in CodeWarrior, the user can see the results from debugger.   
Inputs: storing the int-type inputs as final outcome.  
rawData: storing the arrary of char-type inputs indicating the inputs been successfully received from the serial port.  
Buffer: storing the last 1 char of rawData, used to determine the end of typing.  

Procedure:  
1. Run the code on debugger  
2. Enter the user input on terminal (SCI0)  
3. Check the data stored (via the window of data)  
4. If the values stroed in 'inputs' are all 0s, run the code again by clicking the green bottom  

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Module 2 info -->
## Module 2 - LiDAR Camera
Module 2 is the module for measurement using the LiDAR camera.<br> This module takes the angle values in degree from the PTU module and a series of raw data measurement from the LiDAR stored in an array, then return a single number representing the distance to a single point.
The returned value of this module is converted into vertical distance in centimeter from the device to the object by default, in order to meet the applying occasion of this design.<br>If needed, users may pick the sub-modules to obtain straight-line distances or distance values in the same scale to the raw data.
It is assumed that the PTU has no motion when making measurement. Inaccurate results may occur otherwise. 


### About Module 2 Code
#### Data Obtaining
The driver file “laser.c” initialize the LiDAR sensor and then continuously getting measurements. These values are discarded unless the PTU is confirmed to be at the desired position.<br>The detail operation refers to the PTU module. When The PTU reaches the target position, it starts taking the measured data from LiDAR sensor and write it to a global variable “LaserRD” (stands for “Laser Raw Data”), which is an array of integers. Then it calls the data processing functions to handle the raw data.
The angles of the servo motors are also passed to the data processing part. 
#### Data Processing
The data processing part contains a major function “distance_convert” that calls the other functions to complete its task.
##### distance_convert
Input: two angle values in degree<br>
(The global variable “LaserRD” will be taken automatically, no needed to be included in the input parameters.)<br>
Output: a float number representing the vertical distance from the object to the sensor<br>
It calls the function “laser_noise_removal”, “unit_to_cm”, “angle_convert” in a series to process the data.
##### laser_noise_removal

##### unit_to_cm
Input: an integer value of the measured distance in the same scale to the raw data (from “laser_noise_removal”)<br>
Output: a float number of the measured distance in centimeters<br>
This function simply divide the input with 281.7, which is the ratio from raw data to centimeter.
##### angle_convert
Input: two float numbers of the servo motor angles, one float number from “unit_to_cm” <br>
Output: a float number representing the vertical distance from the object to the sensor<br>

### Instructions for Module 2
#### Getting Measurement
This module is designed on the assumption that the PTU has no motion during data acquisition. Inaccurate results may occur otherwise.<br>
Depending on the rate of data acquisition, it is commended that the the sensor stays in the same position for long enough time to allow enough measured values to fill the data recording buffer. In this project, the recommended time is 0.5s to fill a buffer of size 40. Even if the buffer is not fully filled, the function may still run, but the result could be less accurate.
#### Distance Unit Conversion
The ratio converting raw data to centimeter is obtained from field testing of the device used in this project and adapted to the method of ruling out noises. If a different device used, please refer to the manual of the new device or conduct another field test to obtain the new value. If a new method of noise removal is used, please recalculate this value. 
#### Vertical Distance Conversion
The “angle_convert” function may be modified depends on the actual position and angle of the device connected to the frame, and the configuration of the servo motors.
   
### Details about Testing Procedures for Module 2

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Module 3 info -->
## Module 3 - Pan and Tilt



### About Module 3 Code


### Instructions for Module 3

 

### Details about Testing Procedures for Module 3



<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Module 4 info -->
## Module 4 - Box Detection



### About Module 4 Code


### Instructions for Module 4

 

### Details about Testing Procedures for Module 4



<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Module 5 info -->
## Module 5 - 7 Seg Display
This module takes the calculated quantity of items left on the shelf from the Box Detection module, and displays the quantity on the rightmost 2 digits of the 7-segment display. 


### About Module 5 Code
Functions used in this module include: 
- Init_7seg(void): 
  - initialises the 7-segment display module by configuring PORTB and PORTP to be used as output;
  - PORTP is used to select the digit that is used on the 7-seg display, and PORTB is used to output a hex value to the 7-seg, to display a number).
- displayQty(int itemQty, int seg_flag):  
  - Takes in the SEG_FLAG variable and checks its value  - if SEG_FLAG = 1, 7-seg display module will be executed;
  - Takes in the calculated item quantity from the Box Detection module, use arithmetic operations to obtain numbers on each digit (for example, quantity 13 is     separated to digits 1 and 3); 
  - Hex values corresponding to 7-seg illumination patterns of numbers 0-9 are stored in an array (segHex) in the LCD_Fin.h file, and are called according to       the numbers to be displayed (e.g. segHex[3] stores the hex value that displays number 3 on the 7-seg display, once output to PORTB);
  - The hex value is sent to PORTB for display, and PORTP is used to select which digit the number will be displayed on (e.g. quantity 13 will have number 3         displayed on the rightmost digit, and number 1 displayed on the second rightmost digit). 
- MSDelay(unsigned int itime): 
  - delays the program by a certain amount of time (in milliseconds).



### Instructions for Module 5
For testing this module independently:


 

### Details about Testing Procedures for Module 5



<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Module 6 info -->
## Module 6 - Sound



### About Module 6 Code


### Instructions for Module 6

 

### Details about Testing Procedures for Module 6



<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Module 7 info -->
## Module 7 - LED Lights
Module 7 is responsible for the function of the LED's of the DragonBoard. This module will take in the remaining number of stock and depending on the amount remaining, the LED lights will act as a ‘progress bar’ and display the percentage of stock remaining as a ‘progress bar’.


### About Module 7 Code
The required inputs for the module are the maximum number of boxes, and the remaining number of boxes. From these variables, another variable is calculated named ratio, which as the name suggests is a ratio of the remaining boxes with the total. The program then goes through a series of if statements to determine which range the value ratio lies between. The if statements are set up in order to 'round' ratio to the nearest eigth, to provide the most accurate progress bar.
Once the range is found, another variable led_num is given a specific value. This value will later determine the number of LEDs which are illuminated. 

The values of PORTB and PORTJ are then set. DDRB = 0xFF and DDRJ = 0xFF sets both PORTB and PORTJ as outputs. PTJ = 0x00 then enables LEDs. After this we can then set the value of PORTB to the number we assigned earlier to led_num. The LEDs on the dragonboard should then be illuminated with the corresponding amount of LEDs turned on. For example, if there are 80 total boxes and 10 boxes are remaining, one LED should be illuminated to symbolise one eigth (12.5%) of the stock remaining.



### Instructions for Module 7
For testing module individually:
1. Manually declare the maximum amount of boxes and remaining number of boxes. This can be done at the top of main (eg for maximum boxes to be 80, write int max_boxes = 80;).
2. Connect the device to the dragonboard
3. 2. Run the debugger in the IDE
4. Run the code using the right pointing green Start/Continue arrow.
5. The corresponding number of LEDs should light up depending on the number of max boxes and remaining boxes you inputed. 




### Details about Testing Procedures for Module 7
Testing the LEDs are functioning correctly can be done easily. The user needs to change the values of max boxes and remaining boxes and observe if the correct amount of LEDs are illuminating. For example, make max_boxes = 80 and rem_boxes = 40. It can be seen that 50% of the boxes are remaining. Therefore we should obviously expected half (4/8) LEDs to be illuminated. If this is the case, the module is working correctly.


<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Module 8 info -->
## Module 8 - LCD Display
This module takes the calculated quantity of items left on the shelf from the Box Detection module, and shows a message on the LCD display depending on the item quantity. 


### About Module 8 Code
Functions used in this module include: 
  - COMWRT4(unsigned char):
    - sets cursor position for writing message onto LCD display;
  - DATWRT4(unsigned char): 
    - writes a single character on LCD display;
  - Init_LCD(void): 
    - configures PORTK to output
    - resets the display module
    - sets data display format and display mode
    - clears display
    - sets home position and start position;
  - writeStringLCD(unsigned char * message): 
    - takes in a string, uses the COMWRT4 and DATWRT4 functions to print the string on LCD display;
  - writeIntLCD(int number):
    - takes in an integer and prints it on LCD display;
  - stringIntStringLCD(unsigned char * message1, int number, unsigned char * message2): 
    - prints a message with an integer in the middle (e.g. the refill reminder message “Refill x items” where x is an integer);
  - activateDisplayLCD(unsigned int lcd_flag, int itemQty, int fullQty, char * fullMsg, char * emptyMsg, char * refMsg1, char * refMsg2, char * errorMsg): 
    - Takes in the LCD_FLAG variable and checks its value  - if  LCD_FLAG = 1, LCD display module will be executed;
    - Calls the message writing functions above (writeStringLCD, writeIntLCD, stringIntStringLCD) and prints appropriate messages depending on the item               quantity;
    - When there is no item, prints “Shelf empty”;
    - When item quantity is equal to full capacity, prints “Shelf full”;
    - When item quantity is smaller than full capacity, calculates how many items need to be refilled, and prints “Refill x items”;
    - When item quantity is more than full capacity, prints “Error”.
  - MSDelay(unsigned int itime): 
    - delays the program by a certain amount of time (in milliseconds).



### Instructions for Module 8
For executing this module independently:
User can access the main.c file and locate variables int LCD_FLAG, int qty and int full_qty;
Set LCD_FLAG to 1 to allow the module to be executed;
Set full_qty to any integer larger than 1;
Set qty to an integer larger than full_qty and run the program, the board should display "Error";
Set qty to 0 and run the program the board should dispay "Shelf Empty";
Set qty to the same as full_qty and run the program, the board should display "Shelf full";
Set qty to any positive integer smaller than full_qty and run the program, the board should display "Refill x items" where x is the difference between full_qty and qty. 

Note: when running the program, the board may need to be reset to display the updated message. 

 

### Details about Testing Procedures for Module 8



<p align="right">(<a href="#top">back to top</a>)</p>




<!-- references -->
## References

* https://github.com/othneildrew/Best-README-Template/blob/master/BLANK_README.md#prerequisites

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/github_username/repo_name.svg?style=for-the-badge
[contributors-url]: https://github.com/github_username/repo_name/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo_name/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/repo_name.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo_name/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo_name.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo_name/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo_name.svg?style=for-the-badge
[license-url]: https://github.com/github_username/repo_name/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[product-screenshot]: images/screenshot.png
