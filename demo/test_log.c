/**
*gcc -g -Wall -lpthread  async_log.h async_log.c test_log.c -o async -lrt
*/

#include "async_log.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


#define TEST_NUM 100
#define __DEBUG__ 1
#define debug_printf(format, ...) do {\
									if(__DEBUG__)\
										printf(format, ##__VA_ARGS__);\
								}while(0)

void *func(void *arg) {
	int id = (int)arg;
	int n = TEST_NUM/4;
	clock_t b,e;
	b = clock();
	while(n--){
		log_error("%d:%d-----------%d\n", 123, 456, id);
		log_trace("%s----------%d", "this is a test lofasdfsadfasg file", id);
		usleep(rand()%2000);
		log_debug("%d:%d----------%d\n", 89, 12378, id);
		log_warn("%s----------%d", "thfuck the hell tfasdfasdf log file", id);
	}
	e = clock();
	debug_printf("------%f\n",(double)(e-b)/CLOCKS_PER_SEC);
	return NULL;
}

int main() {
	log_init(3, LOG_TRACE);
	debug_printf("here\n");
	sleep(1);
	
	pthread_t pid[3];
	int i;
	for(i = 0; i< 3; i++) {
		pthread_create(&pid[i], NULL, func, (void *)i);
	}
	
	
	for(i = 0; i < 3; i++)
		pthread_join(pid[i], NULL);
	log_destroy();
	return 0;
}
