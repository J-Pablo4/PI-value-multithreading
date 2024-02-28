/*

Nelly Garcia Sanchez

Juan Pablo Lopez Zuñiga

Equipo Quokka

*/



#include <stdio.h>

#include <stdlib.h>

#include <sys/time.h>

#include <sys/sysinfo.h>

#include <unistd.h>

#include <math.h>

#include <pthread.h>

#include <string.h>



#define LOWER_LIMIT 0 //Empieza el 1/4 circulito

#define UPPER_LIMIT 1 //Termina el 1/4 del circulito

#define NUMBER_OF_TRAPEZES 99999999  //Cuantos trapecios tiene el circulito (osease n)

#define NTHREADS 9

#define MEMBAR __sync_synchronize()



volatile int tickets[NTHREADS];

volatile int choosing[NTHREADS];



void lock(int thread);

void unlock(int thread);

void critical_section(int thread);



void* tfunc(void *args);



int nthreads;



//Variables del circulo

float x = 0;

double sum_x = 0;

double func_eval = 0;

float delta_x;





int main(int argc, char **argv)

{

	memset((void*)tickets, 0, sizeof(tickets));

    	memset((void*)choosing, 0, sizeof(choosing));



	pthread_t tid[NTHREADS];

	int args[NTHREADS];

	int i;	

	

	

	//Variables del Tiempo

	long long start_ts;

	long long stop_ts;

	long long elapsed_time;

	struct timeval ts;

	

    	

    	gettimeofday(&ts, NULL);//Toma el tiempo inicial de la computadora

    	start_ts = ts.tv_sec; // Tiempo inicial

    

	delta_x = (UPPER_LIMIT - LOWER_LIMIT) / (float)NUMBER_OF_TRAPEZES; //Base de los trapecios





	//Inicia Paralelizacion

	for(i=0;i < NTHREADS;i++)

	{

		args[i]=i;

		pthread_create(&tid[i],NULL,tfunc,(void *) &args[i]);

		printf("Se creo el thread %ld \n\r", tid[i]);

	}



	

	// Esperar a que terminen los hilos

	for(i=0;i < NTHREADS;i++)

		pthread_join(tid[i],NULL);

	

	//2(f(xn-1))

	/*for(long double i = 1; i < NUMBER_OF_TRAPEZES; i++)

	{

		x = (float)LOWER_LIMIT + (i * delta_x);

		func_eval = (sqrt(1 - (x*x))*2);

		sum_x += func_eval;

		printf("i: %Lf\n", i);

	}*/

	

	

	

	//(f(x0))

	x = (float)LOWER_LIMIT + (0.0 * delta_x);

	func_eval = sqrt(1 - (x*x));

	sum_x += func_eval;

	

	

	//(f(xn))

	x = (float)LOWER_LIMIT + ((double)NUMBER_OF_TRAPEZES * delta_x);

    	func_eval = sqrt(1 - (x*x));

    	sum_x += func_eval;



    	sum_x *= delta_x;

    	sum_x /= 2.0;



    	printf("Valor de PI: %.15lf\n", sum_x * 4.0);



	gettimeofday(&ts, NULL);

    	stop_ts = ts.tv_sec; // Tiempo final

    	elapsed_time = stop_ts - start_ts;



    	printf("------------------------------\n");

    	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);

	return 0;

}



void *tfunc(void *args)

{

	int nthread = *((int *) args);

	lock(nthread);

	critical_section(nthread);

	unlock(nthread);

}



void lock(int thread)

{

	// Before getting the ticket number

	//"choosing" variable is set to be true

    	choosing[thread] = 1;

 

    	MEMBAR;

    	// Memory barrier applied

    	

    	int max_ticket = 0;

    	

    	// Finding Maximum ticket value among current threads

    	for (int i = 0; i < NTHREADS; ++i) 

    	{

        	int ticket = tickets[i];

        	max_ticket = ticket > max_ticket ? ticket : max_ticket;

    	}

    	

    	// Allotting a new ticket value as MAXIMUM + 1

    	tickets[thread] = max_ticket + 1;

 

    	MEMBAR;

    	choosing[thread] = 0;

    	MEMBAR;

    	

    	// The ENTRY Section starts from here

    	for (int other = 0; other < NTHREADS; ++other) 

    	{

 

        	// Applying the bakery algorithm conditions

        	while (choosing[other]) {}

 

        	MEMBAR;

 

        	while (tickets[other] != 0 && (tickets[other] < tickets[thread] || (tickets[other] == tickets[thread] && other < thread))) {}

    	}

}



// EXIT Section

void unlock(int thread)

{

	MEMBAR;

    	tickets[thread] = 0;

}



// The CRITICAL Section

void critical_section(int thread)

{

	int nthread= thread;

	long double inicio=(nthread*(NUMBER_OF_TRAPEZES/NTHREADS) + 1);

	long double fin=(nthread+1)*(NUMBER_OF_TRAPEZES/NTHREADS);

	

	long double i;



	printf("Hilo %d va desde %Lf hasta %Lf\n",nthread,inicio,fin);

	for(i = inicio; i <= fin;  i++)

	{

		if(i == 99999999)

		{

			break;

		}

		x = (float)LOWER_LIMIT + (i * delta_x);

		func_eval = (sqrt(1 - (x*x))*2);

		sum_x += func_eval;

	}

}

