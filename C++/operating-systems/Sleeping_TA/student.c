/**
 * General structure of a student.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "ta.h"

void *student_loop(void *param)
{
   /* varaibles */
   int times_through_loop = 0;

   int id = *((int*)param);
   srandom((unsigned)time(NULL));

   hang_out(id, rand() % MAX_SLEEP_TIME);

   while (times_through_loop < 5) {

      /* acquire the mutex lock */
      if (pthread_mutex_lock(&mutexLock))
         printf("StudentA %s\n",strerror(errno));

      /* is there a seat available */
      if (curWaiting < NUM_OF_SEATS) {

         printf("\t\tStudent %d takes a seat waiting = %d\n",
              id, ++curWaiting);

         if (sem_post(&students_sem))
             printf("StudentB %s\n",strerror(errno));

         curServed = id;

         if (pthread_mutex_unlock(&mutexLock))
             printf("StudentC %s\n",strerror(errno));

         if (sem_wait(&ta_sem))
             printf("StudentD %s\n",strerror(errno));

         printf("Student %d receiving help\n", id);

       }
       else {
          printf("\t\t\tStudent %d will try later\n", id);
          pthread_mutex_unlock(&mutexLock);
          hang_out(id, rand() % MAX_SLEEP_TIME);
       }
       times_through_loop++;
   }
}

