# NAME:    PC performance test
# VERSION: 0.0.2
# AUTHOR:  MAROUSEK S.
# DATE:    2021/5/30

CFLAGS+= -std=gnu99 -o0
LDFLAGS= -pthread

BINARIES=test

all: ${BINARIES}

OBJS=${patsubst %.c,%.o,${wildcard *.c}}

test: ${OBJS}
	$gcc ${OBJS} ${LDFLAGS} -o $@
	rm -f ${OBJS}

${OBJS}: %.o: %.c
	$gcc -c ${CFLAGS} $< -o $@

clean:
	rm -f ${BINARIES} ${OBJS} $.pc_test_bench.txt
