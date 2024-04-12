float F1 = 15.0;
float F2 = 45.0;
float F3;


int main ()
{
//DIV_S
   F3 = F1 / F2;

    if ((F3 > 0.34) || (F3 < 0.32))
    exit(1);

  exit (0);
}
