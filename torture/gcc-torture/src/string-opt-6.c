/* Copyright (C) 2000  Free Software Foundation.

   Ensure builtin memcpy and strcpy perform correctly.

   Written by Jakub Jelinek, 11/24/2000.  */

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long
#endif

extern void abort (void);
extern char *strcpy (char *, const char *);
/* aasmith -- I changed this from size_t to our_size_t because VC error'd out with:
   error C2371: 'size_t' : redefinition; different basic types */
typedef __SIZE_TYPE__ our_size_t;
extern void *memcpy (void *, const void *, our_size_t);
extern int memcmp (const void *, const void *, our_size_t);

char p[32] = "";

int main()
{
  if (strcpy (p, "abcde") != p || memcmp (p, "abcde", 6))
    exit(1);
  if (strcpy (p + 16, "vwxyz" + 1) != p + 16 || memcmp (p + 16, "wxyz", 5))
    exit(1);
  if (strcpy (p + 1, "") != p + 1 || memcmp (p, "a\0cde", 6))
    exit(1);  
  if (strcpy (p + 3, "fghij") != p + 3 || memcmp (p, "a\0cfghij", 9))
    exit(1);
  if (memcpy (p, "ABCDE", 6) != p || memcmp (p, "ABCDE", 6))
    exit(1);
  if (memcpy (p + 16, "VWX" + 1, 2) != p + 16 || memcmp (p + 16, "WXyz", 5))
    exit(1);
  if (memcpy (p + 1, "", 1) != p + 1 || memcmp (p, "A\0CDE", 6))
    exit(1);  
  if (memcpy (p + 3, "FGHI", 4) != p + 3 || memcmp (p, "A\0CFGHIj", 9))
    exit(1);

#if 0
  /* Test at least one instance of the __builtin_ style.  We do this
     to ensure that it works and that the prototype is correct.  */
  if (__builtin_strcpy (p, "abcde") != p || memcmp (p, "abcde", 6))
    exit(1);
  if (__builtin_memcpy (p, "ABCDE", 6) != p || memcmp (p, "ABCDE", 6))
    exit(1);
#endif

  return 0;
}

#ifdef __OPTIMIZE__
/* When optimizing, all the above cases should be transformed into
   something else.  So any remaining calls to the original function
   should abort.  */
/* bhdwiel: removed static from declaration */
char *
strcpy (char *d, const char *s)
{
  exit(1);
}
#endif
