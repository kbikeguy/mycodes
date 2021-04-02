#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include "ta.h"

pthread_t ta;
pthread_t students[NUM_OF_STUDENTS];

/**
 * Initialize all relevant data structures and
 * synchronization objects.
 */
void init()
{
   curServed = 0;

   if (pthread_mutex_init(&mutexLock, NULL))
      printf("%s\n",strerror(errno));

   if (sem_init(&students_sem, 0, 0) == -1)
      printf("error init students_sem\n");

   if (sem_init(&ta_sem, 0, 0) == -1)
      printf("error init ta\n");

   for (int i = 0; i < NUM_OF_STUDENTS; i++)
      studentID[i] = i;
}

void create_students()
{
   for (int i = 0; i < NUM_OF_STUDENTS; i++)
      pthread_create(&students[i], 0, student_loop, (void*) &studentID[i]);
}

void create_ta()
{
   pthread_create(&ta, 0, ta_loop, 0);
}

int main(void)
{
   int i;

   init();
   create_ta();
   create_students();


   for (i = 0; i < NUM_OF_STUDENTS; i++)
      pthread_join(students[i], NULL);


   /* when all students have finished, we will cancel the TA thread */
   if (pthread_cancel(ta))
      printf("%s\n",strerror(errno));

   return 0;
}

