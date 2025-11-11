#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define PRODUCE_COUNT 10

int pizzas = 0;
sem_t empty, full;
pthread_mutex_t lock;

void *producer(void *arg)
{
    for (int i = 0; i < PRODUCE_COUNT; i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&lock);

        pizzas++;
        printf("Simpson baked pizza 🍕 | Pizzas on counter = %d\n", pizzas);
        fflush(stdout);

        pthread_mutex_unlock(&lock);
        sem_post(&full);
        sleep(1);
    }

    printf("Simpson done baking! 🧑‍🍳\n");
    fflush(stdout);
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    for (int i = 0; i < PRODUCE_COUNT; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&lock);

        pizzas--;
        printf("Joey ate pizza 😋 | Pizzas left = %d\n", pizzas);
        fflush(stdout);

        pthread_mutex_unlock(&lock);
        sem_post(&empty);
        sleep(2);
    }

    printf("Joey is full now! 😴\n");
    fflush(stdout);
    pthread_exit(NULL);
}

int main()
{
    pthread_t simpson, joey;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&lock, NULL);

    pthread_create(&simpson, NULL, producer, NULL);
    pthread_create(&joey, NULL, consumer, NULL);

    pthread_join(simpson, NULL);
    pthread_join(joey, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);

    printf("\nAll threads finished. Resources cleaned up successfully ✅\n");
    fflush(stdout);

    return 0;
}