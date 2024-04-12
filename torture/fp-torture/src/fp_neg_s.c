float F1 = 15.0;
float F2 = -23.5;
float F3;
float F4;


int main ()
{
//neg_s : this inst was not generated
   F3 = -F1;
   F4 = -F2;

    if ((F3 < -15.001) || (F3 > -14.999) || (F4 > 23.501) || (F4 < 23.499))
    exit(1);

  exit (0);
}
