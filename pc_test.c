/********************************************
 ********************************************
 ***                                      ***
 ***    NAME:    PC performance test      ***
 ***    VERSION: 0.0.2                    ***
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
 **************************************************************************/

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

_Bool thread1c = 0;
_Bool thread2c = 0;
_Bool thread3c = 0;
_Bool thread4c = 0;

long long number_of_operations1 = 0;
long long number_of_operations2 = 0;
long long number_of_operations3 = 0;
long long number_of_operations4 = 0;

long long number_of_operations = 0;
_Bool end = 0;

int main()
{
	FILE *save_data;
	void *(*thr_function[])(void *) = { threadTimeCount,thread1,thread2,thread3,thread4 };
	pthread_t threads[5];
	pthread_create(&threads[0], NULL, thr_function[0], NULL);
	pthread_create(&threads[1], NULL, thr_function[1], NULL);
	pthread_create(&threads[2], NULL, thr_function[2], NULL);
	pthread_create(&threads[3], NULL, thr_function[3], NULL);
	pthread_create(&threads[4], NULL, thr_function[4], NULL);
	thread1c = 1;
	thread2c = 1;
	thread3c = 1;
	thread4c = 1;

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
	while (thread1c || thread2c || thread3c || thread4c) {}

	printf("\r");
	/*printf("Number0:  %lld\n",number_of_operations);
	printf("Number1:  %lld\n",number_of_operations1);
	printf("Number2:  %lld\n",number_of_operations2);
	printf("Number3:  %lld\n",number_of_operations3);
	printf("Number4:  %lld\n",number_of_operations4);*/

	number_of_operations = number_of_operations + number_of_operations1 + number_of_operations2 + number_of_operations3 + number_of_operations4;

	printf("Computation score     %f\n",
	       (float)(number_of_operations / RUN_TIME / 18.81));
	pthread_detach(threads[0]);
	pthread_create(&threads[0], NULL, thr_function[0], NULL);

	pthread_detach(threads[1]);
	pthread_join(threads[1], NULL);
	pthread_detach(threads[2]);
	pthread_join(threads[2], NULL);
	pthread_detach(threads[3]);
	pthread_join(threads[3], NULL);
	pthread_detach(threads[4]);
	pthread_join(threads[4], NULL);

	save_data = fopen(bench_txt, "w");

	/* Test memory access speed */
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
	       (float)(number_of_operations / (RUN_TIME / 100) / 5));

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

void *thread1(void *v)
{
	long long number_of_operations11 = 0;
	long long divide;
	while (!end) {
		divide = 1 + number_of_operations11;
		for (int i = 1; i <= 18; i++) {
			divide = divide * i;
			divide++;
		}
		for (int i = 1; i <= 18; i++) {
			divide--;
			divide = divide / i;
		}
		number_of_operations11++;
	}
	thread1c = 0;
	number_of_operations1 = number_of_operations11;
	printf("\r%lld", divide);
	return 0;
}

void *thread2(void *v)
{
	long long number_of_operations22 = 0;
	long long divide;
	while (!end) {
		divide = 1 + number_of_operations22;
		for (int i = 1; i <= 18; i++) {
			divide = divide * i;
			divide++;
		}
		for (int i = 1; i <= 18; i++) {
			divide--;
			divide = divide / i;
		}
		number_of_operations22++;
	}
	thread2c = 0;
	number_of_operations2 = number_of_operations22;
	printf("\r%lld", divide);
	return 0;
}

void *thread3(void *v)
{
	long long number_of_operations33 = 0;
	long long divide;
	while (!end) {
		divide = 1 + number_of_operations33;
		for (int i = 1; i <= 18; i++) {
			divide = divide * i;
			divide++;
		}
		for (int i = 1; i <= 18; i++) {
			divide--;
			divide = divide / i;
		}
		number_of_operations33++;
	}
	thread3c = 0;
	number_of_operations3 = number_of_operations33;
	printf("\r%lld", divide);
	return 0;
}

void *thread4(void *v)
{
	long long number_of_operations44 = 0;
	long long divide;
	while (!end) {
		divide = 1 + number_of_operations44;
		for (int i = 1; i <= 18; i++) {
			divide = divide * i;
			divide++;
		}
		for (int i = 1; i <= 18; i++) {
			divide--;
			divide = divide / i;
		}
		number_of_operations44++;
	}
	thread4c = 0;
	number_of_operations4 = number_of_operations44;
	printf("\r%lld", divide);
	return 0;
}
