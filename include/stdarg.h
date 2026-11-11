#ifndef	__STDARG
#define	__STDARG

typedef char* va_list;

#define va_start(ap, last) (ap = (char*)&last + sizeof(last))
#define va_arg(ap, type) (((type*)(ap += sizeof(type)))[-1])
#define va_end(ap) ap = 0
#define va_copy(dest, src) dest = src

#endif
