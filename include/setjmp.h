#ifndef	__SETJMP
#define	__SETJMP

typedef void *jmp_buf[3];

int setjmp(jmp_buf);
void longjmp(jmp_buf, int);

#endif
