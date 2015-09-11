#include "timing.h"

#include <sys/time.h>
#include <ctime>
#include <limits.h>
#include <stdio.h>

namespace timing {
	
typedef unsigned long long timestamp_t;

timestamp_t start_ = 0;
timestamp_t duration_ = ULLONG_MAX;

static timestamp_t get_timestamp()
{
  struct timeval now;
  gettimeofday(&now, NULL);
  return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000L;
}

void start() {
	start_ = get_timestamp();
	duration_ = ULLONG_MAX;
}

void stop() {
	timestamp_t stop = get_timestamp();
	duration_ = stop - start_;
	start_ = 0;
	if (duration_ == stop) {
		printf("TIMING WARNING: it looks like you didn't call start() before stop().\n");
	}
}

void print_micro() {
	if (duration_ == ULLONG_MAX) {
		printf("TIMING WARNING: it looks like you didn't called stop() before printing.\n");
	}
	printf("Elapsed time: %lluus\n", (unsigned long long)duration_);
}

void print_milli() {
	if (duration_ == ULLONG_MAX) {
		printf("TIMING WARNING: it looks like you didn't called stop() before printing.\n");
	}
	printf("Elapsed time: %Lfms\n", duration_ / 1000.0L);
}

void print_sec() {
	if (duration_ == ULLONG_MAX) {
		printf("TIMING WARNING: it looks like you didn't called stop() before printing.\n");
	}
	printf("Elapsed time: %Lfs\n", duration_ / 1000000.0L);
}

}