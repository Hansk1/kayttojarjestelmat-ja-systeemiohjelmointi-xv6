//User program to test the syscallcount system call (NOTE: the syscall is called getreadycount, because I was in hurry and I didn't have to change the name of it):
#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int readcount = getreadcount(1, 2);
    printf(1, "%d", readcount);
    exit();    
};