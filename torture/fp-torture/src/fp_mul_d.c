double F1 = 35.0;
double F2 = 10.0;
double F3;


int main ()
{
//MUL_S
   F3 = F1 * F2;

    if ((F3 > 350.001) || (F3 < 349.999))
    exit(1);

  exit (0);
}
