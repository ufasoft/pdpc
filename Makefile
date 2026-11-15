RT=RT11
MACRO11=$(RT) MACRO

OBJS=CC.OBJ lexer.OBJ parser.OBJ prepro.OBJ trap.OBJ codgen.OBJ

CC.MLB : cc.cfg
	RT11 LIBRARY/MACRO/CREATE cc cc.cfg

CC.SAV: $(OBJS) libc\C.LIB
	pclink11 -MAP -EXECUTE:$@ $(OBJS) libc\C.LIB

%.OBJ : %.mac macros.inc debug.inc ccmacr.inc CC.MLB
	$(MACRO11) /LIST:$(basename $<).lst $<+cc.mlb/LIB

CC.OBJ : cc.mac macros.inc ccmacr.inc CC.MLB
	$(MACRO11) /LIST:cc.lst cc.mac+cc.mlb/LIB

libc/C.LIB :
	cd libc
	make

test:
	cd test
	make

clean:
	-rm *.LIB *.LST *.MAP *.MLB *.OBJ *.SAV


.PHONY: all clean test