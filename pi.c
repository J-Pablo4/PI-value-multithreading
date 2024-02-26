#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    struct timeval ts;

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial
    
	long long x = 15;
	for(long long i = 0; i < 4; i++)
	{
		x *= 2;
		sleep(1);
	}

	gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
	return 0;
}
