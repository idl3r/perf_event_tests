CC = gcc

CFLAGS = -Wall -g -I../include -I./include -I./trinity_files/include
LFLAGS = 

CFLAGS_X32 = -Wall -mx32 -g -I../include -I./include -I./trinity_files/include
LFLAGS_X32 = -mx32 -static

####

all:	perf_fuzzer replay_log log_to_code filter_log active_events

x32:	perf_fuzzer.x32 replay_log.x32 log_to_code filter_log active_events


###

fuzz_access.o:	fuzz_access.c fuzz_access.h
	$(CC) $(CFLAGS) -c fuzz_access.c

fuzz_access.x32.o:	fuzz_access.c fuzz_access.h
	$(CC) $(CFLAGS_X32) -o fuzz_access.x32.o -c fuzz_access.c
###

fuzz_fork.o:	fuzz_fork.c fuzz_fork.h
	$(CC) $(CFLAGS) -c fuzz_fork.c

fuzz_fork.x32.o:	fuzz_fork.c fuzz_fork.h
	$(CC) $(CFLAGS_X32) -o fuzz_fork.x32.o -c fuzz_fork.c

###

fuzz_ioctl.o:	fuzz_ioctl.c fuzz_ioctl.h
	$(CC) $(CFLAGS) -c fuzz_ioctl.c

fuzz_ioctl.x32.o:	fuzz_ioctl.c fuzz_ioctl.h
	$(CC) $(CFLAGS_X32) -o fuzz_ioctl.x32.o -c fuzz_ioctl.c

###

fuzz_million.o:	fuzz_million.c fuzz_million.h
	$(CC) $(CFLAGS) -c fuzz_million.c

fuzz_million.x32.o:	fuzz_million.c fuzz_million.h
	$(CC) $(CFLAGS_X32) -o fuzz_million.x32.o -c fuzz_million.c

###

fuzz_mmap.o:	fuzz_mmap.c fuzz_mmap.h
	$(CC) $(CFLAGS) -c fuzz_mmap.c

fuzz_mmap.x32.o:	fuzz_mmap.c fuzz_mmap.h
	$(CC) $(CFLAGS_X32) -o fuzz_mmap.x32.o -c fuzz_mmap.c

###

fuzz_open.o:	fuzz_open.c fuzz_open.h
	$(CC) $(CFLAGS) -c fuzz_open.c

fuzz_open.x32.o:	fuzz_open.c fuzz_open.h
	$(CC) $(CFLAGS_X32) -o fuzz_open.x32.o -c fuzz_open.c

###

fuzz_overflow.o:	fuzz_overflow.c fuzz_overflow.h
	$(CC) $(CFLAGS) -c fuzz_overflow.c

fuzz_overflow.x32.o:	fuzz_overflow.c fuzz_overflow.h
	$(CC) $(CFLAGS_X32) -o fuzz_overflow.x32.o -c fuzz_overflow.c

###

fuzz_poll.o:	fuzz_poll.c fuzz_poll.h
	$(CC) $(CFLAGS) -c fuzz_poll.c

fuzz_poll.x32.o:	fuzz_poll.c fuzz_poll.h
	$(CC) $(CFLAGS_X32) -o fuzz_poll.x32.o -c fuzz_poll.c

###

fuzz_prctl.o:	fuzz_prctl.c fuzz_prctl.h
	$(CC) $(CFLAGS) -c fuzz_prctl.c

fuzz_prctl.x32.o:	fuzz_prctl.c fuzz_prctl.h
	$(CC) $(CFLAGS_X32) -o fuzz_prctl.x32.o -c fuzz_prctl.c

###

fuzz_read.o:	fuzz_read.c fuzz_read.h
	$(CC) $(CFLAGS) -c fuzz_read.c

fuzz_read.x32.o:	fuzz_read.c fuzz_read.h
	$(CC) $(CFLAGS_X32) -o fuzz_read.x32.o -c fuzz_read.c

###

fuzz_write.o:	fuzz_write.c fuzz_write.h
	$(CC) $(CFLAGS) -c fuzz_write.c

fuzz_write.x32.o:	fuzz_write.c fuzz_write.h
	$(CC) $(CFLAGS_X32) -o fuzz_write.x32.o -c fuzz_write.c


###

fuzzer_random.o:	fuzzer_random.c fuzzer_random.h
	$(CC) $(CFLAGS) -c fuzzer_random.c

fuzzer_random.x32.o:	fuzzer_random.c fuzzer_random.h
	$(CC) $(CFLAGS_X32) -o fuzzer_random.x32.o -c fuzzer_random.c

###

fuzzer_stats.o:	fuzzer_stats.c fuzzer_stats.h
	$(CC) $(CFLAGS) -c fuzzer_stats.c

fuzzer_stats.x32.o:	fuzzer_stats.c fuzzer_stats.h
	$(CC) $(CFLAGS_X32) -o fuzzer_stats.x32.o -c fuzzer_stats.c

###

perf_attr_print.o:	perf_attr_print.c perf_attr_print.h
	$(CC) $(CFLAGS) -c perf_attr_print.c

