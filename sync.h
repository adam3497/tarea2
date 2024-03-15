#ifndef sync_h
#define sync_h

#include <pthread.h>

#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int index;
    pthread_mutex_t mutex;
    pthread_cond_t can_produce;
    pthread_cond_t can_consume;
} Monitor;

void init_monitor(Monitor *monitor);
void destroy_monitor(Monitor *monitor);
void produce(Monitor *monitor, int item);
int consume(Monitor *monitor);

#endif