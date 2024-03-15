#include <pthread.h>

#include "sync.h"

void* producer(void *arg) {
    Monitor *monitor = (Monitor *) arg;
    for (int i = 0; i < 20; i++) {
        produce(monitor, i);
    }
    return NULL;
}

void* consumer(void *arg) {
    Monitor *monitor = (Monitor *) arg;
    for (int i = 0; i < 20; i++) {
        consume(monitor);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    Monitor monitor;

    init_monitor(&monitor);

    pthread_create(&producer_thread, NULL, producer, &monitor);
    pthread_create(&consumer_thread, NULL, consumer, &monitor);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    destroy_monitor(&monitor);

    return 0;
}
