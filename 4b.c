#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
int read_count = 0; 
sem_t rw_mutex; 
sem_t read_count_mutex; 
void* reader(void* arg) {
while (1) {

sem_wait(&read_count_mutex);
read_count++;
if (read_count == 1) {
sem_wait(&rw_mutex); 
}
sem_post(&read_count_mutex);

printf("Reader %d is reading\n", *((int*)arg));

sem_wait(&read_count_mutex);
read_count--;
if (read_count == 0) {
sem_post(&rw_mutex); 
}
sem_post(&read_count_mutex);
sleep(1); 
}
return NULL;
}
void* writer(void* arg) {
while (1) {

sem_wait(&rw_mutex);

printf("Writer %d is writing\n", *((int*)arg));

sem_post(&rw_mutex);
sleep(1); 
}
return NULL;
}
int main() {
pthread_t readers[5], writers[2];
int reader_ids[5] = {1, 2, 3, 4, 5};
int writer_ids[2] = {1, 2};

sem_init(&rw_mutex, 0, 1); 
sem_init(&read_count_mutex, 0, 1); 

for (int i = 0; i < 5; i++) {
pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
}
for (int i = 0; i < 2; i++) {
pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
}

for (int i = 0; i < 5; i++) {
pthread_join(readers[i], NULL);
}
for (int i = 0; i < 2; i++) {
pthread_join(writers[i], NULL);
}

sem_destroy(&rw_mutex);
sem_destroy(&read_count_mutex);
return 0;
}
