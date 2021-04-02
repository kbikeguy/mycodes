/**
 * test.c
 *
 * Test the implementation of the PID manager.
 *
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "pid.h"

#define NUM_THREADS 100
#define ITERATIONS   10
#define SLEEP         5

int in_use[PID_MAX + 1];
/**
 * mutex lock used when accessing data structure
 * to ensure there are no duplicate pid's in use.
 */
pthread_mutex_t test_mutex;

void *allocator(void *param)
{
   int i, pid;

   for (i = 0; i < ITERATIONS; i++) {
      /* sleep for a random period of time */
		sleep((int)(random() % SLEEP));

      /* allocate a pid */
      pid = allocate_pid();

      if (pid == -1)
         printf("No pid available\n");
      else {
         /* indicate in the in_use map the pid is in use */
         //lock mutex
         if(pthread_mutex_lock(&test_mutex))
            printf("%s\n", strerror(errno));

         //check for duplicate pid
         in_use[pid] ? printf("%d is a duplicate pid\n", pid) : (in_use[pid] = 1);

         printf("allocated %d\n", pid);

         if (pthread_mutex_unlock(&test_mutex))
            printf("%s\n",strerror(errno));
         /* sleep for a random period of time */
         sleep((int)(random() % SLEEP));

         // unlock mutex
        // if (pthread_mutex_unlock(&test_mutex))
        //    printf("%s\n",strerror(errno));

         /* release the pid */
         release_pid(pid);
         printf("released %d\n", pid);
         in_use[pid] = 0;

         // unlock mutex
        // if (pthread_mutex_unlock(&test_mutex))
          //  printf("%s\n",strerror(errno));
      }
   }
}

int main(void)
{
   int i;
   pthread_t tids[NUM_THREADS];
   memset(in_use, 0, PID_MAX + 4);
   /*
   for (i = 0; i <= PID_MAX; i++) {
      in_use[i] = 0;
   }*/

   /* allocate the pid map */
   if (allocate_map() == -1){
      printf("failed to allocate map\n");
      return -1;
   }

   srandom((unsigned)time(NULL));

   /* create the threads */
   for(i = 0; i < NUM_THREADS; i++){
      if(pthread_create(&tids[i], NULL, allocator, (void*)&i) != 0)
         return -1;
   }
   /* join the threads */
   for(i = 0; i < NUM_THREADS; i++)
      pthread_join(tids[i], NULL);

   /* test is finished */

   return 0;
}
