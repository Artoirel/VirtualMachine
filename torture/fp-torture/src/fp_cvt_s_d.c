#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef union {
float F1;
double F3;
} regs;

float F1;
double F3 = 225.49;

int main ()
{
//cvt_d_s
regs regs1;

regs1.F3 = 225.49;
regs1.F1 = (float)regs1.F3;

   F1 = (float)F3;

    printf("union: F3 double : %f \n",regs1.F3);
    printf("union: F1 float  : %f \n",regs1.F1);

    printf(" F3 double : %f \n",F3);
    printf(" F1 float  : %f \n",F1);

return 0;
}
