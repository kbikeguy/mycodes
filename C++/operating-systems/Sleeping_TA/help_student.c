/**
 * Simulate helping a student
 */

#include <stdio.h>
#include "ta.h"

//DONE
void help_student(int sleep_time)
{
   printf("Helping a student for %d seconds waiting students = %d\n", sleep_time, curWaiting);
   sleep(sleep_time);
}
