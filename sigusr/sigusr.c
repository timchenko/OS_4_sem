#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

void handler(int signum, siginfo_t* siginfo, void* context) {
    printf("SIGUSR%d from %d\n", (signum == SIGUSR1) ? 1 : 2, siginfo->si_pid);
    exit(0);
}

int main() {
    struct sigaction waiter;
    waiter.sa_sigaction = &handler;
    waiter.sa_flags = SA_SIGINFO;
    if (sigemptyset(&waiter.sa_mask) ||
        sigaddset(&waiter.sa_mask, SIGUSR1) ||
        sigaddset(&waiter.sa_mask, SIGUSR2)) {
      perror("Setting mask error!\n");
      return errno;
	}
    if (sigaction(SIGUSR1, &waiter, NULL) || 
        sigaction(SIGUSR2, &waiter, NULL)) {
      perror("Setting handler error!\n");
      return errno;
    }
    sleep(10);
    printf("No signals were caught\n");
    return 0;
}
