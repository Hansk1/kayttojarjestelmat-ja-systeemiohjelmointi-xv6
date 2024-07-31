//User program to test the readcount system call:
#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int readcount = getreadcount(0, 5);
    printf(1, "%d", readcount);
    exit();    
};