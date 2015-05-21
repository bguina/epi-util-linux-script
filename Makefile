OUT=	my_script
CC=	gcc
RM=	rm -f

CFILES=	args.c\
	main.c\
	master.c\
	mypty.c\
	ptypair.c\
	script.c\
	slave.c\
	xfuncs.c

OFILES=	$(CFILES:.c=.o)

CFLAGS=	-Iinclude -g -Wall -Wextra
LDFLAGS=

all: out

out: $(OFILES)
	$(CC) $(OFILES) $(LDFLAGS) -o $(OUT)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(OUT)

re: clean fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(@F)
