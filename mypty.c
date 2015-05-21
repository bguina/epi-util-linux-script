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
 **  snprintf
 */
#include <stdio.h>

/*
 **  open
 */
#include <fcntl.h>
/*
 **  ioctl
 */
#include <sys/ioctl.h>
/*
 **  chown
 */
#include <unistd.h>
/*
 **  chmod
 */
#include <sys/stat.h>
/*
 **  tcsetattr
 */
#include <termios.h>

#include "xfuncs.h"
#include "mypty.h"

static int	my_ptsname_r(int fd, char *buff, int sz)
{
  unsigned int	pty;

  if (ioctl(fd, TIOCGPTN, &pty))
    return (-1);
  if (snprintf(buff, sz, "/dev/pts/%u", pty) <= 0)
    return (-1);
  return (0);
}

static int	my_grantpt(char *fslave)
{
  struct stat	st;

  if (stat(fslave, &st) ||
      chown(fslave, getuid(), st.st_gid) ||
      chmod(fslave, 0620))
    return (-1);
  return (0);
}

static int	my_unlockpt(int fd)
{
  int		unlock;

  unlock = 0;
  return (ioctl(fd, TIOCSPTLCK, &unlock));
}

int	my_openpty(int *m, int *s, struct termios *t, struct winsize *w)
{
  char	fslave[512];
  int	master;
  int	slave;

  if ((master = open("/dev/ptmx", O_RDWR)) == -1 ||
      my_ptsname_r(master, fslave, sizeof(fslave)) ||
      my_grantpt(fslave) || my_unlockpt(master) ||
      (slave = open(fslave, O_RDWR | O_NOCTTY)) == -1 ||
      tcsetattr(slave, TCSAFLUSH, t) == -1 ||
      ioctl(slave, TIOCSWINSZ, w) == -1)
  {
    if (master > 0)
      xclose(master);
    return (-1);
  }
  *m = master;
  *s = slave;
  return (0);
}
