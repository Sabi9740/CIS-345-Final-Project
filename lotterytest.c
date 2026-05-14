#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#include "user/user.h"

void
busywork(void)

{

volatile int i;
for(i = 0; i <100000000; i++) {
}
}

int 
main(int argc, char *argv[])
{

int tickets[3] = {30, 20, 10};
int pids[3];

for(int i = 0; i < 3; i++) {
int pid = fork();

if(pid == 0) {
settickets (tickets[i]);
while(1) {
busywork();
}
exit(0);
} else{
pids[i] = pid;

}
}
for(volatile int x = 0; x < 500000000; x++) {
}


struct pstat ps;
getpinfo(&ps);

printf("Lottery Scheduler Test\n");
printf("Ticket ratio: 30:20:10\n");
printf("PID\tTickets\tTicks\n");

for(int i = 0; i < NPROC; i++) {
if(ps.inuse[i]) {
for(int j = 0; j < 3; j++){
if(ps.pid[i] == pids[j]) {

printf("%d\t%d\t%d\n", 
ps.pid[i],
ps.tickets[i],
ps.ticks[i]);
}
}
}
}
for (int i = 0; i < 3; i++) {
kill(pids[i]);
}
for(int i = 0; i < 3; i++) {
wait(0);
}
exit(0);
}
