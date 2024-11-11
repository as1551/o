#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define MAX 5 
int buffer[MAX]; 
int in = 0, out = 0; 
sem_t empty; 
sem_t full; 
sem_t mutex; 
void* producer(void* arg) {
int item;
while (1) {

item = rand() % 100;
printf("Produced: %d\n", item);

sem_wait(&empty);

sem_wait(&mutex);

buffer[in] = item;
in = (in + 1) % MAX;

sem_post(&mutex);

sem_post(&full);
sleep(1); 
}
return NULL;
}
void* consumer(void* arg) {
int item;
while (1) {

sem_wait(&full);

sem_wait(&mutex);

item = buffer[out];
out = (out + 1) % MAX;

sem_post(&mutex);

sem_post(&empty);
printf("Consumed: %d\n", item);
sleep(1); 
}
return NULL;
}
int main() {
pthread_t prod_thread, cons_thread;

sem_init(&empty, 0, MAX); // MAX empty slots
sem_init(&full, 0, 0); // 0 full slots
sem_init(&mutex, 0, 1); // 1 mutex

pthread_create(&prod_thread, NULL, producer, NULL);
pthread_create(&cons_thread, NULL, consumer, NULL);

pthread_join(prod_thread, NULL);
pthread_join(cons_thread, NULL);

sem_destroy(&empty);
sem_destroy(&full);
sem_destroy(&mutex);
return 0;
}
