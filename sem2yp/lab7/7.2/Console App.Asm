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
    buf                 db  300 dup(' ')
;.data?
    str1                 db  10 dup(?),13,10,0
    strend db 13,10,0
.code

MainProc	proc
            mov ecx,26
            xor ebx,ebx
            lpext:
            push ecx
            mov ecx,10
            xor edx,edx
            lp:
            mov  byte ptr str1[edx],bl  
            inc ebx
            inc edx
            loop lp
            push ebx
            push edx
            invoke StdOut, addr  str1
            pop edx
            pop ebx
            pop ecx
            loop lpext
            invoke  StdOut, addr strend
            invoke  StdOut, addr szHelloWorld
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
