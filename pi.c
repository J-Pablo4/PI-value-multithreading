#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

#define LOWER_LIMIT 0
#define UPPER_LIMIT 1
#define NUMBER_OF_TRAPEZES 999999999

int main(int argc, char **argv)
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	struct timeval ts;
	
	float x = 0;
    	double sum_x = 0;
    	double func_eval = 0;
    	float delta_x;
    	double total = 0;

    	gettimeofday(&ts, NULL);
    	start_ts = ts.tv_sec; // Tiempo inicial
    
	delta_x = (UPPER_LIMIT - LOWER_LIMIT) / (float)NUMBER_OF_TRAPEZES;

	for(long double i = 1; i < NUMBER_OF_TRAPEZES; i++)
	{
		x = (float)LOWER_LIMIT + (i * delta_x);
		func_eval = (sqrt(1 - (x*x))*2);
		sum_x += func_eval;
	}

	x = (float)LOWER_LIMIT + (0.0 * delta_x);
	func_eval = sqrt(1 - (x*x));
	sum_x += func_eval;

	x = (float)LOWER_LIMIT + ((double)NUMBER_OF_TRAPEZES * delta_x);
    	func_eval = sqrt(1 - (x*x));
    	sum_x += func_eval;

    	sum_x *= delta_x;
    	sum_x /= 2.0;

    	printf("Area bajo la curva por 4: %.30lf\n", sum_x * 4.0);

	gettimeofday(&ts, NULL);
    	stop_ts = ts.tv_sec; // Tiempo final
    	elapsed_time = stop_ts - start_ts;

    	printf("------------------------------\n");
    	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
	return 0;
}
