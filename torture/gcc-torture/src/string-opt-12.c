/* Copyright (C) 2000  Free Software Foundation.

   Ensure all expected transformations of builtin strcspn occur and
   perform correctly.

   Written by Kaveh R. Ghazi, 11/27/2000.  */

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long
#endif

extern void abort (void);
/* aasmith -- I changed this from size_t to our_size_t because VC error'd out with:
   error C2371: 'size_t' : redefinition; different basic types */
typedef __SIZE_TYPE__ our_size_t;
extern our_size_t strcspn (const char *, const char *);
extern char *strcpy (char *, const char *);

int main ()
{
  const char *const s1 = "hello world";
  char dst[64], *d2;
  
  if (strcspn (s1, "hello") != 0)
    exit(1);
  if (strcspn (s1, "z") != 11)
    exit(1);
  if (strcspn (s1+4, "z") != 7)
    exit(1);
  if (strcspn (s1, "hello world") != 0)
    exit(1);
  if (strcspn (s1, "") != 11)
    exit(1);
  strcpy (dst, s1);
  if (strcspn (dst, "") != 11)
    exit(1);
  strcpy (dst, s1); d2 = dst;
  if (strcspn (++d2, "") != 10 || d2 != dst+1)
    exit(1);
  strcpy (dst, s1); d2 = dst;
  if (strcspn (++d2+5, "") != 5 || d2 != dst+1)
    exit(1);
  if (strcspn ("", s1) != 0)
    exit(1);
  strcpy (dst, s1);
  if (strcspn ("", dst) != 0)
    exit(1);
  strcpy (dst, s1); d2 = dst;
  if (strcspn ("", ++d2) != 0 || d2 != dst+1)
    exit(1);
  strcpy (dst, s1); d2 = dst;
  if (strcspn ("", ++d2+5) != 0 || d2 != dst+1)
    exit(1);

  /* Test at least one instance of the __builtin_ style.  We do this
     to ensure that it works and that the prototype is correct.  */
#if 0
  if (__builtin_strcspn (s1, "z") != 11)
    exit(1);
#endif

  return 0;
}

#ifdef __OPTIMIZE__
/* When optimizing, all the above cases should be transformed into
   something else.  So any remaining calls to the original function
   should abort.  */
static our_size_t
strcspn (const char *s1, const char *s2)
{
  exit(1);
}
#endif
