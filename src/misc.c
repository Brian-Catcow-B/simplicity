#include "misc.h"
#include <stdlib.h>
#include <stdio.h>

int rand_between(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

int min(int a, int b) {
	return (a < b) ? a : b;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

void get_user_input(char *into) {
	scanf("%s", into);
}

