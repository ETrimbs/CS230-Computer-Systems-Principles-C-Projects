#include "challenge.h"

// main function for non-test code
// This exists solely for the benefit of the students to test their own code
int main()
{
  struct Time time1 = create_time(10, 34, 15);
  struct Time time2 = create_time(23, 36, 20);

  struct Time time3 = elapsed_time(time1, time2);

  printf("\nDifference: %i h  %i min  %i sec\n\n", time3.hour, time3.min, time3.sec);

}
