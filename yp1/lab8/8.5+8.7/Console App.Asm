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
STREND  DB      13,10,0             
MESSG2  DB      "Quantiny of numbers?",13,10,0
MESSG3  DB      "Enter:",13,10,0
RES     DQ       0
.data?
PARAM   DQ      ?
.code
ArithAver PROTO QUANT:DWORD
MainProc	proc
       
        Invoke StdOut,addr MESSG2
        Invoke StdIn,addr buf,300
        Invoke atol,addr buf
        PUSH EAX
        Invoke StdOut,addr MESSG3
        POP EAX
        Invoke ArithAver,EAX
        FSTP RES
        Invoke StdOut,ADDR STREND
        Invoke FloatToStr,RES,ADDR buf
        Invoke StdOut,ADDR buf
        Invoke StdOut,ADDR STREND 
            invoke  StdOut, addr szHelloWorld
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp
ArithAver proc QUANT:DWORD
        MOV ECX,QUANT
        FLDZ
        CMP ECX,0
        JE _END
_ALOOP:
        PUSH ECX
        Invoke StdIn,ADDR buf,300
        Invoke StripLF, ADDR buf
        Invoke StrToFloat,ADDR buf,ADDR PARAM
        FLD PARAM
        FADDP ST(1),ST(0)
        POP ECX
        LOOP _ALOOP
        FIDIV QUANT
 _END:      
    ret

ArithAver endp
end MainProc
