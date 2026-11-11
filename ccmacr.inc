;;; Copyright (c) 2026 Ufasoft  https://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com
;;;
;;; SPDX-License-Identifier: MIT
;;;

.INCLUDE /macros.inc/



.GLOBL BINDS, $AHEAP, $EHEAP, CURINP, IS.PP, NO.EXP, $OBASE
.GLOBL	SYNAM0, SYNAM1, TRYEXP


;; Round up R1 to Even value
.MACRO	EVN.UP
	TRAP	^o150
.ENDM	EVN.UP


;; Inserts offset to target into place
;; R1: place in TEXT
;; R2: target in TEXT
.MACRO	EM.OFF
	TRAP	^o151
.ENDM	EM.OFF

;; Inserts offset to current position in TEXT into place
;; R1: place in TEXT
.MACRO	EM.COF
	TRAP	^o152
.ENDM	EM.COF


;; Emit T-code instr and zero place after it
;;   R1: offset to T.JMP's argument in TEXT segment
.MACRO	EM.PLC	instr
	TRAP	^o153
	.WORD	instr
.ENDM	EM.PLC


;; Parse and evaluate Constant Integer Expression
;; OUTPUT: R1: value, $SCRAT: any value
.MACRO	EV.CIE
	TRAP	^o154
.ENDM	EV.CIE

;; Parse and evaluate Constant Expression
;;   R3: Target type to cast or 0
;; OUTPUT: R2: type
;;         $SCRAT: result
.MACRO	EV.CE
	TRAP	^o120
.ENDM	EV.CE

;; Translate a Boolean Expression in parenthesis
.MACRO	.BEXPR
	TRAP	^o155
.ENDM	.BEXPR

;; Translate an Expression in parenthesis (can use commas ',' inside)
;; OUTPUT: R1: Expression Type (last item in EXTYPE)
.MACRO	.PEXPR
	TRAP	^o156
.ENDM	.PEXPR

;; .PEXPR; CK.TOK T.RPAR
.MACRO	.PEXPP
	TRAP	^o233
.ENDM	.PEXPP

;; Call `cb` for every parsed argument separated by comma until `term` terminator
.MACRO	.ITER	cb, term
	TRAP	^o157
	.WORD	cb, term
.ENDM	.ITER

;; Read next Token
;; OUTPUT:  R1: next Token
.MACRO	G.TOK
	TRAP	^o160
.ENDM	G.TOK



;; Reads next Token and jumps to `lab` if it is `tok`
;; Else ungets it
.MACRO	IF.TOK	tok, lab
	TRAP	^o161
	case	tok, lab
.ENDM	IF.TOK

;; Reads next char (skips spaces) and jumps to `lab` if it is `c`
;; Else ungets it
;; OUTPUT: CF=0 - no more chars
.MACRO	IF.CH	c, lab
	TRAP	^o110
	case	c, lab
.ENDM	IF.CH

;; Reads Char
;; If it is `c` then goto `lab`
.MACRO	IF.CHR	c, lab
	TRAP	^o133
	case	c, lab
.ENDM	IF.CHR


;; Parses typed object declaration (typedef, var...)
;; OUTPUT:
;;   R1: Symbol - name of typed object (or 0)
;;   R2: type offset in TYPES
.MACRO	.TYPED
	TRAP	^o162
.ENDM	.TYPED

;; Parse type
;;   Same as: R.TOK, .TYPP2
;; OUTPUT:
;;   R1: type if CF=1
;;   R1: 0 if CF=0 (there is no type designator)
.MACRO	.TYPEP
	TRAP	^o164
.ENDM	.TYPEP

;; Parse type having the first Token in R1
;; OUTPUT:
;;   R1: type if CF=1
;;   R1: 0 if CF=0 (there is no type designator)
.MACRO	.TYPP2
	TRAP	^o107
.ENDM	.TYPP2

;; Unget last token
.MACRO	UN.TOK
	TRAP	^o163
.ENDM	UN.TOK


;; Find symbol R1 in vector `dict` (symbol, value)
;; OUTPUT:
;;   CF=1 R1:Value
;;   CF=0 - not found
.MACRO	.FIND	dict
	TRAP	^o165
	.WORD	dict
.ENDM	.FIND

;; Find symbol R1 in vector `dict` of structure (Symbol, a, b)
;; OUTPUT:
;;   CF=1 R1:a, R2: b, R4: address b in the record
;;   CF=0 - not found
.MACRO	.FIND2	dict
	TRAP	^o166
	.WORD	dict
