/*
 ** file.h for someproject in /home/guina_b/
 ** 
 ** Made by benoit guina
 ** Login   <guina_b@epitech.net>
 ** 
 ** Started on  Fri Jan 01 00:00:00 2010 benoit guina
 ** Last update Fri Jan 01 00:00:00 2010 benoit guina
 */

#ifndef H_ARGS
#define H_ARGS

typedef enum	e_option
{
  OPTION_APPEND,
  OPTION_COMMAND,
  OPTION_EXIT,
  OPTION_FLUSH,
  OPTION_QUIET,
  OPTION_TIME
}		e_option;

#define FLAG(option)	((e_option)(1 << option))

int	args_parse(char **av, e_option *o, char **c, char **fname);

#endif
