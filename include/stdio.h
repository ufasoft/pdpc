#ifndef	__STDIO
#define	__STDIO

#include <stdarg.h>
#include <stddef.h>

#define	EOF	(-1)
#define	FOPEN_MAX 16
#define BUFSIZ 512

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef long fpos_t;

struct _FILE;
typedef struct _FILE FILE;

extern FILE *stdin, *stdout, *stderr;
extern int errno;

FILE* fopen(const char* filename, const char* mode);
int fflush(FILE*);
int fclose(FILE*);
int feof(FILE*);
int ferror(FILE*);
void clearerr(FILE*);
int fseek(FILE* stream, long offset, int whence);
void rewind(FILE*);
size_t fread(void* buffer, size_t size, size_t count, FILE* stream);
size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream);
long ftell(FILE*);
int fileno(FILE*);

int fgetc(FILE*);
#define getc fgetc

int ungetc(int c, FILE*);

int fputc(int ch, FILE*);
#define putc fputc

int fputs(const char*, FILE*);
int puts(const char*);

int vfprintf(FILE*, const char* format, va_list);
int fprintf(FILE*, const char* format, ...);
int vprintf(const char* format, va_list);
int printf(const char*, ...);

int vsprintf(char* buffer, const char* format, va_list);
int sprintf(char* buffer, const char* format, ...);
int vsnprintf(char* buffer, size_t n, const char* format, va_list);
int snprintf(char* buffer, size_t n, const char* format, ...);

int vfscanf(FILE*, const char* format, va_list);
int fscanf(FILE* stream, const char* format, ...);
int vscanf(const char* format, va_list);
int scanf(const char* format, ...);
int sscanf(const char* buffer, const char* format, ...);
int vsscanf(const char* buffer, const char* format, va_list);

void perror(const char*);

int remove(const char*);
int rename(const char* oldfn, const char* newfn);

char* itoa(int value, char* str, int base);

char* tmpnam(char*);
FILE* tmpfile(void);

#endif
