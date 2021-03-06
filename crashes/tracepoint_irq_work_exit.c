/* tracepoint_irq_work_exit.c				*/
/* by Vince Weaver <vincent.weaver _at_ maine.edu	*/

/* generated by the perf_fuzzer				*/

/* crashes 3.12 at least				*/
/* you may have to run it multiple times		*/

#define _GNU_SOURCE 1
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <sys/prctl.h>
#include <poll.h>
#include <linux/hw_breakpoint.h>
#include <linux/perf_event.h>


int fd[1024];
struct perf_event_attr pe[1024];
char *mmap_result[1024];
#define MAX_READ_SIZE 65536

#define MAX_POLL_FDS 128
struct pollfd pollfds[MAX_POLL_FDS];

long long id;

int forked_pid;

struct sigaction sa;
static int overflows=0;
static int sigios=0;

int perf_event_open(struct perf_event_attr *hw_event_uptr,
	pid_t pid, int cpu, int group_fd, unsigned long flags) {

	return syscall(__NR_perf_event_open,hw_event_uptr, pid, cpu,
		group_fd, flags);
}

static void our_handler(int signum, siginfo_t *info, void *uc) {
	int fd = info->si_fd;

	overflows++;
	ioctl(fd,PERF_EVENT_IOC_DISABLE,0);
	if (sigios) return;
	ioctl(fd, PERF_EVENT_IOC_REFRESH,1);
}


int main(int argc, char **argv) {
/* 1 */
/* fd = 82 */

	memset(&pe[82],0,sizeof(struct perf_event_attr));
	pe[82].type=PERF_TYPE_TRACEPOINT;
	pe[82].size=80;

	/* irq_vectors/irq_work_exit/id:24 */
	pe[82].config=0x18;

	pe[82].sample_period=0xdd95cac7b947b610;
	pe[82].sample_type=PERF_SAMPLE_IP|PERF_SAMPLE_TIME|PERF_SAMPLE_READ|PERF_SAMPLE_CALLCHAIN|PERF_SAMPLE_PERIOD|PERF_SAMPLE_DATA_SRC;
//|PERF_SAMPLE_IDENTIFIER; /* 18135 */
	pe[82].read_format=PERF_FORMAT_TOTAL_TIME_ENABLED|PERF_FORMAT_TOTAL_TIME_RUNNING|PERF_FORMAT_ID|PERF_FORMAT_GROUP; /* f */
	pe[82].exclude_hv=1;
	pe[82].mmap=1;
	pe[82].comm=1;
	pe[82].watermark=1;
	pe[82].precise_ip=1; /* constant skid */
	pe[82].mmap_data=1;
	pe[82].exclude_host=1;
	pe[82].exclude_guest=1;
	pe[82].exclude_callchain_user=1;
	pe[82].wakeup_watermark=232;
	pe[82].bp_type=HW_BREAKPOINT_EMPTY;
	pe[82].config1=0x9;
	pe[82].branch_sample_type=PERF_SAMPLE_BRANCH_USER|PERF_SAMPLE_BRANCH_KERNEL|PERF_SAMPLE_BRANCH_HV|PERF_SAMPLE_BRANCH_ANY|PERF_SAMPLE_BRANCH_ANY_CALL|PERF_SAMPLE_BRANCH_ANY_RETURN|PERF_SAMPLE_BRANCH_IND_CALL;
//|PERF_SAMPLE_BRANCH_ABORT_TX;
	pe[82].sample_regs_user=39;
	pe[82].sample_stack_user=37552;

	fd[82]=perf_event_open(&pe[82],
				0, /* current thread */
				-1, /* all cpus */
				-1, /* New Group Leader */
				PERF_FLAG_FD_OUTPUT /*2*/ );


/* 2 */
	mmap_result[82]=mmap(NULL, 20480,PROT_READ|PROT_WRITE, MAP_SHARED,fd[82], 0);
/* 3 */
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = our_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction( SIGRTMIN+2, &sa, NULL) < 0) {
		printf("Error setting up signal handler\n");
	}
	fcntl(fd[82], F_SETFL, O_RDWR|O_NONBLOCK|O_ASYNC);
	fcntl(fd[82], F_SETSIG, SIGRTMIN+2);
	fcntl(fd[82], F_SETOWN,getpid());

	/* Replayed 3 syscalls */
	return 0;
}
