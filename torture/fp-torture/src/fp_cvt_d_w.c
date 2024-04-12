#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float F1 = 225.45;
float F2 = 5.0e+03;
int64_t F3;
double F4;

int main ()
{
//cvt_d_w
   F3 = 0x0000000040268000;
   F4 = (double)F3;

   printf("F4 : %f\n",F4);

  exit (0);
}
