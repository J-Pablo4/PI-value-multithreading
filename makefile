pi : pi.o
	@gcc pi.o -o pi -lm

pi.o : pi.c
	@gcc -c pi.c
