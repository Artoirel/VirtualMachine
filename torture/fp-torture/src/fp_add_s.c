float F1 = 15.0;
float F2 = 45.0;
float F3;


int main ()
{
//ADD_S
   F3 = F1 + F2;

    if ((F3 > 60.001) || (F3 < 59.999))
    exit(1);

  exit (0);
}
