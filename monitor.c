#include <stdio.h>
#include <pthread.h>

#include "sync.h"

void init_monitor(Monitor *monitor) {
    monitor->index = 0;
    pthread_mutex_init(&monitor->mutex, NULL);
    pthread_cond_init(&monitor->can_produce, NULL);
    pthread_cond_init(&monitor->can_consume, NULL);
}

void destroy_monitor(Monitor *monitor) {
    pthread_mutex_destroy(&monitor->mutex);
    pthread_cond_destroy(&monitor->can_produce);
    pthread_cond_destroy(&monitor->can_consume);
}

void produce(Monitor *monitor, int item) {
    pthread_mutex_lock(&monitor->mutex);
    while (monitor->index >= BUFFER_SIZE) {
        pthread_cond_wait(&monitor->can_produce, &monitor->mutex);
    }
    monitor->buffer[monitor->index++] = item;
    printf("Produced: %d\n", item);
    pthread_cond_signal(&monitor->can_consume);
    pthread_mutex_unlock(&monitor->mutex);
}

int consume(Monitor *monitor) {
    pthread_mutex_lock(&monitor->mutex);
    while (monitor->index <= 0) {
        pthread_cond_wait(&monitor->can_consume, &monitor->mutex);
    }
    int item = monitor->buffer[--monitor->index];
    printf("Consumed: %d\n", item);
    pthread_cond_signal(&monitor->can_produce);
    pthread_mutex_unlock(&monitor->mutex);
    return item;
}

