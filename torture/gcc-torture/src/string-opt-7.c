/* Copyright (C) 2000  Free Software Foundation.

   Ensure all expected transformations of builtin strncpy occur and
   perform correctly.

   Written by Kaveh R. Ghazi, 11/25/2000.  */

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long
#endif

extern void abort (void);
/* aasmith -- I changed this from size_t to our_size_t because VC error'd out with:
   error C2371: 'size_t' : redefinition; different basic types */
typedef __SIZE_TYPE__ our_size_t;
extern char *strncpy (char *, const char *, our_size_t);
extern int strcmp (const char *, const char *);
extern int strncmp (const char *, const char *, our_size_t);
extern void *memset (void *, int, our_size_t);

int main ()
{
  const char *const src = "hello world";
  const char *src2;
  char dst[64], *dst2;
  
  memset (dst, 0, sizeof (dst));
  if (strncpy (dst, src, 4) != dst || strncmp (dst, src, 4))
    exit(1);

  memset (dst, 0, sizeof (dst));
  if (strncpy (dst+16, src, 4) != dst+16 || strncmp (dst+16, src, 4))
    exit(1);

  memset (dst, 0, sizeof (dst));
  if (strncpy (dst+32, src+5, 4) != dst+32 || strncmp (dst+32, src+5, 4))
    exit(1);

  memset (dst, 0, sizeof (dst));
  dst2 = dst;
  if (strncpy (++dst2, src+5, 4) != dst+1 || strncmp (dst2, src+5, 4)
      || dst2 != dst+1)
    exit(1);

  memset (dst, 0, sizeof (dst));
  if (strncpy (dst, src, 0) != dst || strcmp (dst, ""))
    exit(1);
  
  memset (dst, 0, sizeof (dst));
  dst2 = dst; src2 = src;
  if (strncpy (++dst2, ++src2, 0) != dst+1 || strcmp (dst2, "")
      || dst2 != dst+1 || src2 != src+1)
    exit(1);

  memset (dst, 0, sizeof (dst));
  dst2 = dst; src2 = src;
  if (strncpy (++dst2+5, ++src2+5, 0) != dst+6 || strcmp (dst2+5, "")
      || dst2 != dst+1 || src2 != src+1)
    exit(1);

  memset (dst, 0, sizeof (dst));
  if (strncpy (dst, src, 12) != dst || strcmp (dst, src))
    exit(1);

#if 0
  /* Test at least one instance of the __builtin_ style.  We do this
     to ensure that it works and that the prototype is correct.  */
  memset (dst, 0, sizeof (dst));
  if (__builtin_strncpy (dst, src, 4) != dst || strncmp (dst, src, 4))
    exit(1);
#endif

  return 0;
}

#ifdef __OPTIMIZE__
/* When optimizing, all the above cases should be transformed into
   something else.  So any remaining calls to the original function
   should abort.  */
static char *
strncpy(char *s1, const char *s2, our_size_t n)
{
  exit(1);
}
#endif