.ENDM	.FIND2


;; Get or add offset of SYNAM0:SYNAM1 in SYMBS
;; OUTPUT: R1: offset in SYMBS
.MACRO	.SYMB
	TRAP	^o230
.ENDM	.SYMB

;; Combined G.SYM; .SYMB
.MACRO	G.SYMB
	TRAP	^o121
.ENDM	G.SYMB

;; Add data to GSD section of .OBJ file
;; Must be followed by:
.MACRO	.GSD	name, type, flags, value
	TRAP	^o122
	.RAD50	/name/
	.BYTE	flags, type
	.WORD	value
.ENDM	.GSD

;; Parse multiple field declaration
;; R3: common type
;; OUTPUT: R1: Symbol; R2: Type
.MACRO	T.DCL
	TRAP	^o123
.ENDM	T.DCL


;; Translate Field access
;; R1: Symbol
;; Stack: L-Value
;; OUTPUT:  R1: Offset of field, R2: Type of field
.MACRO	T.FLD
	TRAP	^o124
.ENDM	T.FLD

;; Cast char types to int
;; R1: type
;; OUTPUT: R1: original type or TY.I
.MACRO	.TRY2I
	TRAP	^o125
.ENDM	.TRY2I


;; Classifies Symbol offset (R1)
;; OUTPUT
;;   CF=0   - Symbol not found
;;   CF=1:
;;     R0: Symbol category: 0: enum value, 1: variable, 2: function
;;     R1: Symbol value: var/func address, or enum value
;;     R2: type for variable or function
.MACRO	.SYM
	TRAP	^o167
.ENDM	.SYM


;; Skip current value on stack. Move it into R0 if it is int
.MACRO	EM.POP
	TRAP	^o146
.ENDM	EM.POP


;; Emits T$JMP and offset to R1 target
;; OUTPUT:
;;   R1: offset to T$JMP's argument in TEXT segment for possible replacement
.MACRO	EM.JMP
	TRAP	^o147
.ENDM	EM.JMP

;; Check the next token is `tok`
.MACRO	CK.TOK	tok
	.WORD	^o7000 + <tok&^o177>
.ENDM	CK.TOK

;; Emit Thunk address relative to $OBASE
.MACRO	.EMI	off
	.BYTE	off
	.BYTE	^o7400/^o400
.ENDM	.EMI


;; Return next char, Stops on \n
;; Skips comments
.MACRO	R.LCHR
	TRAP	^o214
.ENDM	R.LCHR

;; Raw read char, don't process comments
.MACRO	.NEXTC
	TRAP	^o215
.ENDM	.NEXTC

;; .NEXTC, then add the char to ASCII
.MACRO	.NEXTB
	TRAP	^o220
.ENDM	.NEXTB


.MACRO	R.TOK
	TRAP	^o216
.ENDM	R.TOK

;; Shrinks vector capacity to actual size
.MACRO	.SHRINK	vec
	TRAP	^o217
	.WORD	vec
.ENDM	.SHRINK

;; Save vec and initialize it by Zero
;; Effectively: PUSH vec+2, vec
.MACRO	SV.VEC	vec
	TRAP	^o117
	.WORD	vec
.ENDM	SV.VEC

;; clear vec and replace it by the saved from Stack
.MACRO	RE.VEC	vec
	TRAP	^o116
	.WORD	vec
.ENDM	RE.VEC


;; OUTPUT:
;;   R1: read char or 0
.MACRO	R.CHR
	TRAP	^o130
.ENDM	R.CHR

;;   R1: read char or throw Error on EOF
.MACRO	G.CHR
	TRAP	^o131
.ENDM	G.CHR

;; Unget last read char in R1 into FILE or InputStream
.MACRO	.UNGET
	TRAP	^o132
.ENDM	.UNGET

;; .UNGET without modifying ASCII
.MACRO	.UNGE2
	TRAP	^o213
.ENDM	.UNGE2

;; Parses symbol
;; OUTPUT: R1: #$SCRAT, CF:0
.MACRO	G.SYM
	TRAP	^o135
.ENDM	G.SYM

;; Parses symbol avoiding Preprocessor expansion
;; OUTPUT: R1: #$SCRAT, CF:0
.MACRO	PP.SYM
	TRAP	^o221
.ENDM	PP.SYM

;; Skip whitespace
.MACRO	SK.WS
	TRAP	^o136
.ENDM	SK.WS

;; Read char after preprocessing
.MACRO	PP.CHR
	TRAP	^o137
.ENDM	PP.CHR

