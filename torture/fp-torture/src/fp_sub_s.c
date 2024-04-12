float F1 = 15.0;
float F2 = 45.0;
float F3;


int main ()
{
//SUB_S
   F3 = F1 - F2;

    if ((F3 < -30.001) || (F3 > -29.999))
    exit(1);

  exit (0);
}
