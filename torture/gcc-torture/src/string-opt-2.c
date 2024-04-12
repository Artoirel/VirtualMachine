/* Copyright (C) 2000  Free Software Foundation.

   Ensure all expected transformations of builtin strpbrk occur and
   perform correctly.

   Written by Kaveh R. Ghazi, 11/6/2000.  */

extern void abort(void);
extern char *strpbrk (const char *, const char *);
extern int strcmp (const char *, const char *);

void fn (const char *foo, const char *const *bar)
{
  if (strcmp(strpbrk ("hello world", "lrooo"), "llo world") != 0)
    exit(1);
  if (strpbrk (foo, "") != 0)
    exit(1);
  if (strpbrk (foo + 4, "") != 0)
    exit(1);
  if (strpbrk (*bar--, "") != 0)
    exit(1);
  if (strpbrk (*bar, "h") != foo)
    exit(1);
  if (strpbrk (foo, "h") != foo)
    exit(1);
  if (strpbrk (foo, "w") != foo + 6)
    exit(1);
  if (strpbrk (foo + 6, "o") != foo + 7)
    exit(1);

#ifdef __GNUC__
  /* Test at least one instance of the __builtin_ style.  We do this
     to ensure that it works and that the prototype is correct.  */
  if (__builtin_strpbrk (foo + 6, "o") != foo + 7)
    exit(1);
#endif
}

int main()
{
  const char *const foo[] = { "hello world", "bye bye world" };
  fn (foo[0], foo + 1);
  return 0;
}


#if defined(__OPTIMIZE__) && defined(__GNUC__) 
/* When optimizing, all the above cases should be transformed into
   something else.  So any remaining calls to the original function
   should abort.  */
/* bhdwiel: removed static from declaration */
char *
strpbrk(const char *s1, const char *s2)
{
  exit(1);
}
#endif
