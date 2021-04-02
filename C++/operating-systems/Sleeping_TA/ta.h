/**
 * Header file for sleeping TA
 */

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>


/* the maximum time (in seconds) to sleep */
#define MAX_SLEEP_TIME         5

/* number of maximum waiting students */
#define MAX_WAITING_STUDENTS   3

/* number of potential students */
#define NUM_OF_STUDENTS        5

/* number of available seats */
#define NUM_OF_SEATS           3


/* semaphores and mutex lock */
pthread_mutex_t mutexLock;

/* semaphore declarations */
sem_t students_sem;
sem_t ta_sem;

/* the number of waiting students */
int curWaiting;

/* student being served */
int curServed;

/* the numeric id of each student */
int studentID[NUM_OF_STUDENTS];

/* student function prototype */
void *student_loop(void*);
void help_student(int);
void hang_out(int, int);

/* ta function prototype */
void *ta_loop(void*);