;; Find word R1 in table, following this macro
;; OUTPUT: R1: number of symbol, CF=1
;; CF=0, if the Symbol not found
.MACRO	F.WORD
	TRAP	^o140
.ENDM	F.WORD


;; Insert R1 entry into list
.MACRO	LS.INS	list
	TRAP	^o141
	.WORD	list
.ENDM	LS.INS

;; Remove R1 entry from list
.MACRO	LS.DEL	list
	TRAP	^o142
	.WORD	list
.ENDM	LS.DEL

;; CRADIX-50
;;  - same as RADIX-50, but '_' is encoded as '.' <34>

;; Encode ASCIZ in $SCRAT to CRADIX-50 in SYNAM0, SYNAM1
;; OUTPUTL R1: SYNAM0
.MACRO	A.R50
	TRAP	^o143
.ENDM	A.R50


;; Find 2-word entry in table, following this macro
;; OUTPUT: R1: number of symbol, CF=1
;; or branch by offset in Last Word, if the Symbol not found
.MACRO	F.DWORD
	TRAP	^o144
.ENDM	F.DWORD


;; Begin .OBJ block type of typ
.MACRO	OU.BLK	typ
	TRAP	^o170
	.WORD	typ
.ENDM	OU.BLK

;; Write WORD in R3 into current block of .OBJ file
.MACRO	OU.W
	TRAP	^o171
.ENDM	OU.W

;; Write BYTE in R3 into current block of .OBJ file
.MACRO	OU.B
	TRAP	^o231
.ENDM	OU.B

;; R1: TYPES offset
;; OUTPUT: ZF=1 if the type is a function
.MACRO	IS.FUN
	TRAP	^o232
.ENDM	IS.FUN

;; Finalize block
;; Write length and checksum
.MACRO	OU.FIN
	TRAP	^o172
.ENDM	OU.FIN

;; R1: type
;; OUTPUT: CF=1 if type was an array, R1: element type of array
.MACRO	IS.ARR
	TRAP	^o106
.ENDM	IS.ARR


;; Determine Type category
;; R1: type
;; OUTPUT: R2: category: TC.ARR, TC.SCT, TC.SCA ...
.MACRO	TY.CAT
	TRAP	^o206
.ENDM	TY.CAT


;; R1: type
;; OUTPUT: CF=1 if type was a pointer, R1: target type of pointer
.MACRO	IS.PTR
	TRAP	^o173
.ENDM	IS.PTR


;; R1: type
;; OUTPUT: R1: (type*) -- offset in TYPES table
.MACRO	PTR.OF
	TRAP	^o174
.ENDM	PTR.OF

;; R1: type
;; OUTPUT: R1: sizeof(type)
.MACRO	SZ.TYP
	TRAP	^o175
.ENDM	SZ.TYP

;; R1: type
;; OUTPUT: R1: sizeof(type) aligned up to WORD
;; Side effect: adds this size to R2
.MACRO	SZ.ALG
	TRAP	^o201
.ENDM	SZ.ALG

;; Ensure top of EXTYPE is R-Value
;; OUTPUT: R1: Type
.MACRO	C.RVAL
	TRAP	^o176
.ENDM	C.RVAL

;; Converts pointer to L-Value
.MACRO	C.LVAL
	TRAP	^o177
.ENDM	C.LVAL

;; add args WORD into .TEXT section
.MACRO	.EMIT	arg
        .IF NB arg
        	TRAP	^o200
        	.WORD	arg
        .IFF
        	TRAP	^o222
        .ENDC
.ENDM	.EMIT

;; Parse unary expression
.MACRO	.UNARY
	TRAP	^o340
.ENDM	.UNARY

;; Parse expression
.MACRO	.EXPR
	TRAP	^o202
.ENDM	.EXPR

;!!!R .MACRO	.ASGMT
;!!!R 	TRAP	^o203
;!!!R .ENDM	.ASGMT

;; Parse Unary R-Value
;; OUTPUT: R1: Type
.MACRO	P.UNRV
	TRAP	^o204
.ENDM	P.UNRV

;; R1: target local `name` (0: function scope)
;; OUTPUT: R1: offset to local var or argument `name` relative SP
.MACRO	LOC.FI
	TRAP	^o223
.ENDM	LOC.FI

;; OUTPUT: R1: offset in TEXT to save jmp offset
.MACRO	EM.BEQ
	TRAP	^o224
.ENDM	EM.BEQ

;; OUTPUT: R1: offset in TEXT to save jmp offset
.MACRO	EM.BNE
	TRAP	^o225
