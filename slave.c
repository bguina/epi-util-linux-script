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
 **  exit
 */
#include <stdlib.h>
/*
 **  perror
 */
#include <stdio.h>

/*
 **  dup2, execv, setsid
 */
#include <unistd.h>
/*
 **  ioctl
 */
#include <sys/ioctl.h>

#include "xfuncs.h"
#include "script.h"
#include "slave.h"

static int	my_login_tty(int fd)
{
  if (setsid() == (pid_t)-1 ||
      ioctl(fd, TIOCSCTTY, (char *)NULL) == -1 ||
      dup2(fd, 0) == -1 ||
      dup2(fd, 1) == -1 ||
      dup2(fd, 2) == -1)
    return (-1);
  xclose(fd);
  return (0);
}

void	slave_run(t_script *s)
{
  char	*av[4];

  xclose(s->ptym);
  xclose(s->f);
  my_login_tty(s->ptys);
  av[0] = s->shell;
  av[1] = (s->c) ? "-c" : "-i";
  av[2] = s->c;
  av[3] = 0;
  if (execv(s->shell, av) == -1)
  {
  }
  perror("execl");
  exit(1);
}