perf_attr_print.x32.o:	perf_attr_print.c perf_attr_print.h
	$(CC) $(CFLAGS_X32) -o perf_attr_print.x32.o -c perf_attr_print.c

###

get_cpuinfo.o:	get_cpuinfo.c get_cpuinfo.h
	$(CC) $(CFLAGS) -c get_cpuinfo.c

get_cpuinfo.x32.o:	get_cpuinfo.c get_cpuinfo.h
	$(CC) $(CFLAGS_X32) -o get_cpuinfo.x32.o -c get_cpuinfo.c

###

filter_log:	filter_log.o
	$(CC) $(LFLAGS) -o filter_log filter_log.o

filter_log.o:	filter_log.c
	$(CC) $(CFLAGS) -c filter_log.c

###

replay_log:	replay_log.o \
		../lib/perf_helpers.o perf_attr_print.o \
		trinity_files/trinity_lib.a
	$(CC) $(LFLAGS) -o replay_log replay_log.o ../lib/perf_helpers.o perf_attr_print.o trinity_files/trinity_lib.a

replay_log.o:	replay_log.c perf_attr_print.h
	$(CC) $(CFLAGS) -c replay_log.c

replay_log.x32:	replay_log.x32.o \
		../lib/perf_helpers.x32.o perf_attr_print.x32.o \
		trinity_files/trinity_lib.x32.a
	$(CC) $(LFLAGS_X32) -o replay_log.x32 replay_log.x32.o ../lib/perf_helpers.x32.o perf_attr_print.x32.o trinity_files/trinity_lib.x32.a

replay_log.x32.o:	replay_log.c perf_attr_print.h
	$(CC) $(CFLAGS_X32) -o replay_log.x32.o -c replay_log.c

###

active_events:	active_events.o \
		../lib/perf_helpers.o perf_attr_print.o
	$(CC) $(LFLAGS) -o active_events active_events.o ../lib/perf_helpers.o perf_attr_print.o

active_events.o:	active_events.c perf_attr_print.h
	$(CC) $(CFLAGS) -c active_events.c


###

log_to_code:	log_to_code.o \
		perf_attr_print.o \
		../lib/perf_helpers.o
	$(CC) $(LFLAGS) -o log_to_code log_to_code.o perf_attr_print.o ../lib/perf_helpers.o

log_to_code.o:	log_to_code.c perf_attr_print.h
	$(CC) $(CFLAGS) -c log_to_code.c

####

perf_fuzzer:	perf_fuzzer.o perf_attr_print.o get_cpuinfo.o \
		fuzz_access.o fuzz_close.o fuzz_fork.o fuzz_ioctl.o \
		fuzz_million.o fuzz_mmap.o fuzz_open.o fuzz_overflow.o \
		fuzz_poll.o fuzz_prctl.o fuzz_read.o fuzz_write.o \
		fuzzer_random.o fuzzer_stats.o \
		../lib/perf_helpers.o ../lib/bpf_helpers.o \
		../lib/instructions_testcode.o \
		trinity_files/trinity_lib.a
	$(CC) $(LFLAGS) -o perf_fuzzer perf_fuzzer.o \
		perf_attr_print.o get_cpuinfo.o \
		fuzz_access.o fuzz_close.o fuzz_fork.o fuzz_ioctl.o \
		fuzz_million.o fuzz_mmap.o fuzz_open.o fuzz_overflow.o \
		fuzz_poll.o fuzz_prctl.o fuzz_read.o fuzz_write.o \
		fuzzer_random.o fuzzer_stats.o \
		../lib/perf_helpers.o ../lib/bpf_helpers.o \
		../lib/instructions_testcode.o \
		trinity_files/trinity_lib.a

perf_fuzzer.o:	perf_fuzzer.c get_cpuinfo.h perf_attr_print.h version.h
	$(CC) $(CFLAGS) -c perf_fuzzer.c

####

perf_fuzzer.x32:	perf_fuzzer.x32.o get_cpuino.x32.o perf_attr_print.x32.o \
		../lib/perf_helpers.x32.o ../lib/instructions_testcode.x32.o \
		trinity_files/trinity_lib.x32.a
	$(CC) $(LFLAGS_X32) -o perf_fuzzer.x32 perf_fuzzer.x32.o \
		get_cpuinfo.x32.o perf_attr_print.x32.o \
		../lib/perf_helpers.x32.o ../lib/instructions_testcode.x32.o \
		trinity_files/trinity_lib.x32.a

perf_fuzzer.x32.o:	perf_fuzzer.c get_cpuinfo.h perf_attr_print.h version.h
	$(CC) $(CFLAGS_X32) -o perf_fuzzer.x32.o -c perf_fuzzer.c

####

trinity_files/trinity_lib.a:	
	cd trinity_files && make

trinity_files/trinity_lib.x32.a:	
	cd trinity_files && make x32

####

clean:	
	rm -f *~ *.o perf_fuzzer replay_log log_to_code filter_log active_events
	cd trinity_files && make clean