.ENDM	EM.BNE

;; R1: target offset behind local var's entry in LOCALS
;; OUTPUT: R1: offset to local var or argument `name` relative SP
.MACRO	LOC.OF
	TRAP	^o205
.ENDM	LOC.OF

;!!!R ;; R1: target local `name` (0: function scope)
;!!!R .MACRO	.UNWIND
;!!!R 	TRAP	^o206
;!!!R .ENDM	.UNWIND

;; R1: offset in LOCALS
.MACRO	.UNWTO
	TRAP	^o207
.ENDM	.UNWTO

;; Translate a Scoped Statement (statement which unwinds)
.MACRO	.STMT
	TRAP	^o210
.ENDM	.STMT

;; Initialize Global variable by Constant Expression
;; R3: Type of variable
.MACRO	.GINI
	TRAP	^o334
.ENDM	.GINI

;; Initialize Local variable/struct field/array element
;; R3: Type of variable
;; R5: Offset of the field in the Stack
.MACRO	.LINI
	TRAP	^o336
.ENDM	.LINI

;; Add R1 byte into dynamic vector ar
;; Returns: R1 unmodified, ZF=1 if R1==0
.MACRO	PUSH.B	vec
	TRAP	^o234
	.WORD	vec
.ENDM	PUSH.B

;; CLR R1; PUSH.B vec
.MACRO	PU.BZ	vec
	TRAP	^o211
	.WORD	vec
.ENDM	PU.BZ

;; Add ASCIZ string dynamic vector ar. Adds also terminating NUL
;; R1: pointer to ASCIZ string
.MACRO	PUSH.S	vec
	TRAP	^o235
	.WORD	vec
.ENDM	PUSH.S

;; Add R1,R2 DWORD into dynamic vector ar
.MACRO	PUSH.D	vec
	TRAP	^o236
	.WORD	vec
.ENDM	PUSH.D


;; Cast current expression to bool (0 or 1)
.MACRO	CAST.B
	TRAP	^o126
.ENDM	CAST.B

;; Cast current expression to `type` in R1
.MACRO	.CAST
	TRAP	^o114
.ENDM	.CAST

;; Cast current expression to int
.MACRO	CAST.I
	TRAP	^o115
.ENDM	CAST.I


;; OUTPUT:
;;  R4: Pointet to top item in EXTYPE
.MACRO	EXTY.P
	TRAP	^o127
.ENDM	EXTY.P

;; PUSH.W EXTYPE
.MACRO	PU.EXT
	TRAP	^o226
.ENDM	PU.EXT

;; POP.W EXTYPE
.MACRO	PO.EXT
	TRAP	^o203
.ENDM	PO.EXT

;; MOV #TY.I, R1; PUSH.W EXTYPE
.MACRO	PU.TYI
	TRAP	^o111
.ENDM	PU.TYI

;; OUTPUT:
;;  R1: type of top expression
.MACRO	.EXTYP
	TRAP	^o113
.ENDM	.EXTYP

;; Emit global symbol
.MACRO	.EMSYM	sym, addr
	TRAP	^o112
	.WORD	sym, addr
.ENDM	.EMSYM





.MACRO	.fopen
	TRAP	^o342
.ENDM	.fopen


.MACRO	.strcat
	TRAP	^o332
.ENDM	.strcat



;; Tokens
;; Low byte: token ID (must be 1..0x7F)
;; High byte: precedence

;; Keywords

;;-- Two lower bits are used as part of TDEFS key
T.ENUM	= ^x01
T.STRU	= ^x02	; struct
T.UNIO	= ^x03	; union
;;--

T.CHAR	= ^x04
T.CONST	= ^x05	; const
T.CONT	= ^x06	; continue
T.DEFA	= ^x07	; default
T.DO	= ^x08
T.DOUB	= ^x09	; double
T.ELSE	= ^x0A
T.AUTO	= ^x0B
T.EXTE	= ^x0C	; extern
T.FLOA	= ^x0D	; float
T.FOR	= ^x0E
T.GOTO	= ^x0F
T.IF	= ^x10
T.INLI	= ^x11	; inline
T.INT	= ^x12
T.LONG	= ^x13
T.REGI	= ^x14	; register
T.RETU	= ^x15	; return
T.SHOR	= ^x16	; short
T.SIGN	= ^x17	; signed
T.SIZE	= ^x18	; sizeof
T.STAT	= ^x19	; static
T.BREAK = ^x1A
T.SWIT	= ^x1B	; switch
T.TYPE	= ^x1C	; typedef
T.CASE	= ^x1D
T.UNSI	= ^x1E	; unsigned
T.VOID	= ^x1F
T.VOLA	= ^x20	; volatile
T.WHIL	= ^x21	; while

