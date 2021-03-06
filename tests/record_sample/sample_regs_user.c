/* sample_regs_user.c  */
/* by Vince Weaver   vincent.weaver _at_ maine.edu */

/* An attempt to figure out the PERF_SAMPLE_REGS_USER code */

#define _GNU_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

#include <errno.h>

#include <signal.h>
#include <sys/mman.h>

#include <sys/ioctl.h>
#include <asm/unistd.h>
#include <sys/prctl.h>

#include "perf_event.h"
#include "test_utils.h"
#include "perf_helpers.h"
#include "instructions_testcode.h"
#include "parse_record.h"

#include "asm/perf_regs.h"



#define SAMPLE_FREQUENCY 100000

#define MMAP_DATA_SIZE 8

static int count_total=0;
static char *our_mmap;
static long long prev_head;
static int quiet;
static long long global_sample_type;
static long long global_sample_regs_user;

static void our_handler(int signum, siginfo_t *info, void *uc) {

	int ret;

	int fd = info->si_fd;

	ret=ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);

	prev_head=perf_mmap_read(our_mmap,MMAP_DATA_SIZE,prev_head,
		global_sample_type,0,global_sample_regs_user,
		NULL,quiet,NULL);

	count_total++;

	ret=ioctl(fd, PERF_EVENT_IOC_REFRESH, 1);

	(void) ret;

}


int main(int argc, char **argv) {

	int ret;
	int fd;
	int mmap_pages=1+MMAP_DATA_SIZE;

	struct perf_event_attr pe;

	struct sigaction sa;
	char test_string[]="Testing PERF_SAMPLE_REGS_USER...";

	quiet=test_quiet();

	if (!quiet) printf("This tests PERF_SAMPLE_REGS_USER samples\n");

	        memset(&sa, 0, sizeof(struct sigaction));
        sa.sa_sigaction = our_handler;
        sa.sa_flags = SA_SIGINFO;

        if (sigaction( SIGIO, &sa, NULL) < 0) {
                fprintf(stderr,"Error setting up signal handler\n");
                exit(1);
        }

        /* Set up Instruction Event */

        memset(&pe,0,sizeof(struct perf_event_attr));

        pe.type=PERF_TYPE_HARDWARE;
        pe.size=sizeof(struct perf_event_attr);
        pe.config=PERF_COUNT_HW_INSTRUCTIONS;
        pe.sample_period=SAMPLE_FREQUENCY;
        pe.sample_type=PERF_SAMPLE_IP | PERF_SAMPLE_REGS_USER;

	global_sample_type=pe.sample_type;

#if defined (__x86_64__)


	/* Bitfield saying which registers we want */
	pe.sample_regs_user=(1ULL<<PERF_REG_X86_64_MAX)-1;
	/* DS, ES, FS, and GS not valid on x86_64 */
	/* see  perf_reg_validate() in arch/x86/kernel/perf_regs.c */
	pe.sample_regs_user&=~(1ULL<<PERF_REG_X86_DS);
	pe.sample_regs_user&=~(1ULL<<PERF_REG_X86_ES);
	pe.sample_regs_user&=~(1ULL<<PERF_REG_X86_FS);
	pe.sample_regs_user&=~(1ULL<<PERF_REG_X86_GS);


#elif defined(__i386__)

	pe.sample_regs_user=(1ULL<<PERF_REG_X86_32_MAX)-1;
#else
	pe.sample_regs_user=1;
#endif

	global_sample_regs_user=pe.sample_regs_user;

        pe.read_format=0;
        pe.disabled=1;
        pe.pinned=1;
        pe.exclude_kernel=1;
        pe.exclude_hv=1;
        pe.wakeup_events=1;

	arch_adjust_domain(&pe,quiet);

	fd=perf_event_open(&pe,0,-1,-1,0);
	if (fd<0) {
		if (!quiet) {
			fprintf(stderr,"Problem opening leader %s\n",
				strerror(errno));
			test_fail(test_string);
		}
	}
	our_mmap=mmap(NULL, mmap_pages*4096,
		PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	fcntl(fd, F_SETFL, O_RDWR|O_NONBLOCK|O_ASYNC);
	fcntl(fd, F_SETSIG, SIGIO);
	fcntl(fd, F_SETOWN,getpid());

	ioctl(fd, PERF_EVENT_IOC_RESET, 0);

	ret=ioctl(fd, PERF_EVENT_IOC_ENABLE,0);

	if (ret<0) {
		if (!quiet) {
			fprintf(stderr,"Error with PERF_EVENT_IOC_ENABLE "
				"of group leader: %d %s\n",
				errno,strerror(errno));
			exit(1);
		}
	}

	instructions_million();

	ret=ioctl(fd, PERF_EVENT_IOC_REFRESH,0);

	if (!quiet) {
                printf("Counts %d, using mmap buffer %p\n",count_total,our_mmap);
        }

	if (count_total==0) {
		if (!quiet) printf("No overflow events generated.\n");
		test_fail(test_string);
	}
	munmap(our_mmap,mmap_pages*4096);

	close(fd);

	test_pass(test_string);

	return 0;
}
