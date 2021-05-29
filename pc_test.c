/********************************************
 ********************************************
 ***                                      ***
 ***    NAME:    PC performance test      ***
 ***    VERSION: 0.0.1                    ***
 ***    AUTHOR:  MAROUSEK S.              ***
 ***    DATE:    2021/5/30                ***
 ***                                      ***
 ********************************************
 ********************************************/

/**************************************************************************
 *                                                                        *
 * Info:                                                                  *
 *                                                                        *
 *    compile:          'make'   (or 'gcc pc_test.c -lpthread -o test')   *
 *    execute:          './test'                                          *
 *    remove binary:    'make clean'                                      *
 *                                                                        *
 *    score == 100      same as reference value                           *
 *    score >  100      better                                            *
 *    score <  100      worse                                             *
 *                                                                        *
 **************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define RUN_TIME 1000		// ms

void *threadTimeCount(void *);

_Bool end = 0;

int main()
{
	FILE *save_data;
	void *(*thr_function[])(void *) = { threadTimeCount };
	pthread_t threads[1];
	pthread_create(&threads[0], NULL, thr_function[0], NULL);
	char *bench_txt = "pc_test_bench.txt";

	/* Test computation speed */
	long long number_of_operations = 0;
	while (!end) {
		long long divide = 1 + number_of_operations;
		for (int i = 1; i <= 18; i++) {
			divide = divide * i;
			divide++;
		}
		for (int i = 1; i <= 18; i++) {
			divide--;
			divide = divide / i;
		}
		printf("\r%lld", divide);
		number_of_operations++;
	}
	printf("\r");
	printf("Computation score     %f\n",
	       (float)(number_of_operations / RUN_TIME / 9.41));
	pthread_detach(threads[0]);
	pthread_create(&threads[0], NULL, thr_function[0], NULL);
	save_data = fopen(bench_txt, "w");

	/* Test memory access speed */
	number_of_operations = 0;
	end = 0;
	long long file_out;
	while (!end) {
		long long divide = 1 + number_of_operations;
		for (int i = 1; i <= 18; i++) {
			divide = divide * i;
			divide++;
		}
		fprintf(save_data, "%lld\n", divide);
		fclose(save_data);
		save_data = fopen(bench_txt, "r");
		fscanf(save_data, "%lld", &file_out);
		printf("\r%lld", file_out);
		fclose(save_data);
		save_data = fopen(bench_txt, "w");
		for (int i = 1; i <= 18; i++) {
			divide--;
			divide = divide / i;
		}
		printf("\r%lld", divide);
		number_of_operations++;
	}
	fclose(save_data);
	printf("\r");
	printf("Memory access score   %f\n",
	       (float)(number_of_operations / (RUN_TIME / 100) / 7.58));

	/* Exit */
	if (remove(bench_txt)) {
		fprintf(stderr, "ERROR: File %s not removed!\n", bench_txt);
	}
	pthread_detach(threads[0]);
	pthread_join(threads[0], NULL);
	return 0;
}

void *threadTimeCount(void *v)
{
	clock_t start = clock();
	while ((clock() - start) * 1000 / CLOCKS_PER_SEC < RUN_TIME) ;
	end = 1;
	return 0;
}
