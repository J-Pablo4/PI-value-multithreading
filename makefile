pi : pi.o
	@gcc pi.o -o pi

pi.o : pi.c
	@gcc -c pi.c
