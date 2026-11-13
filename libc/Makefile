RT=RT11
MACRO11=$(RT) MACRO

CC.MLB : clib.cfg
	RT11 LIBRARY/MACRO/CREATE cc clib.cfg

%.OBJ : %.mac macros.inc CC.MLB
	$(MACRO11) /LIST:$(basename $<).lst $<+cc.mlb/LIB

CRT0.OBJ : crt0.mac thunk.mac macros.inc CC.MLB
	$(MACRO11) /LIST:crt0.lst crt0.mac+cc.mlb/LIB

C.LIB : brk.OBJ bsearc.OBJ trap.OBJ float.OBJ fread.OBJ fwrite.OBJ ftoa.OBJ heap.OBJ ltoa.OBJ perror.OBJ printf.OBJ qsort.OBJ rand.OBJ rename.OBJ \
		scanf.OBJ setjmp.OBJ signal.OBJ sleep.OBJ stdio.OBJ stdlib.OBJ string.OBJ strerr.OBJ strspn.OBJ atof.OBJ strtol.OBJ time.OBJ tmpfil.OBJ
	$(RT) LIB/CREATE C.LIB stdio,fread,string
	$(RT) LIB/INSERT C.LIB heap,ltoa,perror,printf
	$(RT) LIB/INSERT C.LIB setjmp,stdlib,strerr
	$(RT) LIB/INSERT C.LIB strtol,trap,rand,time
	$(RT) LIB/INSERT C.LIB atof,float,ftoa
	$(RT) LIB/INSERT C.LIB scanf,brk
	$(RT) LIB/INSERT C.LIB bsearc,fwrite,rename,tmpfil
	$(RT) LIB/INSERT C.LIB qsort,strspn,signal,sleep

clean:
	-rm *.LST *.OBJ *.LIB *.SAV
