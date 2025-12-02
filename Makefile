CC = clang
CFLAGS = -Wall -Wextra -std=c99 -Ilib

LIB_SRCS = lib/*.c
LIB_OBJS = $(LIB_SRCS:.c=.o)

# generic build rule:
# any folder like day01, day02...
%/solution: %/solution.c $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# helper targets

.PHONY: build run clean format

# build e.g.: make build day01
build:
	@if [ "$(word 2,$(MAKECMDGOALS))" = "" ]; then \
		echo "usage: make build day01"; exit 1; \
	fi
	$(MAKE) $(word 2,$(MAKECMDGOALS))/solution

# run e.g.: make run day01
run:
	@if [ "$(word 2,$(MAKECMDGOALS))" = "" ]; then \
		echo "usage: make run day01"; exit 1; \
	fi
	$(MAKE) $(word 2,$(MAKECMDGOALS))/solution
	./$(word 2,$(MAKECMDGOALS))/solution

clean:
	rm -f $(LIB_OBJS) */solution

format:
	find . -name '*.c' -o -name '*.h' | xargs clang-format -i
