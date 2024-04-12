float F1 = 225.0;
float F2 = 5.0e+03;
float F3;
float F4;

int main ()
{
//mov_s : the move instruction was not generated
   F3 = F1;

    if ((F3 > 225.001) || (F3 < 224.999))
    exit(1);

  exit (0);
}
