float F1 = 335.0;
float F2 = -0.01;
float F3;


int main ()
{
//MUL_S
   F3 = F1 * F2;

    if ((F3 < -3.35001) || (F3 > -3.34999))
    exit(1);

  exit (0);
}