;; Flags
TF.BIN	= ^x8000	; binary operation
TF.ASG	= ^x10		; assignment operation

;;-- Must be adjacent
T.ADD	= ^x0C61 ! TF.BIN	; +	; Low 2 bits are used in POINCR
T.SUB	= ^x0C62 ! TF.BIN	; -	;
T.AST	= ^x0D63 ! TF.BIN	; *
T.DIV	= ^x0D64 ! TF.BIN	; /
T.MOD	= ^x0D65 ! TF.BIN	; %
T.AND	= ^x0866 ! TF.BIN	; &
T.OR	= ^x0667 ! TF.BIN	; |
T.XOR	= ^x0768 ! TF.BIN	; ^
T.LSH	= ^x0B69 ! TF.BIN	; <<
T.RSH	= ^x0B6A ! TF.BIN	; >>

T.LAND	= ^x56B  ! TF.BIN	; &&
T.LOR	= ^x46C  ! TF.BIN	; ||
T.TERN	= ^x26D  ! TF.BIN	; ?

T.ASGN	= ^x170  ! TF.BIN	; =
T.ADDA	= ^x171  ! TF.BIN	; +=
T.SUBA	= ^x172  ! TF.BIN	; -=
T.MULA	= ^x173  ! TF.BIN	; *=
T.DIVA	= ^x174  ! TF.BIN	; /=
T.REMA	= ^x175  ! TF.BIN	; %=
T.ANDA	= ^x176  ! TF.BIN	; &=
T.ORA	= ^x177  ! TF.BIN	; |=
T.XORA	= ^x178  ! TF.BIN	; ^=
T.LSHA	= ^x179  ! TF.BIN	; <<=
T.RSHA	= ^x17A  ! TF.BIN	; >>=


T.EQ	= ^x0941 ! TF.BIN	; ==
T.NE	= ^x0942 ! TF.BIN	; !=
T.LT	= ^x0A43 ! TF.BIN	; <
T.LTEQ	= ^x0A44 ! TF.BIN	; <=
T.GT	= ^x0A45 ! TF.BIN	; >
T.GTEQ	= ^x0A46 ! TF.BIN	; >=

T.LSTR	= ^x22			; "

;; When IS.EXP is true
;;--
T.SH	= ^x23	; #
T.SHSH	= ^x24	; ##
;;--



T.INCR	= ^x0F3D		; ++
T.DECR	= ^x0F2A		; --
T.ARRO	= ^x0F2B		; ->


T.3DOT	= ^x59			; ...
T.SYM	= ^x5A

T.LPAR	= ^x28			; (
T.RPAR	= ^x29			; )
T.COMM	= ^x2C			; ,
T.DOT	= ^x2E			; .
T.COLO	= ^x3A			; :
T.SEMI	= ^x3B			; ;
T.BRA	= ^x5B			; [
T.KET	= ^x5D			; ]
T.LBRC	= ^x7B			; {
T.RBRC	= ^x7D			; }
T.NOT	= ^x7E			; ~

T.LNOT	= ^x7F			; !


;;--- Order does matter
T.LLNG	= ^x026		; long literal
T.LINT	= ^x027		; '\'' int literal
T.LFLT	= ^x06F		; float literal
.IIF NE C$DBL	T.LDBL	= ^x038		; double literal
;;---


T.SP	= ^x3E	; Space

TY.VOID	= 0
TY.SYM	= ^o77760	; Global Symbol address
TY.UNK	= ^o77765
TY.C	= ^o77766
TY.SC	= ^o77767
TY.UI	= ^o77770	; unsigned, unsigned short
TY.I	= ^o77771	; int, short
TY.UL	= ^o77772
TY.L	= ^o77773
TY.FLT	= ^o77775
.IIF NE C$DBL	TY.DBL	= ^o77777

;; Type categories
TC.VOID	= 0
TC.ENU	= T.ENUM&377	; 1 enum
TC.SCT	= T.STRU&377	; 2 struct
TC.UNI	= T.UNIO&377	; 3 union
TC.SCA	= 4		; scalar (number)
TC.ARR	= 5		; array
TC.PTR	= 6
TC.FUN	= ^o10		; function

;; .OBJ section names
BT.GSD	= 1
BT.EGS	= 2
BT.TXT	= 3
BT.RLD	= 4
BT.END	= 6
