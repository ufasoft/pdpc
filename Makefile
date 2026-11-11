RT=RT11
MACRO11=$(RT) MACRO

OBJS=CC.OBJ lexer.OBJ parser.OBJ prepro.OBJ trap.OBJ codgen.OBJ crt0.OBJ

CC.MLB : cc.cfg
	RT11 LIBRARY/MACRO/CREATE cc cc.cfg

CC.SAV: $(OBJS) libc\C.LIB
	pclink11 -MAP -EXECUTE:$@ $(OBJS) libc\C.LIB

%.OBJ : %.mac macros.inc debug.inc ccmacr.inc CC.MLB
	$(MACRO11) /LIST:$(basename $<).lst $<+cc.mlb/LIB

CC.OBJ : cc.mac crt0.mac macros.inc ccmacr.inc CC.MLB
	$(MACRO11) /LIST:cc.lst cc.mac+cc.mlb/LIB

crt0.OBJ : crt0.mac thunk.mac macros.inc ccmacr.inc CC.MLB
	$(MACRO11) /LIST:crt0.lst crt0.mac+cc.mlb/LIB



libc/C.LIB :
	REM cd libc
	REM make

clean:
	-rm *.LIB *.LST *.MAP *.OBJ *.SAV
