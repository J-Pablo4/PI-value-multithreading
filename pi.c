/*
Nelly Garcia Sanchez
Juan Pablo Lopez Zuñiga
Equipo: Quokka
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

#define LOWER_LIMIT 0 //Empieza el 1/4 de circulito
#define UPPER_LIMIT 1 //Termina el 1/4 de circulito
#define NUMBER_OF_TRAPEZES 999999999 //Cuantos trapecios tiene el circulito (osease n)

int main(int argc, char **argv)
{
	//Variables del Tiempo
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	struct timeval ts;
	
	//Variables del circulo
	float x = 0;
    	double sum_x = 0;
    	double func_eval = 0;
    	float delta_x;

    	gettimeofday(&ts, NULL);//Toma el tiempo inicial de la computadora
    	start_ts = ts.tv_sec; // Tiempo inicial
    
	delta_x = (UPPER_LIMIT - LOWER_LIMIT) / (float)NUMBER_OF_TRAPEZES; //Base de los trapecios (delta x = (b-a)/n)

	//2*f(xn-1) Calculo de los trapecios de en medio
	for(long double i = 1; i < NUMBER_OF_TRAPEZES; i++)
	{
		x = (float)LOWER_LIMIT + (i * delta_x); //xi = a+i*delta x
		func_eval = (sqrt(1 - (x*x))*2); //2*f(xn-1)
		sum_x += func_eval;
		printf("i: %Lf\n", i);
	}

	//f(x0) Calculo del primer trapecio
	x = (float)LOWER_LIMIT + (0.0 * delta_x); //x0 = a+0*delta x
	func_eval = sqrt(1 - (x*x)); //f(x0)
	sum_x += func_eval;

	//f(xn) Calculo del ultimo trapecio
	x = (float)LOWER_LIMIT + ((double)NUMBER_OF_TRAPEZES * delta_x); //xn = a+n*delta x
    	func_eval = sqrt(1 - (x*x)); //f(xn)
    	sum_x += func_eval;

    	sum_x *= delta_x; //delta x * sumatoria de todas las areas
    	sum_x /= 2.0; //sumatoria de todas las areas entre 2

    	printf("Valor de PI: %.15lf\n", sum_x * 4.0);

	gettimeofday(&ts, NULL); //Toma el tiempo final de la computadpra
    	stop_ts = ts.tv_sec; // Tiempo final
    	elapsed_time = stop_ts - start_ts; //Calculo del tiempo de ejecucion

    	printf("------------------------------\n");
    	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
	return 0;
}
