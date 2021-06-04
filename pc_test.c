/********************************************
 ********************************************
 ***                                      ***
 ***    NAME:    PC performance test      ***
 ***    VERSION: 0.0.3                    ***
 ***    AUTHOR:  MAROUSEK S.              ***
 ***    DATE:    2021/5/30                ***
 ***                                      ***
 ********************************************
 ********************************************/

/******************************************************************************
 *                                                                            *
 * Info:                                                                      *
 *                                                                            *
 *    compile:          'make'   (or 'gcc pc_test.c -lpthread -o0 -o test')   *
 *    execute:          './test'                                              *
 *    remove binary:    'make clean'                                          *
 *                                                                            *
 ******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define RUN_TIME 10000		// ms

void *threadTimeCount(void *);
void *thread1(void *);
void *thread2(void *);
void *thread3(void *);
void *thread4(void *);

_Bool thread1c;
long long number_of_operations1 = 0;
_Bool thread2c;
long long number_of_operations2 = 0;
_Bool thread3c;
long long number_of_operations3 = 0;
_Bool thread4c;
long long number_of_operations4 = 0;

long long number_of_operations = 0;
_Bool end = 0;

int main(int argc, char *argv[])
{
	FILE *save_data;
	void *(*thr_function[])(void *) =
	    { threadTimeCount, thread1, thread2, thread3, thread4 };
	pthread_t threads[5];
	for (int i = 0; i < 5; i++) {
		pthread_create(&threads[i], NULL, thr_function[i], NULL);
	}

	char *bench_txt = "pc_test_bench.txt";

	/* Test computation speed */
	long long divide;
	while (!end) {
		divide = 1 + number_of_operations;
		for (int i = 1; i <= 18; i++) {
			divide = divide * i;
			divide++;
		}
		for (int i = 1; i <= 18; i++) {
			divide--;
			divide = divide / i;
		}
		number_of_operations++;
	}
	printf("\r%lld", divide);
	while (thread1c || thread2c || thread3c || thread4c) {
	}

	printf("\r");
	if (argc > 1) {
		printf
		    ("Number0:  %lld\nNumber1:  %lld\nNumber2:  %lld\nNumber3:  %lld\nNumber4:  %lld\n",
		     number_of_operations, number_of_operations1,
		     number_of_operations2, number_of_operations3,
		     number_of_operations4);
	}

	number_of_operations =
	    number_of_operations + number_of_operations1 +
	    number_of_operations2 + number_of_operations3 +
	    number_of_operations4;

	printf("Computation score     %f\n",
	       (float)(number_of_operations / RUN_TIME / 18.81));
	for (int i = 0; i < 5; i++) {
		pthread_detach(threads[i]);
		pthread_join(threads[i], NULL);
	}

	save_data = fopen(bench_txt, "w");

	/* Test memory access speed */
	pthread_create(&threads[0], NULL, thr_function[0], NULL);
	number_of_operations = 0;
	end = 0;
	long long file_out;
	while (!end) {
		divide = 1 + number_of_operations;
		for (int i = 1; i <= 18; i++) {
			divide = divide * i;
			divide++;
		}
		fprintf(save_data, "%lld\n", divide);
		fclose(save_data);
		save_data = fopen(bench_txt, "r");
		fscanf(save_data, "%lld", &file_out);
		fclose(save_data);
		save_data = fopen(bench_txt, "w");
		for (int i = 1; i <= 18; i++) {
			divide--;
			divide = divide / i;
		}
		number_of_operations++;
	}
	fclose(save_data);
	printf("\r%lld", divide);
	printf("\r");
	printf("Memory access score   %f\n",
	       ((float)number_of_operations / (RUN_TIME / 100) / 5));

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
	thread1c = thread2c = thread3c = thread4c = 0;
	return 0;
}

long long computationThread(long long number_o_o, _Bool *threadC)
{
	long long divide;
	while (*threadC) {
		divide = 1 + number_o_o;
		for (int i = 1; i <= 18; i++) {
			divide = divide * i;
			divide++;
		}
		for (int i = 1; i <= 18; i++) {
			divide--;
			divide = divide / i;
		}
		number_o_o++;
	}
	return number_o_o;
}

void *thread1(void *v)
{
	thread1c = 1;
	long long number_of_operations11 = computationThread(0, &thread1c);
	number_of_operations1 = number_of_operations11;
	printf("\r%lld", number_of_operations11);
	return 0;
}

void *thread2(void *v)
{
	thread2c = 1;
	long long number_of_operations22 = computationThread(0, &thread2c);
	number_of_operations2 = number_of_operations22;
	printf("\r%lld", number_of_operations22);
	return 0;
}

void *thread3(void *v)
{
	thread3c = 1;
	long long number_of_operations33 = computationThread(0, &thread3c);
	number_of_operations3 = number_of_operations33;
	printf("\r%lld", number_of_operations33);
	return 0;
}

void *thread4(void *v)
{
	thread4c = 1;
	long long number_of_operations44 = computationThread(0, &thread4c);
	number_of_operations4 = number_of_operations44;
	printf("\r%lld", number_of_operations44);
	return 0;
}
