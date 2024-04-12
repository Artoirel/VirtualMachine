/* Copyright (C) 2001  Free Software Foundation.

   Ensure all builtin strlen comparisons against zero are optimized
   and perform correctly. The multiple calls to strcpy are to prevent
   the potentially "pure" strlen calls from being removed by CSE.

   Written by Roger Sayle, 11/02/2001.  */

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long
#endif

extern void abort (void);
/* aasmith -- I changed this from size_t to our_size_t because VC error'd out with:
   error C2371: 'size_t' : redefinition; different basic types */
typedef __SIZE_TYPE__ our_size_t;
extern our_size_t strlen (const char *);
extern char *strcpy (char *, const char *);

int
main ()
{
  char str[8];
  char *ptr;

  ptr = str;
  strcpy (ptr, "nts");
  if (strlen (ptr) == 0)
    exit(1);

  strcpy (ptr, "nts");
  if (strlen (ptr) < 1)
    exit(1);

  strcpy (ptr, "nts");
  if (strlen (ptr) <= 0)
    exit(1);

  strcpy (ptr, "nts");
  if (strlen (ptr+3) != 0)
    exit(1);

  strcpy (ptr, "nts");
  if (strlen (ptr+3) > 0)
    exit(1);

  strcpy (ptr, "nts");
  if (strlen (str+3) >= 1)
    exit(1);

  return 0;
}

#ifdef __OPTIMIZE__
/* When optimizing, all the above cases should be transformed into
   something else.  So any remaining calls to the original function
   should abort.  */
static our_size_t
strlen (const char *s)
{
  exit(1);
}
#endif

