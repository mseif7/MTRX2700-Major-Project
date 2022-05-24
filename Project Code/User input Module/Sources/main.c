#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h> 

#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SERIAL_BUFFER 50
  
// NOTE: these are stored as pointers because they 
//       are const values so we can't store them directly
//       in the struct
typedef struct SerialPort { 
  byte *BaudHigh;
  byte *BaudLow;
  byte *ControlRegister1;
  byte *ControlRegister2;
  byte *DataRegister;
  byte *StatusRegister;
} SerialPort;

typedef struct Input {  // Struct for storing user input
  int Rows; // total rows
  int Cols; // total columns
  int Height_shelf; // total height of the shelf
  int Width_shelf; // total width of the shelf
  int Height_box; // height of the box in the shelf
  int Width_box; // width of the box in the shelf
  int Length_box; // length of the box in the shelf
} Input;


/////// Functions ///////////////

//void InitialiseSerialPort1(SerialPort *serial_port, int successFlag); // Serial Port 1 initialisation  For output system information
void InitialiseSerialPort0(SerialPort *serial_port, int successFlag); // Serial Port 0 initialisation  For user input
//void SerialOutputMsg(char data, SerialPort *serial_port, int flag);  // printf function to Sci1
void readSerial(SerialPort *serial_port); // scanf function from Sci0
void ResetSerial();  // reseting flags and counters to initial status
int new_atoi(char *ptr, int length);
int compare(char Achar);

/////////////////////////////////

 
void MSDelay(unsigned int);
 
char *init_success = "Initialisation Successful\r\n";
char *reset_success = "Reset Successful\r\n";
char *read_success = "Read Successful\r\n";

char *current_character = 0x00; // set initial pointer location
char *writeCounter = 0x00;

char Cols[4];
char Rows[4]; 
char Height_shelf[4];
char Width_shelf[4];   
char Height_box[4];
char Width_box[4];   
char Length_box[4];

char *Cols_p = 0x00;  
char *Rows_p = 0x00;  
char *Height_shelf_p = 0x00;  
char *Width_shelf_p = 0x00;  
char *Height_box_p = 0x00;  
char *Width_box_p = 0x00;  
char *Length_box_p = 0x00;  

      


 
// instantiate the serial port parameters
//   note: the complexity is hidden in the c file

//********************************************************************************************
SerialPort SCI0 = {&SCI0BDH, &SCI0BDL, &SCI0CR1, &SCI0CR2, &SCI0DRL, &SCI0SR1};
//SerialPort SCI1 = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
Input Inputs; 

int readCounter; // counter to use for reading in data from serial
//int writeCounter; // counter to use for writing in data from serial

int test = 0;
int mark;
int i = 0;
int loc = 0;
int mult = 0;// test variable

int initSuccessFlag = 1; // Flag for indication of serial port initialisation;
int resetFlag = 1; // Flag for indication of serial port reset;
int readFlag = 1;
int Flag = 1; // Flag for transmit Flags to interrupt

char rawData[SERIAL_BUFFER];
char buffer[SERIAL_BUFFER]; // seperating string


