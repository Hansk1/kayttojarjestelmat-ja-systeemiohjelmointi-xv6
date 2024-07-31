#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "defs.h"


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//You can reset the counter with an argument (1 point), First argument is reset number. If the number is 1, then the selected counter is reseted.
//You can select between the number of different system call which to follow (1 point). Second argument is the SYS call number which call count we want. Now it supports only read and exit calls.
//NOTE: the syscall is called getreadycount, because I was in hurry and I didn't have to change the name of it.

int
sys_getreadcount(void){
  //Get the reset number:
  int resetNumber;
  argint(0, &resetNumber);

  //Get the wanted syscall counter number:
  int syscallnumber;
  argint(1, &syscallnumber);
  
  if(resetNumber == 1 && syscallnumber == 5) {
    globalreadcount = 0;
    return(globalreadcount);
  }
  
  if(resetNumber == 1 && syscallnumber == 2) {
      globalexitcount = 0;
      return(globalexitcount);
    }

  if(syscallnumber == 5) {
    return(globalreadcount);
  }
  
  if(syscallnumber == 2) {
      return(globalexitcount);
    }
  return(-1);

}