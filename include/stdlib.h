#ifndef	__STDLIB
#define	__STDLIB

#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void* malloc(size_t);
void* calloc(size_t num, size_t size);
void free(void*);
void* realloc(void* ptr, size_t new_size);
size_t _msize(void*);


long strtol(const char* str, char** str_end, int base);
int atoi(const char*);
long atol(const char*);
char* itoa(int value, char* buf, int base);
char* ltoa(long val, char* buf, int base);
char* ultoa(unsigned long val, char* buf, int base);
char* ftoa(float val, char* buf);
double atof(const char*);

int abs(int);
long labs(int);

typedef struct _div_t { int quot; int rem; } div_t;
div_t div(int x, int y);

typedef struct _ldiv_t { long rem; long quot; } ldiv_t;
ldiv_t ldiv(long x, long y);

#define RAND_MAX 32767
void srand(unsigned seed);
int rand(void);

void* bsearch(const void *key, const void *ptr, size_t count, size_t size, int (*comp)(const void*, const void*));
void qsort(void* ptr, size_t count, size_t size, int (*comp)(const void*, const void*));


void abort(void);
void exit(int status);
int atexit(void (*func)(void));

#endif
