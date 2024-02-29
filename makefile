all: pi pi_multi

pi: pi.o
	@gcc pi.o -o pi -lm

pi.o: pi.c
	@gcc -c pi.c

pi_multi: pi_multi.o
	@gcc pi_multi.o -o pi_multi -lm -pthread

pi_multi.o: pi_multi.c
	@gcc -c pi_multi.c

clean:
	@rm -f pi pi_multi *.o
