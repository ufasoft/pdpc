#ifndef	__UNISTD
#define	__UNISTD

int brk(void *addr);
void *sbrk(intptr_t increment);
unsigned sleep(unsigned sec);

#endif
