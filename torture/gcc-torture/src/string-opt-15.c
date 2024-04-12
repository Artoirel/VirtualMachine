/* Copyright (C) 2001  Free Software Foundation.

   Ensure that short builtin memcmp are optimized and perform correctly.
   On architectures with a cmpstrsi instruction, this test doesn't determine
   which optimization is being performed, but it does check for correctness.

   Written by Roger Sayle, 12/02/2001.  */

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long
#endif

extern void abort (void);
/* aasmith -- I changed this from size_t to our_size_t because VC error'd out with:
   error C2371: 'size_t' : redefinition; different basic types */
typedef __SIZE_TYPE__ our_size_t;
extern int memcmp (const void *, const void *, our_size_t);
extern char *strcpy (char *, const char *);

int
main ()
{
  char str[8];

  strcpy (str, "3141");

  if ( memcmp (str, str+2, 0) != 0 )
    exit(1);
  if ( memcmp (str+1, str+3, 0) != 0 )
    exit(1);

  if ( memcmp (str+1, str+3, 1) != 0 )
    exit(1);
  if ( memcmp (str, str+2, 1) >= 0 )
    exit(1);
  if ( memcmp (str+2, str, 1) <= 0 )
    exit(1);

  return 0;
}

#ifdef __OPTIMIZE__
/* When optimizing, all the above cases should be transformed into
   something else.  So any remaining calls to the original function
   should abort.  */
static int
memcmp (const char *p1, const char *p2, our_size_t len)
{
  exit(1);
}
#endif

