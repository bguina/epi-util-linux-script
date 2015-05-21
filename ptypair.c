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
 **  struct termios
 */
#include <termio.h>

/*
 **  ioctl
 */
#include <sys/ioctl.h>

#include "xfuncs.h"
#include "script.h"
#include "mypty.h"
#include "ptypair.h"

static int		ptypair_termcaps_init(struct s_script *s)
{
  struct termios	t;

  if (tcgetattr(0, &s->tb) == -1)
    return (-1);
  t = s->tb;
  t.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP |
      INLCR | IGNCR | ICRNL | IXON);
  t.c_oflag &= ~OPOST;
  t.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  t.c_cflag &= ~(CSIZE | PARENB);
  t.c_cflag |= CS8;
  if (tcsetattr(0, TCSAFLUSH, &t) == -1)
    return (-1);
  return (0);
}

static void	ptypair_termcaps_restore(struct s_script *s)
{
  if (tcsetattr(0, TCSAFLUSH, &s->tb))
  {
  }
}

int			ptypair_open(struct s_script *s)
{
  struct winsize	win;

  if (ioctl(0, TIOCGWINSZ, (char *)&win) == -1 ||
      ptypair_termcaps_init(s) == -1)
    return (-1);
  ioctl(0, TIOCGWINSZ, (char *)&win);
  if (my_openpty(&s->ptym, &s->ptys, &s->tb, &win) == 0)
    return (0);
  ptypair_termcaps_restore(s);
  return (-1);
}

void	ptypair_close(struct s_script *s)
{
  ptypair_termcaps_restore(s);
}
