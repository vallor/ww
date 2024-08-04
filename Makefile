CFLAGS=-g -Wall -pedantic -std=c2x

ww:

clean:
	rm ww

install:	ww
	cp -a ww ~/bin/ww
