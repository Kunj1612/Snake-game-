#include <stdio.h>
#include <pthread.h>
#include<unistd.h>

#define SIZE 5

int buffer[SIZE];
int count = 0;

pthread_mutex_t mutex;

void* producer(void* arg) {
    int i = 0;  

    while (1) {

        while (1) {
            pthread_mutex_lock(&mutex);

            if (count < SIZE) {
                buffer[count++] = (i + 1) % 5;
                printf("Produced: %d\n", i);
                i = (i + 1) % 5;  

                pthread_mutex_unlock(&mutex);
                break;
            }

            pthread_mutex_unlock(&mutex);
        }

    }
    return NULL;
}

void* consumer(void* arg) {

    while (1) {

        while (1) {
            pthread_mutex_lock(&mutex);

            if (count > 0) {
                int item = buffer[--count];
                printf("Consumed: %d\n", item);

                pthread_mutex_unlock(&mutex);
                break;
            }

            pthread_mutex_unlock(&mutex);
        }
    }


    return NULL;
}

int main() {
    pthread_t prod, cons;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}