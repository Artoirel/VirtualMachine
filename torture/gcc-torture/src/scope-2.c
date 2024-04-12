static int v = 3;

f ()
{
  int v = 4;
  {
    extern int v;
    if (v != 3)
      exit(1);
  }
}

main ()
{
  f ();
  exit (0);
}
