#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float F1 = 225.0;
float F2 = 5.0e+03;
float F3;
float F4;

int main ()
{
//Sqrt_S
   F3 =sqrtf(F1);
   F4 =sqrtf(F2);

    if ((F4 > 70.72) || (F4 < 70.71) || (F3 > 15.001) || (F3 < 14.999))
    exit(1);

  exit (0);
}
