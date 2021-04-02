/**
 * A solution to the pid manager problem. 
 *
 */

#include "pid.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>

// Allocates the pid map.
int allocate_map(void)
{
   memset(pid_map, 0, sizeof(pid_map));

   int size = PID_MAX + 1;
   for(int i = 0; i < size; i++)
      if(pid_map[i])
         return -1;

   return 0;
}

// Allocates a pid
int allocate_pid(void)
{
   /* local variables */
   int size = PID_MAX + 1;
   int found = 0;

   /* acquire the mutex lock and warn if unable */
   if(pthread_mutex_lock(&mutex))
      printf("unable to lock\n");

   /* find the next available pid */
   for(int i = 0; i < size && !found; i++) {
      if(!pid_map[i]) {
         last = 1 + i + PID_MIN;
         pid_map[i] = 1;
         found = 1;
      }
   }
   /* release and warn if the mutex was not released */
   if(pthread_mutex_unlock(&mutex))
      printf("unable to unlock\n");

   return found ? last : -1;
}

// Releases a pid
void release_pid(int pid)
{
   /* acquire the mutex lock and warn if unable */
   if(pthread_mutex_lock(&mutex))
      printf("unable to lock\n");

   pid_map[pid - 1 - PID_MIN] = 0;

   /* release and warn if the mutex was not released  */
   if(pthread_mutex_unlock(&mutex))
      printf("unable to unlock\n");
}
