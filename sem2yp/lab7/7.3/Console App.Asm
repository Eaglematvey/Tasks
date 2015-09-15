.486
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
    enterstr            db   "Enter string:",13,10,0
    buf                 db  300 dup(' ')
    str1                 db  300 dup(?),13,10,0
    strend db 13,10,0
.code

MainProc	proc
            invoke  StdOut,  addr enterstr
            invoke StdIn,addr str1,300
            invoke StripLF,addr str1
            sub eax,2
            mov ecx,eax
            lea edi,buf
            lea esi,str1
            _lp:
            lodsb 
            cmp al,97
            jge _check
            jmp _toloop
         _check:
            cmp al,122
            jg _toloop
            sub al,32
         _toloop:
            stosb
            loop _lp
            invoke  StdOut,  addr buf
            invoke  StdOut,  addr strend
            invoke  StdOut, addr szHelloWorld
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
