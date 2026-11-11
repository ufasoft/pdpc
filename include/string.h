#ifndef	__STRING
#define	__STRING

#include <stddef.h>

int memcmp(const void* lhs, const void* rhs, size_t count);
void* memcpy(void* dest, const void* src, size_t count)
void* memmove(void* dest, const void* src, size_t count)
void* memset(void* dest, int ch, size_t count);
void* memchr(const void* ptr, int ch, size_t count);
char* strcpy(char* dest, const char* src);
char* strcat(char* dest, const char *src);
char* strncat(char* dest, const char *src, size_t count);
int strcmp(const char* lhs, const char* rhs);
char* strdup(const char*);
int strncmp(const char* lhs, const char* rhs, size_t count);
char* strstr(const char* str, const char* substr);
char* strchr(const char* str, int ch );
char* strrchr(const char* str, int ch);
char *strrev(char*);
size_t strspn(const char* dest, const char* src);
size_t strcspn(const char* dest, const char* src);
char *strpbrk(const char *dest, const char *breakset);
char* strtok(char* str, const char* delim);

char* strerror(int);

#endif
