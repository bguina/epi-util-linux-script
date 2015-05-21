/*
 ** file.h for someproject in /home/guina_b/
 ** 
 ** Made by benoit guina
 ** Login   <guina_b@epitech.net>
 ** 
 ** Started on  Fri Jan 01 00:00:00 2010 benoit guina
 ** Last update Fri Jan 01 00:00:00 2010 benoit guina
 */

#ifndef H_MYPTY
#define H_MYPTY

struct termios;
struct winsize;

int my_openpty(int *m, int *s, struct termios *t, struct winsize *w);

#endif
