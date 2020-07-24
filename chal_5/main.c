#include "challenge.h"

// main function for non-test code
// This exists solely for the benefit of the students to test their own code
int main()
{
  struct Cred* a = cred("x", "y", NULL);
  struct Cred* b = cred("z", "p", NULL);
  set_next(a, b);

  cred_free(a);

  printf("\n%c\n", get_password(get_next(a))[0]);

}
