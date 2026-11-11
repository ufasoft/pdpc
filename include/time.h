#ifndef	__TIME
#define	__TIME

#include <stddef.h>

typedef unsigned long time_t;	// Unsigned to address Y2038 problem

struct tm {
	int	  tm_sec
		, tm_min
		, tm_hour
		, tm_mday
		, tm_mon
		, tm_year
		, tm_wday
		, tm_yday
		, tm_isdst;
};

extern long timezone;

time_t time(time_t* arg);
time_t mktime(struct tm*);
struct tm* gmtime(const time_t*);
struct tm* localtime(const time_t*);
size_t strftime(char* s, size_t maxsize, const char* format, const struct tm*);
char *asctime(const struct tm*);
char *ctime(const time_t*);

extern int CLOCKS_PER_SEC; // 60 or 50 Hz
typedef long clock_t;
clock_t clock(void);

#endif
