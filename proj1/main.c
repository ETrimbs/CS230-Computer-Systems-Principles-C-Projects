#include "challenge.h"

// main function for non-test code
// This exists solely for the benefit of the students to test their own code
int main(void)
{
	int N = 3;
	int arr[5] = { 0,1,2,3,4 };
	int scale = 5;

	scale(N, arr, scale);


	int N2 = 3;
	int arr2[3][3] = {
		{1,2,3},
		{5,6,7},
		{10,9,8}
	};
	int flat[9];

	flatten(N2, arr2, flat);


}
