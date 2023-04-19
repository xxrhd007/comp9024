CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -Werror -O0 -g
CFILES  = graph.c queue.c stack.c set.c pqueue.c crawler.c
HFILES  = graph.h queue.h stack.h set.h pqueue.h

ifneq ($(shell which dcc),)
	CC = dcc
endif

.PHONY: clean memcheck

crawler: $(CFILES) $(HFILES) 
	$(CC) $(CFLAGS) -o $@ $(CFILES) -lxml2 -lcurl -I/usr/include/libxml2

gcc-crawler:  $(CFILES) $(HFILES)
	gcc $(CFLAGS) -o $@ $(CFILES) -lm -lxml2 -lcurl -I/usr/include/libxml2

micro-web.txt: gcc-crawler
	./gcc-crawler http://www.cse.unsw.edu.au/~cs9024/micro-web crawl > micro-web.txt

memcheck: gcc-crawler micro-web.txt
	valgrind -s --leak-check=full --show-leak-kinds=all ./gcc-crawler micro-web.txt crawl >/dev/null

clean:
	rm -f crawler gcc-crawler micro-web.txt
