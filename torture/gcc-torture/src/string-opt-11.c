/* Copyright (C) 2000  Free Software Foundation.

   Ensure all expected transformations of builtin strspn occur and
   perform correctly.

   Written by Kaveh R. Ghazi, 11/27/2000.  */

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long
#endif

extern void abort (void);
/* aasmith -- I changed this from size_t to our_size_t because VC error'd out with:
   error C2371: 'size_t' : redefinition; different basic types */
typedef __SIZE_TYPE__ our_size_t;
extern size_t strspn (const char *, const char *);
extern char *strcpy (char *, const char *);

int main ()
{
  const char *const s1 = "hello world";
  char dst[64], *d2;
  
  if (strspn (s1, "hello") != 5)
    exit(1);
  if (strspn (s1+4, "hello") != 1)
    exit(1);
  if (strspn (s1, "z") != 0)
    exit(1);
  if (strspn (s1, "hello world") != 11)
    exit(1);
  if (strspn (s1, "") != 0)
    exit(1);
  strcpy (dst, s1);
  if (strspn (dst, "") != 0)
    exit(1);
  strcpy (dst, s1); d2 = dst;
  if (strspn (++d2, "") != 0 || d2 != dst+1)
    exit(1);
  strcpy (dst, s1); d2 = dst;
  if (strspn (++d2+5, "") != 0 || d2 != dst+1)
    exit(1);
  if (strspn ("", s1) != 0)
    exit(1);
  strcpy (dst, s1);
  if (strspn ("", dst) != 0)
    exit(1);
  strcpy (dst, s1); d2 = dst;
  if (strspn ("", ++d2) != 0 || d2 != dst+1)
    exit(1);
  strcpy (dst, s1); d2 = dst;
  if (strspn ("", ++d2+5) != 0 || d2 != dst+1)
    exit(1);

  /* Test at least one instance of the __builtin_ style.  We do this
     to ensure that it works and that the prototype is correct.  */
#if 0
  if (__builtin_strspn (s1, "hello") != 5)
    exit(1);
#endif

  return 0;
}

#ifdef __OPTIMIZE__
/* When optimizing, all the above cases should be transformed into
   something else.  So any remaining calls to the original function
   should abort.  */
static our_size_t
strspn (const char *s1, const char *s2)
{
  exit(1);
}
#endif
