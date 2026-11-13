# Ufasoft C Compiler for PDP-11 (RT-11 OS)

## Developer's Manual

**Version:** 2026.0

This is a minimal compiler for [PDP-11](https://en.wikipedia.org/wiki/PDP-11) computers family, implementing subset of [ANSI C](https://en.wikipedia.org/wiki/ANSI_C) (C89) standard.

It generates [threaded code](https://en.wikipedia.org/wiki/Threaded_code).

The project's codename is **PDP C**.

The priority was the compiler binary size. So it doesn't have any optimizer.

Project's site: https://ufasoft.com/pdpc

Developer's kit for RT-11: [pdpc.7z](https://ufasoft.com/files/pdpc/pdpc.7z)

Floppy disk image for УКНЦ: [ccuknc.dsk](https://ufasoft.com/files/pdpc/ccuknc.dsk)

Floppy disk image for БК-0011М: [cc-osbk.dsk](https://ufasoft.com/files/pdpc/cc-osbk.dsk)

**Author:** Sergey Pavlov (dev@ufasoft.com)

## Requirements

- PDP-11 compatible CPU with EIS and FIS instruction sets. Or installed emulator of them.
  - FIS is used for floating point operations. Integer-only programs don't require it.
- 56 KB RAM

Originally it was designed for running on Soviet PDP-11 clones:

- [МС 0502 (ДВК-3)](https://en.wikipedia.org/wiki/DVK)
- [МС 0511 (УКНЦ)](https://en.wikipedia.org/wiki/UKNC)

## Command line

```text
.CC [options] foo.c
```

By default this builds `foo.sav` executable file.

Options:

- `-c` Compile only, without LINK invocation.
- `-D sym` Add `#define sym 1` Preprocessor definition.
- `-E` Preprocess only.
- `-o fname` Place output in file `fname`.

## Predefined preprocessor macros

- `__pdp11__ = 40` (as PDP-11/40 was the model supporting both EIS and FIS instruction sets).
- `_PDPC = 20260` (encoded version number)
- `__DATE__`
- `__FILE__`
- `__LINE__`

## Calling conventions

Push all arguments to Stack, beginning with the last argument.

Copy first five argument WORDs to registers R1..R5.

Assign register R0 = 0.

Call with `JSR PC, funaddr` instruction.

In the called function the address of the first argument would be SP+2.

Functions return by `RTS PC` instruction. The caller is responsible for cleaning the Stack from arguments.

The function result is in R0 or for 32-bit results in R1:R0 (R1 contains higher 16 bits).

Most of standard functions from C.LIB library don't use arguments from the Stack and can be invoked with arguments in registers only.

Exceptions: variable-parameter functions, like `printf()`.

## Differences from the ANSI C Standard

- Identifiers are case-insensitive, only first 6 chars are significant for compatibility with the RT-11 linker.

  `_` (underscore) character is mapped to RADIX-50 `.` (dot) character in `.OBJ` file.

  Preprocessor identifiers are case-sensitive and all chars are significant.

- There are no [Digraphs and Trigraphs](https://en.wikipedia.org/wiki/Digraphs_and_trigraphs).
- `double` and `float` are the same type - 4-byte value in DEC's format.
- `time_t` is 4-byte unsigned long to address [Y2038 problem](https://en.wikipedia.org/wiki/Year_2038_problem).

## Limitations

- Maximum of 15 simultaneously open files.

  Every `fopen()` allocates 526 bytes for buffer, so the actual limit may be lower because of Heap fragmentation.
- Stack size is ~1200 bytes.
- Command line is limited by 80 chars.
- Sum of function invocation arguments sizes must be <= 126 bytes.

---

## Error codes

- Stack overflow.
- C1 - Command line error.
- C2 - General unclassified error.
- C3 - Preprocessor `#error` directive.
- C4 - Comma is expected.
- C5 - Unexpected token.
- C6 - Overflow
- C8 - Wrong constant expression.
- C9 - Wrong variable initialization.
- C10 - `.OBJ` file write error.
- C11 - Arithmetic error (Division by zero).
- C12 - Undeclared Identifier.
- C12 - Incorrect Token.
- C14 - Invalid declarator.
- C16 - Wrong type.
- C17 - Wrong field name.
- C19 - The statement is not allowed here.
- C20 - Not supported functionality.
- C21 - Expression must be L-Value.

## C.LIB - standard C Library

Implemented functions:

`abort`, `abs`, `asctime`, `atexit`, `atof`, `atoi`, `atol`, `brk`, `bsearch`, `calloc`, `clearerr`, `clock`, `ctime`, `div`, `exit`, `fclose`, `feof`, `ferror`, `fflush`, `fgetc`, `fileno`, `fopen`, `fprintf`, `fputc`, `fputs`, `fread`, `free`, `fscanf`, `fseek`, `ftell`, `ftoa`, `fwrite`, `getc`, `gmtime`, `isalnum`, `isalpha`, `isdigit`, `islower`, `isprint`, `isspace`, `isupper`, `isxdigit`, `itoa`, `labs`, `localtime`, `longjmp`, `ltoa`, `malloc`, `memchr`, `memcmp`, `memcpy`, `memmove`, `memset`, `mktime`, `_msize`, `perror`, `puts`, `qsort`, `rand`, `realloc`, `rename`, `rewind`, `sbrk`, `scanf`, `setjmp`, `signal`, `snprintf`, `srand`, `sscanf`, `strcat`, `strchr`, `strcpy`, `strcspn`, `strdup`, `strerror`, `strftime`, `strlen`, `strncat`, `strncmp`, `strpbrk`, `strrchr`, `strrev`, `strspn`, `strstr`, `strtok`, `strtol`, `time`, `tmpfile`, `tmpnam`, `tolower`, `toupper`, `ungetc`, `vfprintf`, `vprintf`, `vsnprintf`.

---

© Ufasoft
