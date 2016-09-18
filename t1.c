/*
* Project 1 written by Timothy Hennessy
* 
* Description: Create 2 to 12 threads using
* pthreads library.
*
* Each thread will...
* -Odd thread tids compute factorial(tid)
* -Even thread tids compute sumation(tid)
*
* Each computation is referenced in main
* and summed together.
*
* Important steps:
* 1. Create/define thread references
* 2. Create thread entry point "sayhi"
* 3. Create threads
* 4. Join threads after they call pthread
*    exit.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Put in desired number of threads
#define NUM_THREADS    12

// Will not use computed[0] in order to have
// index start at 1
long computed[NUM_THREADS + 1] = {0};

long summation(long t)
{
    long sum = 0;
    long i;
    for (i = 1; i <= t; i++)
        sum += i;
    return sum;
}

long factorial(long t)
{
    long product = 1;
    long i;
    for (i = 1; i <= t; i++)
        product *= i;
    return product;
}

/*
* Description: Thread entry point. Determines
* if thread tid is odd or even and calls 
* factorial or summation, respectively.
*
* Function header complies with pthread
* library specification.
*
* Threads store returned values into
* global array called computed.
*
* Threads call pthread_exit.
*/
void *sayhi(void *param)
{
    long thread_id = (long) param;
    long result;

    if (thread_id % 2 == 0)
        result = summation(thread_id);
    else
        result = factorial(thread_id);
    computed[thread_id] = result;
    pthread_exit(NULL);
}

int main(void)
{
    if (NUM_THREADS < 2 || NUM_THREADS > 12)
    {
        printf("Must generate 2 to 12 threads\n");
        exit(1);
    }

    // Local variables
    int N = NUM_THREADS + 1;
    pthread_t tids[N];
    long t, sum = 0;
    void *status;

    // Welcome message
    printf("%d threads go to work!\n", NUM_THREADS);

    // Create threads
    for (t = 1; t < N; t++)
    {
        pthread_create(&tids[t], NULL, sayhi, (void *) t);
    }
        
    // Join threads
    for (t = 1; t < N; t++)
    {
        pthread_join(tids[t], &status);
    }
    
    // Resulting values
    printf("---------------------------------------\n");
    for (t = 1; t < N; t++)
    {
        printf("Thread %ld = %ld\n", t, computed[t]);
        sum += computed[t];
        printf("Current sum = %ld\n", sum);
    }
    printf("---------------------------------------\n");
    printf("Final sum = %ld\n\n", sum);

    return 0;
}
