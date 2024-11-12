// Server Program: server.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#define SHM_KEY 12345 // Key for shared memory
#define SHM_SIZE 1024 // Size of shared memory segment
int main() {
int shmid;
char *shm_ptr;
// Create a shared memory segment
shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
if (shmid == -1) {
perror("shmget failed");
exit(1);
}
// Attach the shared memory segment to the server's addressspace
shm_ptr = (char *) shmat(shmid, NULL, 0);
if (shm_ptr == (char *) -1) {
perror("shmat failed");
exit(1);
}
// Write a message to shared memory
printf("Writing to shared memory: Hello from Server!\n");
strcpy(shm_ptr, "Hello from Server!");
// Detach from the shared memory
shmdt(shm_ptr);
return 0;
}


/*client program */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#define SHM_KEY 12345 // Same key as in the server
#define SHM_SIZE 1024 // Size of shared memory segment
int main() {
int shmid;
char *shm_ptr;
// Locate the shared memory segment
shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
if (shmid == -1) {
perror("shmget failed");
exit(1);
}
// Attach to the shared memory segment
shm_ptr = (char *) shmat(shmid, NULL, 0);
if (shm_ptr == (char *) -1) {
perror("shmat failed");
exit(1);
}
// Read the message from shared memory
printf("Message from server: %s\n", shm_ptr);
// Detach from the shared memory
shmdt(shm_ptr);
return 0;
}
