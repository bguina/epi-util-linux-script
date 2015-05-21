/*
 ** file.c for someproject in /home/guina_b/
 ** 
 ** Made by benoit guina
 ** Login   <guina_b@epitech.net>
 ** 
 ** Started on  Fri Jan 01 00:00:00 2010 benoit guina
 ** Last update Fri Jan 01 00:00:00 2010 benoit guina
 */

/*
 **  perror
 */
#include <stdio.h>

/*
 **  errno
 */
#include <errno.h>

#include "script.h"

int		main(int r, char **av)
{
  t_script	s;

  errno = 0;
  r = 1;
  if (script_init(&s, av) == 0)
  {
    r = script_run(&s);
    script_free(&s);
  }
  if (errno)
    perror(av[0]);
  return (r);
}
