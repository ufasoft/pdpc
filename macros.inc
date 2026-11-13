;;; Copyright (c) 2026 Ufasoft  https://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com
;;;
;;; SPDX-License-Identifier: MIT
;;;

.INCLUDE /pdp11.inc/
.INCLUDE /rt11.inc/

.MCALL	.CFG
.CFG

.IIF NDF C$DBL, 	C$DBL 	= 0			; double is the same as float
.IIF NDF C$DBG, 	C$DBG 	= 0			; Don't include Debug symbols

.LIST	ME		; Macro expansions
.ENABL	AMA		; address mode 37
.ENABL	LC

;; RT-11 macros
.MCALL	.CHAIN, .CSIGEN, .CSISPC, .EXIT, .GTJB, .PRINT, .SETTOP, .TRPSET, .SCCA, .SERR

;; Standard C symbols
.GLOBL	atexit, atof, atoi, atol, calloc, errno, exit, fclose, fopen, fgetc, fprintf, fputc, fputs, free, fseek, gmtime
.GLOBL	isalnum, isdigit, isspace, itoa, ldiv, ltoa
.GLOBL	perror, puts, realloc, stdout, stdin, stderr
.GLOBL	snprintf, strlen, strcpy, strchr, strerror, strftime, strtol, isxdigit, time, toupper

;; libc extension symbols
.GLOBL	ftoa, .msize, ultoa



EPERM	=: 1
ENOENT	=: 2
EIO	=: 5
EBADF	=: 9.
ENOMEM	=: 12.
EFAULT	=: 14.
EBUSY	=: 16.
EEXIST	=: 17.
ENODEV	=: 19.
EINVAL	=: 22.
EMFILE	=: 24.



.GLOBL	$AREA

P.INVO	=: ^o120			; Previos Vector 10
$SCRAT	=: ^o310		; Scratch buffer for temporary values
ASTKLO	=: ^o400
ASTART	=: ^o2000		; Startup code, discarded after Runtime initialization
ASTACK	=: ^o3000


$DEVBL	= $SCRAT

;; BYTE-aligned Read only data
.MACRO	.RDATA
	.PSECT	.rdata, D, RO
.ENDM	.RDATA

;; WORD-aligned Read only data
.MACRO	.RADAT
	.PSECT	.radat, D, RO
.ENDM	.RADAT

.MACRO	.CALLOC	sz
	.IF NB sz
		TRAP	^o105
		.WORD	sz
	.IFF
		TRAP	^o212
	.ENDC
.ENDM	.CALLOC


.MACRO	.REALLOC
	TRAP	^o102
.ENDM	.REALLOC

.MACRO	.SUBRC	fun
	TRAP	^o104
	.WORD	fun
.ENDM	.SUBRC

.MACRO	.CALL1	fun
	TRAP	^o207
	.WORD	fun
.ENDM	.CALL1

.MACRO	.CALL2	fun
	TRAP	^o210
	.WORD	fun
.ENDM	.CALL2

.MACRO	.LARG1
	TRAP	^o211
.ENDM	.LARG1

.MACRO	.LARG2
	TRAP	^o212
.ENDM	.LARG2

.MACRO	.LARGN
	TRAP	^o214
.ENDM	.LARGN

;; Look up low 7 bits of R1 in the list of `case` keys
.MACRO	switch
	TRAP	^o40
	.SWITB = .
.ENDM	switch

;; key: 7-bit value
;; lab: -256..255 WORDs distance
.MACRO	case	key, lab
	.IIF GT lab - . - 511. 	.ERROR	lab is out of bounds
	.IIF GT . - lab - 512.	.ERROR	lab is out of bounds
	.BYTE	key&^o177!<lab-.-2/4&^o200>, lab-.-1/2&^o377
.ENDM	case

.MACRO	default
	.SWITN	= <. - .SWITB> / 2
	.SWITE	= .
	. = .SWITB - 2
	TRAP	^o40 + .SWITN
	. = .SWITE
.ENDM	default

;; Pop a WORD from vevtor. Decrease vec size by 2
;; OUTPUT:
;;   CF=0  - R1: former last word of the vec
;;   CF=1  - vec is empty
.MACRO	POP.W	vec
	TRAP	^o103
	.WORD	vec
.ENDM	POP.W

;; add R1 word into dynamic vector ar
.MACRO	PUSH.W	vec, val
	.IF NB val
		TRAP	^o227
		.WORD	val, vec
	.IFF
		TRAP	^o101
		.WORD	vec
	.ENDC
.ENDM	PUSH.W



;; free `vec` and reset its pointer and size to 0
.MACRO	.CLEAR	vec
	TRAP	^o145
	.WORD	vec
.ENDM	.CLEAR

;; Remove R1 from WORD vector vec
.MACRO	REMO.W	vec
	TRAP	^o100
	.WORD	vec
.ENDM	REMO.W


;; Call & Return
.MACRO	.CCALR	addr, nArg
	TRAP	^o117+nArg
.ENDM	.CCALR


.MACRO	.E.SO
	TRAP	0
.ENDM

.MACRO	.ERR	n
	.IF NB n
		TRAP	n
	.IFF
		TRAP	2
	.ENDC
.ENDM	.ERR

.MACRO	.CKSTK
	CMP	SP, #ASTKLO
	BHIS	.+4
	.E.SO
.ENDM


;; strlen(R1)
.MACRO	.strlen
	TRAP	^o300
.ENDM	.strlen

;; strcmp(R1, R2)
;; OUTPUT: CF:0
.MACRO	.strcmp
	TRAP	^o302
.ENDM	.strcmp

;; strcpy(R1, R2)
.MACRO	.strcpy
	TRAP	^o304
.ENDM	.strcpy

.MACRO	.isspace
	TRAP	^o306
.ENDM	.isspace

.MACRO	.MALLOC
	TRAP	^o310
.ENDM	.MALLOC

.MACRO	.free
	TRAP	^o312
.ENDM	.free

.MACRO	.fputc
	TRAP	^o314
.ENDM	.fputc

.MACRO	.isdigit
	TRAP	^o316
.ENDM	.isdigit

.MACRO	.fputs
	TRAP	^o320
.ENDM	.fputs

.MACRO	.fgetc
	TRAP	^o322
.ENDM	.fgetc

.MACRO	.fclose
	TRAP	^o324
.ENDM	.fclose

.MACRO	.fseek
	TRAP	^o326
.ENDM	.fseek

.MACRO	.isalnum
	TRAP	^o330
.ENDM	.isalnum



RC = %7		; C calling convention register. !!!Change to %7
FP = %4
RT = %5

.MACRO	.NEXT
	JMP	@(RT)+
.ENDM	.NEXT


;; _FILE.flags
F.EOF	= 200
F.ERR	= 100

F.UNG1	= 40	; order does matter in fgetc() and ungetc()

F.TMP	= 4
F.DIRT	= 10


.IIF NE C$DBG .INCLUDE /debug.inc/
