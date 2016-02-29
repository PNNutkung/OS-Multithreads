/**
 * Main application class, entry point of the program.
 *
 * Authors: Phasin, the pink panty. Group
 *          Pipatpol Tanavongchinda 5710546372
 *          Pakpon Jetapai 5710546381
 *          Thanawit Gerdpraserd 5710547182
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 3

int* nums;
int ans[3];

int stoi(const char *s)
{
    int i;
    int mult = 1;
    i = 0;
    mult = s[0] == '-' ? -1 : 1;
    s = s[0] == '-' ? s + 1 : s;
    while(*s >= '0' && *s <= '9')
    {
        i = i * 10 + (mult * (*s - '0'));
        s++;
    }
    return i;
}

void* findMax(void* numbers){
    int max,i;
    long num;

    num = (long) numbers;
    for(i = 0;i < num;i++){
        if(i == 0||max < nums[i]){
            max = nums[i];
        }
    }
    ans[0] = max;
    pthread_exit(NULL);
}

void* findMin(void * numbers){
    int min, i;
    long num;

    num = (long) numbers;
    for(i = 0; i < num; i++){
        if(i == 0||min > nums[i]){
            min = nums[i];
        }
    }
    ans[1] = min;
    pthread_exit(NULL);
}

void* findMean(void* numbers){
    int sum,i;
    long num;

    num = (long) numbers;
    for(i = 0;i < num;i++){
        sum += nums[i];
    }
    ans[2] = (sum*1.0)/(num*1.0);
    pthread_exit(NULL);
}

int main(int argc, char const* argv[]){
    int n = argc - 1;
    pthread_t threads[NUM_THREADS];
    long taskids[NUM_THREADS];
    long maxround[1];
    int i = 0, rc, rc1, rc2, input;

    nums = (int*) calloc(n, sizeof(int));

    for (i = 1; i < argc; i++) {
        nums[i - 1] = stoi(argv[i]);
    }

    maxround[0] = n;
    printf("In main: creating thread 0\n");
    rc = pthread_create(&threads[0], NULL, findMax, (void *)maxround[0]);
    if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
     }

    printf("In main: creating thread 1\n");
    rc1 = pthread_create(&threads[1], NULL, findMin,(void *)maxround[0]);
    if (rc1) {
        printf("ERROR; return code from pthread_create() is %d\n", rc1);
        exit(-1);
    }

    printf("In main: creating thread 2\n");
    rc2 = pthread_create(&threads[2], NULL, findMean,(void *)maxround[0]);
    if (rc2) {
        printf("ERROR; return code from pthread_create() is %d\n", rc2);
        exit(-1);
     }
     int ppp;
     for ( ppp = 0; ppp < 2; ppp++)
       pthread_join(threads[ppp], NULL);
    printf("Min: %d\n", ans[1]);
    printf("Max: %d\n", ans[0]);
    printf("Average: %d\n", ans[2]);
    pthread_exit(NULL);
}
