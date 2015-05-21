/*
 ** file.h for someproject in /home/guina_b/
 ** 
 ** Made by benoit guina
 ** Login   <guina_b@epitech.net>
 ** 
 ** Started on  Fri Jan 01 00:00:00 2010 benoit guina
 ** Last update Fri Jan 01 00:00:00 2010 benoit guina
 */

#ifndef H_SCRIPT
#define H_SCRIPT

/*
 **  struct termios
 */
#include <termios.h>
#include <unistd.h>

#include "args.h"

typedef struct	s_script
{
  e_option o;
  char *c;
  char *fname;
  int e;
  struct termios tb;
  int f;
  int ptym;
  int ptys;
  char *shell;
}		t_script;

#define DEFAULT_SHELL_PATH	"/bin/bash"
#define DEFAULT_OUTFILE		"typescript"

int	script_init(t_script *s, char **av);
int	script_run(t_script *s);
void	script_free(t_script *s);

#endif
