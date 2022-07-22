#ifndef MISC_H
#define MISC_H

typedef int bool;

#define true 1
#define false 0

#define CHARNAME_MAX_LEN 100

int rand_between(int min, int max);
int min(int a, int b);
int max(int a, int b);
void get_user_input(char *);

#endif // MISC_H

