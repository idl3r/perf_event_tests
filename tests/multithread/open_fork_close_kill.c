/* Try to track un-debuggable problem */

/* by Vince Weaver   vincent.weaver@maine.edu */

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

static char test_string[]="Testing open/fork/close/kill...";
static int quiet;


int main(int argc, char** argv) {

	int fd2,pid;

	struct perf_event_attr pe;

	quiet=test_quiet();

	if (!quiet) {
		printf("Testing open/fork/close/kill %d.\n",getpid());
		sleep(5);
	}

	/* Create software event */
	memset(&pe,0,sizeof(struct perf_event_attr));
	pe.type=PERF_TYPE_SOFTWARE;
	pe.size=sizeof(struct perf_event_attr);
	pe.config=PERF_COUNT_SW_TASK_CLOCK;
	pe.disabled=0;
	pe.exclude_kernel=1;
	pe.exclude_hv=1;
	arch_adjust_domain(&pe,quiet);

	fd2=perf_event_open(&pe,0,-1,-1,0);
	if (fd2<0) {
		fprintf(stderr,"Unexpected error %s\n",strerror(errno));
		test_fail(test_string);
	}

	pid=fork();

	if (pid==0) {
		/* child */
		while(1);
	}


	printf("Child %d\n",pid);

	sleep(5);

	close(fd2);

	sleep(1);

	kill(pid,9);

	sleep(1);

	test_pass(test_string);

	return 0;
}

