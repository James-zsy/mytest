#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


static void *print_a_plus_b_thread(void *arg);
static void *print_b_minus_a_thread(void *arg);
static void *modify_a_thread(void *arg);
static void *modify_b_thread(void *arg);

static int a = 0;
static int b = 0;
static pthread_mutex_t a_lock;
static pthread_mutex_t b_lock;


static void *print_a_plus_b_thread(void *arg)
{
    int val;
    while (1) {
        pthread_mutex_lock(&a_lock);
        val = a;
        pthread_mutex_unlock(&a_lock);

        pthread_mutex_lock(&b_lock);
        val += b;
        pthread_mutex_unlock(&b_lock);

        printf("a plus b ==> %d\n", val);
        sleep(1);
    }
    return NULL;
}

static void *print_b_minus_a_thread(void *arg)
{
    int val;
    while (1) {
        pthread_mutex_lock(&b_lock);
        val = b;
        pthread_mutex_unlock(&b_lock);

        pthread_mutex_lock(&a_lock);
        val -= a;
        pthread_mutex_unlock(&a_lock);

        printf("b minus a ==> %d\n", val);
        sleep(1);
    }
    return NULL;
}

static void *modify_a_thread(void *arg)
{
    while (1) {
        pthread_mutex_lock(&a_lock);
        a = rand() % 100;
        pthread_mutex_unlock(&a_lock);

        sleep(1);
    }
    return NULL;
}

static void *modify_b_thread(void *arg)
{
    while (1) {
        pthread_mutex_lock(&b_lock);
        b = rand() % 100;
        pthread_mutex_unlock(&b_lock);

        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int run_time = 0;
    pthread_t t1, t2, t3, t4;

    srand(time(NULL));

    pthread_create(&t1, NULL, modify_a_thread, NULL);
    pthread_create(&t2, NULL, modify_b_thread, NULL);
    pthread_create(&t3, NULL, print_a_plus_b_thread, NULL);
    pthread_create(&t4, NULL, print_b_minus_a_thread, NULL);

    while (run_time++ < 10) {
        sleep(1);
    }
    return 0;
}
