#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

// semaphore signal (V)
void sem_signal(int semid) {
    struct sembuf op = {0, 1, 0};
    semop(semid, &op, 1);
}

int main() {
    key_t key = ftok(".", 75);

    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    int semid = semget(key, 1, 0666 | IPC_CREAT);

    semctl(semid, 0, SETVAL, 0); // initialize to 0

    char *msg = shmat(shmid, NULL, 0);

    printf("Server: Enter message: ");
    fgets(msg, 100, stdin);

    sem_signal(semid);  // Signal client that data is ready
    printf("Server: Data written to shared memory.\n");

    shmdt(msg);
    return 0;
}