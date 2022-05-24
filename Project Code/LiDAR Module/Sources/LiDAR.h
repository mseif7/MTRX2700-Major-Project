#define RawDataToCM 281.7
#define LaserBufferSize 40
#define pi 3.1415926535898
#define RAD (pi/180)

float distance_convert(float,float);
int laser_noise_removal(void);
void sort_l(int,int);
float unit_to_cm(int);
float angle_convert(float,float,float);
void clear_laser_buffer(void);
