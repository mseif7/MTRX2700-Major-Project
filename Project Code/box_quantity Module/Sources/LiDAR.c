#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LiDAR.h"

//buffer storing laser sensor raw data
int laserRD[LaserBufferSize+1]={4812,5969,6738,3817,4977,4607,2755,5224,6640,4800,6735,5437,4534,6878,1786,4280,5642,3069,3740,5779,6848,2633,3997,5548,5238,5839,3864,5881,2244,4767,7600,2376,4538,1954,2285,7074,4462,4468,5555,4499,0};



//the major function to convert an array of raw data to a vertical distance in cm
float distance_convert(float a1,float a2){
  float distance;
  
  //get the straight-line distance in cm
  distance=unit_to_cm(laser_noise_removal());

  //convert to vertiacl distance
  distance=angle_convert(a1,a2,distance);

  return distance;
}



//a quicksort function for laser sensor readings
//modified from a typical quicksort function copied from internet
void sort_l(int start,int end)
{
    int i,j,temp,x;
    i=start;
    j=end;
    x=laserRD[start];
    while(i<j)
    {
        while(i<j && x<laserRD[j])
            j--;
        while(i<j && x>laserRD[i])
            i++;
        if(i<j)
        {
            temp=laserRD[j];
            laserRD[j]=laserRD[i];
            laserRD[i]=temp;
        }
    }
    temp=x;
    x=laserRD[i];
    laserRD[i]=temp;
    if(start<j)
        sort_l(start,j-1);
    if(i<end)
        sort_l(j+1,end);
}

// the function to reduce the noise in raw data
// return a single value representing the distance
int laser_noise_removal(void){
  volatile int len,left,right,count,buffer_size;
  volatile int min,max,i;
  volatile float s1,s2;
  volatile int a=1;
  volatile double average;
  
  buffer_size=LaserBufferSize;
  //the buffer may not be fully filled, rule out zeros
  i=-1;
  while(laserRD[i+1]!=0) {
    i++;
  }
  
  if(i==-1){    
    clear_laser_buffer(); //clear buffer
    return -2;//if i is still -1, buffer is empty, the returned -2 is for debugging
  }
  
  /*
  if((i/buffer_size)<0.5){
    clear_laser_buffer(); //clear buffer
    return -3;//less than 50% of the buffer filled, no enough valid data, the returned -3 is for debugging  
  }
  */
  
  //sort data before the zeros
  len=i;
  sort_l(0,len);

  average=-1; //value for debugging, if return -1, error
  
  //start by dropping the biggest and smallest 10% (noise)
  left=(int)(len/10);
  right=len-(int)(len/10);
  count=right-left+1;

  
  //divide the range equally into 3, between min, s1, s2, max
  min=laserRD[left];
  max=laserRD[right];
  s1=min+(max-min)/3;
  s2=max-(max-min)/3;
  
  //get average
  average=0;
  for(i=left;i<=right;i++){
    average=average+laserRD[i]/count;
  }
  
    
  while(a)
  {        
        
    //drop data based on average
    if(average<=s1)
    {
      while(laserRD[right]>s1)
        right--;   
    } else if(average>=s2)
    {
      while(laserRD[left]<s2)
        left++;   
    } else{
    
      while(laserRD[left]<s1)
        left++;    
      while(laserRD[right]>s2)
        right--;        
    }
  
    count=right-left+1;
  
      
    //get the new average
    average=0;
    for(i=left;i<=right;i++){
      average=average+laserRD[i]/count;
    }

    
    //loop until max-min<=1500
    //or max/min<=1.5
    //or less than 30% data left
    if(laserRD[right]-laserRD[left]<1500)
      a=0;
    if(laserRD[right]/laserRD[left]<1.5)
      a=0;
    if(count/len<0.3)
      a=0;
    
    else{
      min=laserRD[left];
      max=laserRD[right];
      s1=min+(max-min)/3;
      s2=max-(max-min)/3;
    }
    
  }
  
  clear_laser_buffer(); //clear buffer
  return (int)average;
}

// convert distance to centimeter
float unit_to_cm (int distance) {
  float distance_cm;
  distance_cm=distance/RawDataToCM;
  return distance_cm;
}

//convert straight-line distance to vertical distance
float angle_convert(float a1,float a2,float d){
  
  // convert angle to radian
  a1*= RAD;
  a2*= RAD;  
  
  d=d*cos(a1)*cos(a2);
  
  return d;
}

//clear the laser data buffer
void clear_laser_buffer(void){
  int i;
   
  for(i=0;i<LaserBufferSize;i++){
    laserRD[i]=0;  
  }
}

