#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define LOWER_LIMIT 0
#define UPPER_LIMIT 1
#define NUMBER_OF_TRAPEZES 1000000

int main(int argc, char **argv)
{
	long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    struct timeval ts;

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial
    
	float delta_x = (UPPER_LIMIT - LOWER_LIMIT) / (float)NUMBER_OF_TRAPEZES;

	for(long long i = 0; i < NUMBER_OF_TRAPEZES - 2; i++)
	{
		
	}

	gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("delta x: %.60f\n", delta_x);

    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
	return 0;
}
