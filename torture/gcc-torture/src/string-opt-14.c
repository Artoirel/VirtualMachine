/* Copyright (C) 2001  Free Software Foundation.

   Ensure builtin memset and memcpy are optimized away correctly.

   Written by Roger Sayle, 11/23/2001.  */

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long
#endif

extern void abort (void);
/* aasmith -- I changed this from size_t to our_size_t because VC error'd out with:
   error C2371: 'size_t' : redefinition; different basic types */
typedef __SIZE_TYPE__ our_size_t;
extern void *memset (void *s, int c, our_size_t n);
extern void *memcpy (void *dest, const void *src, our_size_t n);

char dst[32];
char src[32];

int
main ()
{
    memset (src, 0, 0);
    memcpy (dst, src, 0);
    return 0;
}

#ifdef __OPTIMIZE__
/* When optimizing, all the above cases should be transformed into
   something else.  So any remaining calls to the original function
   should abort.  */

static void *
memset (void *s, int c, our_size_t n)
{
  exit(1);
}

static void *
memcpy (void *dest, const void *src, our_size_t n)
{
  exit(1);
}
#endif

