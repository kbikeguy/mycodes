/**
 * Simulate a student hanging out
 */

#include <stdio.h>
#include "ta.h"

//DONE
void hang_out(int lnumber, int sleep_time) 
{
   printf("\tStudent %d hanging out for %d seconds\n", lnumber, sleep_time);
      sleep(sleep_time);
}