//********************************************************************************************
//  added to the ISR vector table
#pragma CODE_SEG NON_BANKED 
/* Interrupt section for this module. Placement will be in NON_BANKED area. */
/*interrupt VectorNumber_Vsci1 void SerialInterruptHandler(){

  if (*(SCI1.StatusRegister) & SCI1SR1_TDRE_MASK && *current_character != 0x00) {
    SerialOutputMsg(*(current_character++), &SCI1, Flag);
  } 
  else if (*current_character == 0x00){
    
    // string is finished, stop the transmit interrupt from firing
    *(SCI1.ControlRegister2) &= ~SCI1CR2_TCIE_MASK;
  }
}
*/
interrupt VectorNumber_Vsci0 void ReadInterruptHandler(){
  
 
  if (*(SCI0.StatusRegister) & SCI0SR1_RDRF_MASK && buffer[0] != 0x3F) {
   // *(SCI1.ControlRegister2) |= SCI1CR2_TCIE_MASK;
    readFlag = 1;
    readSerial(&SCI0);
    
    //writeCounter = &rawData[0];
    //SerialOutputMsg(*(writeCounter++), &SCI1, readFlag);
    buffer[0] = rawData[readCounter - 1];
    }    
    
  else if (buffer[0] == 0x3F){
     
    while (mark == 0){      
      if (rawData[test] == ' '){
         mark = test;     
      } 
      else if (rawData[test] != ' '){
         test++;  
      }
    }
    while (i < test){
      Cols[i] = rawData[i];
      i++;    
    }
//********************** 
    test++;   
    while (mark == i){
      if (rawData[test] == ' '){
        mark = test;
      } 
      else if (rawData[test] != ' '){
        test++;
      }      
     }
    i++;
    while (i < test){
      Rows[loc] = rawData[i];
      i++;
      loc++;    
    }    
//*********************** 
    test++;
    loc = 0;   
    while (mark == i){
      if (rawData[test] == ' '){
        mark = test;
      } 
      else if (rawData[test] != ' '){
        test++;
      }      
     }
     i++;
    while (i < test){
      Height_shelf[loc] = rawData[i];
      i++;
      loc++;    
    }    
//**********************
    test++;
    loc = 0;
    while (mark == i){
      if (rawData[test] == ' '){
        mark = test;
      } 
      else if (rawData[test] != ' '){
        test++;
      }      
     }
     i++;
    while (i < test){
      Width_shelf[loc] = rawData[i];
      i++;
      loc++;    
    }    
//************************
    test++;
    loc = 0;  
    while (mark == i){
      if (rawData[test] == ' '){
        mark = test;
      } 
      else if (rawData[test] != ' '){
        test++;
      }      
     }
     i++;
    while (i < test){
      Height_box[loc] = rawData[i];
      i++;
      loc++;    
    }    
//************************
    test++;
    loc = 0;  
    while (mark == i){
      if (rawData[test] == ' '){
        mark = test;
      } 
      else if (rawData[test] != ' '){
        test++;
      }      
     }
     i++;
    while (i < test){
      Width_box[loc] = rawData[i];
      i++; 
      loc++;   
    }    
//************************ 
    test++;
    loc = 0; 
    while (mark == i){
      if (rawData[test] == ' '){
        mark = test;
      } 
      else if (rawData[test] != ' '){
        test++;
      }      
     }
     i++;
    while (i < test){
      Length_box[loc] = rawData[i];
      i++;
      loc++;    
    }
    loc = 100;
    test = 0;
    i = 10000;
    mark = 10001;   
//************************
    Cols_p = &Cols[0];  
    Rows_p = &Rows[0];  
    Height_shelf_p = &Height_shelf[0];  
    Width_shelf_p = &Width_shelf[0];  
    Height_box_p = &Height_box[0];  
    Width_box_p = &Width_box[0];  
    Length_box_p = &Length_box[0];
    
     
    
    Inputs.Cols = new_atoi(Cols_p, strlen(Cols));
    Inputs.Rows = new_atoi(Rows_p, strlen(Rows));
    Inputs.Height_shelf = new_atoi(Height_shelf_p, strlen(Height_shelf));
    Inputs.Width_shelf = new_atoi(Width_shelf_p, strlen(Width_shelf));
    Inputs.Height_box = new_atoi(Height_box_p, strlen(Height_box));
    Inputs.Width_box = new_atoi(Width_box_p, strlen(Width_box));
    Inputs.Length_box = new_atoi(Length_box_p, strlen(Length_box)); 
    //mult = Inputs.Rows * Inputs.Cols;

    //*(SCI1.ControlRegister2) &= ~SCI1CR2_TCIE_MASK;       
  } 
  if (readCounter >= 51) {  // reset if input over 50
    //*(SCI1.ControlRegister2) &= ~SCI1CR2_TCIE_MASK;     // string is finished, stop the transmit interrupt from firing
    ResetSerial();
  }
         
  }
      


                            
