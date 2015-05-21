/*
 ** fname.c for someproject in /home/guina_b/
 ** 
 ** Made by benoit guina
 ** Login   <guina_b@epitech.net>
 ** 
 ** Started on  Fri Jan 01 00:00:00 2010 benoit guina
 ** Last update Fri Jan 01 00:00:00 2010 benoit guina
 */

#include "xfuncs.h"
#include "args.h"

static int	args_string_parse(char *bin, char *s, e_option *o, char **c)
{
  e_option	a;

  while (*s)
  {
    a = (*s == 'a') ? OPTION_APPEND :
      (*s == 'c') ? OPTION_COMMAND :
      (*s == 'e') ? OPTION_EXIT :
      (*s == 'f') ? OPTION_FLUSH :
      (*s == 'q') ? OPTION_QUIET :
      (*s == 't') ? OPTION_TIME :
      -1;
    if (a == (e_option)-1)
    {
      xfprintf(stderr, "%s: invalid option -- '%c'\n", bin, *s);
      return (1);
    }
    if (a == OPTION_COMMAND && s[1])
    {
      *c = s + 1;
      return (0);
    }
    *o |= FLAG(a);
    s++;
  }
  return (0);
}

int	args_parse(char **av, e_option *o, char **c, char **fname)
{
  char	*bin;

  bin = *av;
  *o = 0;
  *c = 0;
  *fname = 0;
  while (*++av)
    if (*o & FLAG(OPTION_COMMAND))
    {
      *c = *av;
      *o &= ~FLAG(OPTION_COMMAND);
    }
    else if (**av == '-')
    {
      if (args_string_parse(bin, *av + 1, o, c) != 0)
        return (1);
    }
    else if (!*fname)
      *fname = *av;
  if (*o & FLAG(OPTION_COMMAND))
  {
    xfprintf(stderr, "%s: option requires an argument -- 'c'\n", av[0]);
    return (1);
  }
  return (0);
}
