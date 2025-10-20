#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // Number of philosophers

pthread_mutex_t forks[N];

void* philosopher(void* num) {
    int id = (int)num;

    while (1) {
        printf("Philosopher %d is thinking 💭\n", id);
        sleep(1);

        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[(id + 1) % N]);
            printf("Philosopher %d picked up right fork 🍴\n", id);

            pthread_mutex_lock(&forks[id]);
            printf("Philosopher %d picked up left fork 🍴 and starts eating 🍝\n", id);
        } else {
            pthread_mutex_lock(&forks[id]);
            printf("Philosopher %d picked up left fork 🍴\n", id);

            pthread_mutex_lock(&forks[(id + 1) % N]);
            printf("Philosopher %d picked up right fork 🍴 and starts eating 🍝\n", id);
        }

        sleep(2); // eating

        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % N]);
        printf("Philosopher %d put down both forks 💤\n", id);
    }
}

int main() {
    pthread_t thread_id[N];
    int philosopher_ids[N];

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&forks[i], NULL);

    for (int i = 0; i < N; i++) {
        philosopher_ids[i] = i;
        pthread_create(&thread_id[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    for (int i = 0; i < N; i++)
        pthread_mutex_destroy(&forks[i]);

    return 0;
}