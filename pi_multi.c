/*
Nelly Garcia Sanchez
Juan Pablo Lopez Zuñiga
Equipo: Quokka
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

#define LOWER_LIMIT 0 //Empieza el 1/4 del circulito
#define UPPER_LIMIT 1 //Termina el 1/4 del circulito
#define NUMBER_OF_TRAPEZES 999999999  //Cuantos trapecios tiene el circulito (osease n)
#define NTHREADS 9 //Numero de threads
#define MEMBAR __sync_synchronize()

volatile int tickets[NTHREADS];//tickets del algoritmo de la panaderia
volatile int choosing[NTHREADS];//arreglo para saber que un thread esta escogiendo ticket

void lock(int thread); //Funcion para obtener ticket y esperar a que los otros threads tengan un ticket o que terminen de ingresar a la seccion critica
void unlock(int thread); //Funcion para decir que un thread ya termino de usar la seccion critica
void critical_section(int thread); // Funcion para acceder a la seccion critica.

void* tfunc(void *args);

//Variables globales del circulo
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
		pthread_create(&tid[i],NULL,tfunc,(void *) &args[i]); //se crean los threads
		printf("Se creo el thread %ld \n\r", tid[i]);
	}

	// Esperar a que terminen los threads
	for(i=0;i < NTHREADS;i++)
		pthread_join(tid[i],NULL);

	//(f(x0)) Calculo del primer trapecio
	x = (float)LOWER_LIMIT + (0.0 * delta_x); //x0 = a+0*delta x
	func_eval = sqrt(1 - (x*x)); //f(x0)
	sum_x += func_eval;

	//(f(xn)) Calculo del ultimo trapecio
	x = (float)LOWER_LIMIT + ((double)NUMBER_OF_TRAPEZES * delta_x); //xn = a+n*delta x
    	func_eval = sqrt(1 - (x*x)); //f(xn)
    	sum_x += func_eval;

    	sum_x *= delta_x; //delta x * sumatoria de todas las areas
    	sum_x /= 2.0; //sumatoria de todas las areas / 2

    	printf("Valor de PI: %.10lf\n", sum_x * 4.0);

	gettimeofday(&ts, NULL);// Toma el tiempo final de la computadora
    	stop_ts = ts.tv_sec; // Tiempo final
    	elapsed_time = stop_ts - start_ts; //Calculo de tiempo de ejecucion

    	printf("------------------------------\n");
    	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);

	return 0;
}

void *tfunc(void *args)
{
	int nthread = *((int *) args);
	lock(nthread); //Inicio del algoritmo de la panaderia
	critical_section(nthread); //Acceso a la seccion critica
	unlock(nthread); //Fin del algoritmo de la panaderia
}

void lock(int thread)
{
	//El thread indica que va a empezar a tomar un ticket
    	choosing[thread] = 1;

	MEMBAR;

    	int max_ticket = 0; //variable para definir el ticket con el turno mas alto que se le dio a un thread

    	// Operacion para encontrar el ticket con el turno mas alto entre los threads que estan en ejecucion
    	for (int i = 0; i < NTHREADS; ++i)
    	{
        	int ticket = tickets[i];
        	max_ticket = ticket > max_ticket ? ticket : max_ticket;
    	}

    	// Asignacion a nuestro thread el tueno mas alto mas 1
    	tickets[thread] = max_ticket + 1;

    	MEMBAR;
    	choosing[thread] = 0; //Decimos que el thread termino de elegir ticket
    	MEMBAR;

    	//Operaciones para checar que todos los threads tengan un turno asignado y revisar que thread tiene el ticket con el turno mas bajo
    	for (int other = 0; other < NTHREADS; ++other)
    	{
		//Si los threads no han terminado de escoger turno, se bloquean
        	while (choosing[other]) {}
        	MEMBAR;
		
		//Esperar a que el thread con el turno mas bajo termine de acceder a la seccion critica
        	while (tickets[other] != 0 && (tickets[other] < tickets[thread] || (tickets[other] == tickets[thread] && other < thread))) {}
    	}
}

void unlock(int thread)
{
	MEMBAR;
    	tickets[thread] = 0; //Asignacion para indicar que el thread que estaba en ejecucion, termino de acceder a la seccion critica
}

void critical_section(int thread)
{
	int nthread= thread;
	long double inicio=(nthread*(NUMBER_OF_TRAPEZES/NTHREADS) + 1); //Inicio de iteracion de cada thread
	long double fin=(nthread+1)*(NUMBER_OF_TRAPEZES/NTHREADS); //Fin de iteracion de cada thread

	long double i;

	printf("Hilo %d va desde %Lf hasta %Lf\n",nthread,inicio,fin);
	
	// 2*f(n-1) Operaciones para calcular los trapecios de en medio con threads
	for(i = inicio; i <= fin;  i++)
	{
		//Condicion para no calcular el ultimo trapecio
		if(i == 99999999)
		{
			break;
		}
		x = (float)LOWER_LIMIT + (i * delta_x); //xi = a+i*delta x
		func_eval = (sqrt(1 - (x*x))*2); //2*f(xn-1)
		sum_x += func_eval;
	}
}