void main(void){  
  
  //InitialiseSerialPort1(&SCI1, initSuccessFlag); 
  InitialiseSerialPort0(&SCI0, initSuccessFlag); 

  EnableInterrupts
    
  // enable the transmit mask
  //*(SCI1.ControlRegister2) |= SCI1CR2_TCIE_MASK;
 
    
  while (*current_character != 0x00) {
    // waiting in here until the string has completed sending
    //*(SCI0.StatusRegister) = SCI0SR1_RDRF_MASK;
  }
  
  
  ResetSerial();
  writeCounter = &rawData[0];
  //mult = Inputs.Rows * Inputs.Cols;
 
  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  
   
}



// InitialiseSerial - Initialise the serial port SCI1
// Input: baudRate is tha baud rate in bits/sec
void InitialiseSerialPort1(SerialPort *serial_port, int successFlag) {
  
  *(serial_port->BaudHigh)=0;
  *(serial_port->BaudLow)=156; 
  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK|SCI1CR2_TE_MASK|SCI1CR2_TCIE_MASK; 
  *(serial_port->ControlRegister1) = 0x00;
  
  current_character = &init_success[0];
  initSuccessFlag = 0;
  Flag = initSuccessFlag;
  
}   

 
void InitialiseSerialPort0(SerialPort *serial_port, int successFlag) {
  
  *(serial_port->BaudHigh)=0;
  *(serial_port->BaudLow)=156; 
  *(serial_port->ControlRegister2) = SCI0CR2_RE_MASK|SCI0CR2_TE_MASK|SCI0CR2_RIE_MASK;; 
  *(serial_port->ControlRegister1) = 0x00;
  
  current_character = &init_success[0];
  initSuccessFlag = 0;
  Flag = initSuccessFlag;
  
}  
 
 
        
void SerialOutputMsg(char data, SerialPort *serial_port, int flag) {  

  int wait_counter = 0;
  while((*(serial_port->StatusRegister) & SCI1SR1_TDRE_MASK) & flag == 0){
     if (wait_counter < 0x05)
       wait_counter++;
  }
  
  *(serial_port->DataRegister) = data;
}


void readSerial(SerialPort *serial_port) {
  if (*(serial_port->StatusRegister) && SCI0SR1_RDRF_MASK) {      
      rawData[readCounter] = *(serial_port->DataRegister); // store the char from port 0 in a static list
      *(serial_port->DataRegister) = rawData[readCounter];

      readCounter ++; // update the readCounter to be ready for next char
      readFlag = 0;
      Flag = readFlag;
    } 
}


void ResetSerial() {

  resetFlag = 0;
  Flag = resetFlag;
  current_character = &reset_success[0];
  resetFlag = 1; 
  
  Flag = 1;
  readFlag = 1;                                            
  readCounter = 0;

}


int new_atoi(char *ptr, int length)
{
    volatile int ans1 = 0;
    volatile int ans2 = 1;
    volatile int ans3 = 0;
    volatile int i = 0;
    volatile int j = 1;
    
    while (i < length){
      
      ans1 = (int)compare(*(ptr + i));
      
      while (j < length) {
          
          ans2 = (int)ans2 * (int)10; 
          j++;          
      }
      
      ans3 = (int)ans3 + ((int)ans1 * (int)ans2);
      ans1 = (int)0;
      ans2 = (int)1;
      i++;
      j = i + 1;      
    }
    
        return ans3;
} 


int compare(char Achar){
    
    int answer = 0;

    if (Achar == '0'){ (answer = 0);}
    if (Achar == '1'){ (answer = 1);}
    if (Achar == '2'){ (answer = 2);}
    if (Achar == '3'){ (answer = 3);}
    if (Achar == '4'){ (answer = 4);}
    if (Achar == '5'){ (answer = 5);}
    if (Achar == '6'){ (answer = 6);}
    if (Achar == '7'){ (answer = 7);}
    if (Achar == '8'){ (answer = 8);}
    if (Achar == '9'){ (answer = 9);}
    
    return answer;
      
}

 