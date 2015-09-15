.586
.model flat, stdcall                    
option casemap :none

include windows.inc     ; always first

include masm32.inc
include gdi32.inc
include user32.inc
include kernel32.inc

includelib masm32.lib
includelib gdi32.lib
includelib user32.lib
includelib kernel32.lib

.data
    szHelloWorld        db   "Press ENTER to continue...", 13, 10, 0
    buf                 db  300 dup(' ')
    Space               db " ",0
STREND  DB      13,10,0             
MESSG2  DB      "Enter A:",13,10,0
MESSG3  DB      "LOG2(X):",13,10,0
MESSG4  DB      "LN(X):",13,10,0
MESSG5  DB      "E^X:",13,10,0
MESSG6  DB      "A^X:",13,10,0
RES     DQ       0
_X       DQ      1
_STEP    DQ      0.5
.data?
_A      DQ       ?
PARAM   DQ      ?
.code
LN PROTO X:QWORD
L2 PROTO X:QWORD
POWE PROTO X:QWORD
POWA PROTO X:QWORD,A:QWORD
XPLUSSTEP PROTO X:QWORD,STEP:QWORD
MainProc	proc
        Invoke StdOut,addr MESSG2
        Invoke StdIn,addr buf,300
        Invoke StrToFloat,ADDR buf,ADDR _A
        Invoke StdOut,ADDR STREND
        Invoke StdOut,ADDR MESSG3
        MOV ECX,19
        FLD1
        FSTP _X
    ALOOP:
        PUSH ECX
        Invoke L2,_X
        FSTP RES
        Invoke FloatToStr,RES,ADDR buf
        Invoke StdOut,ADDR buf
        Invoke StdOut,ADDR Space
        Invoke XPLUSSTEP, _X,_STEP
        FSTP _X
        POP ECX
        LOOP ALOOP
        Invoke StdOut,ADDR STREND
        Invoke StdOut,ADDR MESSG4 
        MOV ECX,19
        FLD1
        FSTP _X
    BLOOP:
        PUSH ECX
        Invoke LN,_X
        FSTP RES
        Invoke FloatToStr,RES,ADDR buf
        Invoke StdOut,ADDR buf
        Invoke StdOut,ADDR Space
        Invoke XPLUSSTEP, _X,_STEP
        FSTP _X
        POP ECX
        LOOP BLOOP
        Invoke StdOut,ADDR STREND 
        Invoke StdOut,ADDR MESSG5
        MOV ECX,19
        FLD1
        FSTP _X
    CLOOP:
        PUSH ECX
        Invoke POWE,_X
        FSTP RES
        Invoke FloatToStr,RES,ADDR buf
        Invoke StdOut,ADDR buf
        Invoke StdOut,ADDR Space
         Invoke XPLUSSTEP, _X,_STEP
        FSTP _X
        POP ECX
        LOOP CLOOP
        Invoke StdOut,ADDR STREND 
        Invoke StdOut,ADDR MESSG6
        
        MOV ECX,19
        FLD1
        FSTP _X
    DLOOP:
        PUSH ECX
        Invoke POWA,_X,_A
        FSTP RES
        Invoke FloatToStr,RES,ADDR buf
        Invoke StdOut,ADDR buf
         Invoke StdOut,ADDR Space
        Invoke XPLUSSTEP, _X,_STEP
        FSTP _X
         POP ECX
        LOOP DLOOP
      
        Invoke StdOut,ADDR STREND 
            invoke  StdOut, addr szHelloWorld
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp
LN proc X:QWORD
    fldln2
    fld X
    fyl2x
    fstp st(1)
    ret
LN endp
L2 proc X:QWORD
    fld1
    fld X
    fyl2x
    fstp st(1)
    ret
L2 endp
POWE proc X:QWORD
   fld     X
   fldl2e
   fmul
   fld     st(0)
   frndint
   fsub    st(1), st(0)
   fxch    st(1)
   f2xm1
   fld1
   fadd
   fscale
   fstp    st(1)
    ret
POWE endp
POWA proc X:QWORD,A:QWORD
    invoke LN,A
    fmul X
    fstp PARAM
    invoke POWE,PARAM
    ret

POWA endp
XPLUSSTEP proc X:QWORD,STEP:QWORD
    FLD X
    FLD STEP
    FADDP ST(1),ST(0)
    ret

XPLUSSTEP endp
end MainProc