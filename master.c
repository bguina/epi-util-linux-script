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
 **  BUFSIZ, perror
 */
#include <stdio.h>

/*
 **  errno
 */
#include <errno.h>

/*
 **  waitpid
 */
#include <sys/types.h>
#include <sys/wait.h>
/*
 **  select
 */
#include <sys/select.h>
/*
 **  read
 */
#include <unistd.h>
/*
 **  time, ...
 */
#include <time.h>

#include "xfuncs.h"
#include "script.h"
#include "master.h"

static int	master_redirect(fd_set *set, int from, int to, int f)
{
  if (FD_ISSET(from, set))
  {
    char	buf[BUFSIZ];
    int	sz;

    if ((sz = read(from, buf, sizeof(buf))) >= 0)
    {
      if (!sz)
        printf("read of 0 from %i\n", from);
      if (write(to, buf, sz) == sz)
      {
        if (!from || write(f, buf, sz) == sz)
          return (0);
      }
      return (-1);
    }
  }
  return (0);
}

static int	master_select(t_script *s)
{
  while (1)
  {
    fd_set	set;
    int	status;

    FD_ZERO(&set);
    FD_SET(0, &set);
    FD_SET(s->ptym, &set);
    if (select(FD_SETSIZE, &set, 0, 0, 0) == -1 ||
        master_redirect(&set, 0, s->ptym, s->f) == -1 ||
        master_redirect(&set, s->ptym, 1, s->f) == -1)
      return (-1);
    if (waitpid(-1, &status, WNOHANG) == -1)
    {
      errno = 0;
      s->e = (WIFEXITED(status) && (s->o & FLAG(OPTION_EXIT))) ?
        WEXITSTATUS(status) : 0;
      return (0);
    }
  }
}

static void	master_ftimestamp(int f, int b)
{
  int		e;
  char		*t;
  char		buf[BUFSIZ];
  time_t	tvec;

  e = errno;
  t = "%sScript %s on %s";
  if ((tvec = time((time_t *)NULL)) == (time_t)-1 ||
      strftime(buf, sizeof(buf), "%c\n", localtime(&tvec)) == 0 ||
      dprintf(f, t, (b) ? "\n" : "\n", (b) ? "started" : "stopped", buf) < 0)
    perror("strftime");
  errno = e;
}

int	master_run(struct s_script *s)
{
  int	r;

  xclose(s->ptys);
  master_ftimestamp(s->f, 1);
  r = master_select(s);
  master_ftimestamp(s->f, 0);
  return (r);
}
