/* Copyright (C) 2000, 2001  Free Software Foundation.

   Ensure all expected transformations of builtin strncmp occur and
   perform correctly.

   Written by Kaveh R. Ghazi, 11/26/2000.  */

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long
#endif

extern void abort (void);
/* aasmith -- I changed this from size_t to our_size_t because VC error'd out with:
   error C2371: 'size_t' : redefinition; different basic types */
typedef __SIZE_TYPE__ our_size_t;
extern int strncmp (const char *, const char *, our_size_t);

int main ()
{
  const char *const s1 = "hello world";
  const char *s2, *s3;
  
  if (strncmp (s1, "hello world", 12) != 0)
    exit(1);
  if (strncmp ("hello world", s1, 12) != 0)
    exit(1);
  if (strncmp ("hello", "hello", 6) != 0)
    exit(1);
  if (strncmp ("hello", "hello", 2) != 0)
    exit(1);
  if (strncmp ("hello", "hello", 100) != 0)
    exit(1);
  if (strncmp (s1+10, "d", 100) != 0)
    exit(1);
  if (strncmp (10+s1, "d", 100) != 0)
    exit(1);
  if (strncmp ("d", s1+10, 1) != 0)
    exit(1);
  if (strncmp ("d", 10+s1, 1) != 0)
    exit(1);
  if (strncmp ("hello", "aaaaa", 100) <= 0)
    exit(1);
  if (strncmp ("aaaaa", "hello", 100) >= 0)
    exit(1);
  if (strncmp ("hello", "aaaaa", 1) <= 0)
    exit(1);
  if (strncmp ("aaaaa", "hello", 1) >= 0)
    exit(1);

  s2 = s1; s3 = s1+4;
  if (strncmp (++s2, ++s3, 0) != 0 || s2 != s1+1 || s3 != s1+5)
    exit(1);
  s2 = s1;
  if (strncmp (++s2, "", 1) <= 0 || s2 != s1+1)
    exit(1);
  if (strncmp ("", ++s2, 1) >= 0 || s2 != s1+2)
    exit(1);
  if (strncmp (++s2, "", 100) <= 0 || s2 != s1+3)
    exit(1);
  if (strncmp ("", ++s2, 100) >= 0 || s2 != s1+4)
    exit(1);
  if (strncmp (++s2+6, "", 100) != 0 || s2 != s1+5)
    exit(1);
  if (strncmp ("", ++s2+5, 100) != 0 || s2 != s1+6)
    exit(1);
  if (strncmp ("ozz", ++s2, 1) != 0 || s2 != s1+7)
    exit(1);
  if (strncmp (++s2, "rzz", 1) != 0 || s2 != s1+8)
    exit(1);
  s2 = s1; s3 = s1+4;
  if (strncmp (++s2, ++s3+2, 1) >= 0 || s2 != s1+1 || s3 != s1+5)
    exit(1);
#if defined(__i386__) || defined (__pj__) || defined (__i370__)
  /* These tests work on platforms which support cmpstrsi.  */
  s2 = s1;
  if (strncmp (++s2, "ello", 3) != 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("ello", ++s2, 3) != 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp (++s2, "ello", 4) != 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("ello", ++s2, 4) != 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp (++s2, "ello", 5) <= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("ello", ++s2, 5) >= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp (++s2, "ello", 6) <= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("ello", ++s2, 6) >= 0 || s2 != s1+1)
    exit(1);

  s2 = s1;
  if (strncmp (++s2, "zllo", 3) >= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("zllo", ++s2, 3) <= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp (++s2, "zllo", 4) >= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("zllo", ++s2, 4) <= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp (++s2, "zllo", 5) >= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("zllo", ++s2, 5) <= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp (++s2, "zllo", 6) >= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("zllo", ++s2, 6) <= 0 || s2 != s1+1)
    exit(1);

  s2 = s1;
  if (strncmp (++s2, "allo", 3) <= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("allo", ++s2, 3) >= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp (++s2, "allo", 4) <= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("allo", ++s2, 4) >= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp (++s2, "allo", 5) <= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("allo", ++s2, 5) >= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp (++s2, "allo", 6) <= 0 || s2 != s1+1)
    exit(1);
  s2 = s1;
  if (strncmp ("allo", ++s2, 6) >= 0 || s2 != s1+1)
    exit(1);

  s2 = s1; n = 2; x = 1;
  if (strncmp (++s2, s1+(x&3), ++n) != 0 || s2 != s1+1 || n != 3)
    exit(1);
  s2 = s1; n = 2; x = 1;
  if (strncmp (s1+(x&3), ++s2, ++n) != 0 || s2 != s1+1 || n != 3)
    exit(1);
  s2 = s1; n = 3; x = 1;
  if (strncmp (++s2, s1+(x&3), ++n) != 0 || s2 != s1+1 || n != 4)
    exit(1);
  s2 = s1; n = 3; x = 1;
  if (strncmp (s1+(x&3), ++s2, ++n) != 0 || s2 != s1+1 || n != 4)
    exit(1);
  s2 = s1; n = 4; x = 1;
  if (strncmp (++s2, s1+(x&3), ++n) != 0 || s2 != s1+1 || n != 5)
    exit(1);
  s2 = s1; n = 4; x = 1;
  if (strncmp (s1+(x&3), ++s2, ++n) != 0 || s2 != s1+1 || n != 5)
    exit(1);
  s2 = s1; n = 5; x = 1;
  if (strncmp (++s2, s1+(x&3), ++n) != 0 || s2 != s1+1 || n != 6)
    exit(1);
  s2 = s1; n = 5; x = 1;
  if (strncmp (s1+(x&3), ++s2, ++n) != 0 || s2 != s1+1 || n != 6)
    exit(1);

  s2 = s1; n = 2;
  if (strncmp (++s2, "zllo", ++n) >= 0 || s2 != s1+1 || n != 3)
    exit(1);
  s2 = s1; n = 2; x = 1;
  if (strncmp ("zllo", ++s2, ++n) <= 0 || s2 != s1+1 || n != 3)
    exit(1);
  s2 = s1; n = 3; x = 1;
  if (strncmp (++s2, "zllo", ++n) >= 0 || s2 != s1+1 || n != 4)
    exit(1);
  s2 = s1; n = 3; x = 1;
  if (strncmp ("zllo", ++s2, ++n) <= 0 || s2 != s1+1 || n != 4)
    exit(1);
  s2 = s1; n = 4; x = 1;
  if (strncmp (++s2, "zllo", ++n) >= 0 || s2 != s1+1 || n != 5)
    exit(1);
  s2 = s1; n = 4; x = 1;
  if (strncmp ("zllo", ++s2, ++n) <= 0 || s2 != s1+1 || n != 5)
    exit(1);
  s2 = s1; n = 5; x = 1;
  if (strncmp (++s2, "zllo", ++n) >= 0 || s2 != s1+1 || n != 6)
    exit(1);
  s2 = s1; n = 5; x = 1;
  if (strncmp ("zllo", ++s2, ++n) <= 0 || s2 != s1+1 || n != 6)
    exit(1);

  s2 = s1; n = 2;
  if (strncmp (++s2, "allo", ++n) <= 0 || s2 != s1+1 || n != 3)
    exit(1);
  s2 = s1; n = 2; x = 1;
  if (strncmp ("allo", ++s2, ++n) >= 0 || s2 != s1+1 || n != 3)
    exit(1);
  s2 = s1; n = 3; x = 1;
  if (strncmp (++s2, "allo", ++n) <= 0 || s2 != s1+1 || n != 4)
    exit(1);
  s2 = s1; n = 3; x = 1;
  if (strncmp ("allo", ++s2, ++n) >= 0 || s2 != s1+1 || n != 4)
    exit(1);
  s2 = s1; n = 4; x = 1;
  if (strncmp (++s2, "allo", ++n) <= 0 || s2 != s1+1 || n != 5)
    exit(1);
  s2 = s1; n = 4; x = 1;
  if (strncmp ("allo", ++s2, ++n) >= 0 || s2 != s1+1 || n != 5)
    exit(1);
  s2 = s1; n = 5; x = 1;
  if (strncmp (++s2, "allo", ++n) <= 0 || s2 != s1+1 || n != 6)
    exit(1);
  s2 = s1; n = 5; x = 1;
  if (strncmp ("allo", ++s2, ++n) >= 0 || s2 != s1+1 || n != 6)
    exit(1);

#endif  
  
#if 0
  /* Test at least one instance of the __builtin_ style.  We do this
     to ensure that it works and that the prototype is correct.  */
  if (__builtin_strncmp ("hello", "a", 100) <= 0)
    exit(1);
#endif

  return 0;
}

#ifdef __OPTIMIZE__
/* When optimizing, all the above cases should be transformed into
   something else.  So any remaining calls to the original function
   should abort.  */
static int
strncmp(const char *s1, const char *s2, our_size_t n)
{
  exit(1);
}
#endif
