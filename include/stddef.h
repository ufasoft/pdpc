#ifndef	__STDDEF
#define	__STDDEF

typedef unsigned size_t;
typedef int ptrdiff_t;


#define NULL 0

#define offsetof(type, member) ((size_t)&(((type *)0)->member))


#endif
