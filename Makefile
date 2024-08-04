CFLAGS=-g -Wall -pedantic

ww:

clean:
	rm ww

install:	ww
	cp -a ww ~/bin/ww
