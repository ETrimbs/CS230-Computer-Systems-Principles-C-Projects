#include "challenge.h"

// main function for non-test code
// This exists solely for the benefit of the students to test their own code


//Create a binary search tree structure and traverse on it.
//Implement two functions: build_tree and prep_print 
//You can use strcpy to copy string and strcat to concatenate string

int main()
{
  reset_print();
  puts("reset");
  build_tree();
  puts("build");
  prep_print(get_banana());
  puts("print prep");
  printf("%s", get_print_buf());


}
