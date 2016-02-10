CFLAGS = -g -Wall -Werror -std=c99 -pedantic \
		-Wmissing-prototypes \
		-Wno-sign-compare \
		-Wno-unused-parameter

RM = rm -f

all: libmjh.a


libmjh.a:
	sh Build_ename.sh > ename.c.inc
	${CC} -c -g ${CFLAGS} *.c
	${RM} $@
	${AR} rs $@ *.o

clean:
	${RM} *.o ename.c.inc libmjh.a
