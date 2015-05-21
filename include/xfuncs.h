/*
 ** file.h for someproject in /home/guina_b/
 ** 
 ** Made by benoit guina
 ** Login   <guina_b@epitech.net>
 ** 
 ** Started on  Fri Jan 01 00:00:00 2010 benoit guina
 ** Last update Fri Jan 01 00:00:00 2010 benoit guina
 */

#ifndef H_XFUNCS
#define H_XFUNCS

/*
 **  FILE
 */
#include <stdio.h>

void	xfprintf(FILE *stream, const char *format, ...);
void	xprintf(const char *format, ...);
void	xclose(int fd);

#endif
