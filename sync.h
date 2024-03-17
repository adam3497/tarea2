#ifndef sync_h
#define sync_h

#define BUFFER_SIZE 10 // Definimos el tamaño máximo del buffer

// Estructura para el monitor
typedef struct {
    int buffer[BUFFER_SIZE]; // Buffer para almacenar los datos
    int count; // Contador de elementos en el buffer
    int in; // Índice de inserción en el buffer
    int out; // Índice de extracción del buffer
    pthread_mutex_t mutex; // Mutex para garantizar la exclusión mutua
    pthread_cond_t not_full; // Variable de condición para señalar cuando el buffer no está lleno
    pthread_cond_t not_empty; // Variable de condición para señalar cuando el buffer no está vacío
} Monitor;

// Funciones para el monitor
void monitor_init(Monitor *mon); // Inicializa el monitor
void produce(Monitor *mon, int data); // Función para que el productor produzca datos y los inserte en el buffer
int consume(Monitor *mon); // Función para que el consumidor extraiga datos del buffer


#endif