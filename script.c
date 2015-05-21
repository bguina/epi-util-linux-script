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
 **  getenv
 */
#include <stdlib.h>

/*
 **  open
 */
#include <fcntl.h>
/*
 **  close
 */
#include <unistd.h>

#include "xfuncs.h"
#include "ptypair.h"
#include "master.h"
#include "slave.h"
#include "script.h"

int	script_init(t_script *s, char **av)
{
  int	open_flags;

  if (!(s->shell = getenv("SHELL")))
    s->shell = DEFAULT_SHELL_PATH;
  if (args_parse(av, &s->o, &s->c, &s->fname) == -1)
    return (-1);
  open_flags = O_WRONLY | O_CREAT;
  open_flags |= (s->o & FLAG(OPTION_APPEND)) ? O_APPEND : O_TRUNC;
  if (!s->fname)
    s->fname = DEFAULT_OUTFILE;
  if ((s->f = open(s->fname, open_flags, 0664)) == -1)
    return (-1);
  if (ptypair_open(s) == 0)
    return (0);
  xclose(s->f);
  return (-1);
}

int	script_run(t_script *s)
{
  pid_t	son;
  int	r;

  xprintf("Script started, file is %s\n", s->fname);
  if ((son = fork()) == -1)
    return (-1);
  if (!son)
    slave_run(s);
  r = master_run(s);
  xprintf("Script done, file is %s\n", s->fname);
  return (r);
}

void	script_free(t_script *s)
{
  ptypair_close(s);
  xclose(s->f);
}

