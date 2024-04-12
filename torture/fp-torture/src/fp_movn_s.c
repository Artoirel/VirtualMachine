float F1 = 55.236;
float F2 = -88.236;
float F3;

#define ITERATIONS 10

int main()
{
//movn_s : generated MOVN & MOVZ

    int a = 5;
    float float_value = 0.0;
    int i = 0;
    for (i = 0;i < ITERATIONS; i++)
    {
	float_value = (a) ? F1 : F2;
	a--;
    }	

    if ((float_value > 55.236001) || (float_value < 55.235999)) {
        exit(1);
    }

  exit (0);
}








