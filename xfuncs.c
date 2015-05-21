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
 **  vprintf
 */
#include <stdarg.h>

/*
 **  errno
 */
#include <errno.h>
/*
 **  close
 */
#include <unistd.h>

#include "xfuncs.h"

void		xfprintf(FILE *stream, const char *format, ...)
{
  int		e;
  va_list	ap;

  e = errno;
  va_start(ap, format);
  if (vfprintf(stream, format, ap) < 0)
    perror("fprintf");
  va_end(ap);
  errno = e;
}

void		xprintf(const char *format, ...)
{
  int		e;
  va_list	ap;

  e = errno;
  va_start(ap, format);
  if (vprintf(format, ap) < 0)
    perror("printf");
  va_end(ap);
  errno = e;
}

void	xclose(int fd)
{
  int	e;

  e = errno;
  if (close(fd) == -1)
    perror("close");
  errno = e;
}
