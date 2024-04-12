double F1 = 25.0;
double F2 = 45.0;
double F3;


int main ()
{
//SUB_d
   F3 = F2 - F1;

    if ((F3 > 20.001) || (F3 < 19.999))
    exit(1);

  exit (0);
}
