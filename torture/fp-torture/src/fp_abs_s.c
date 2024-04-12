#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float F1 = 225.0;
float F2 = 5.0e+03;
float F3;
float F4;

int main ()
{
//abs_s : the abs_s inst was not generated
   F3 =fabs(-3.455);
   F4 =fabs(3.455);

    if ((F3 < 3.45499) || (F3 > 3.45599))
    exit(1);

    if ((F4 < 3.45499) || (F4 > 3.45599))
    exit(1);

  exit (0);
}
