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
    szPrompt      	    db  "Enter integer: ", 0
    szHelloWorld        db   "Press ENTER to continue...", 13, 10, 0
    buf                 db  300 dup(' ')
    strres              db   32 dup(?),13,10,0 
    tmp                 db   "01",13,10,0
    strend db 13,10,0
.code

MainProc	proc
            invoke  StdOut, addr szPrompt
            invoke  StdIn, addr buf, 300
            invoke  atol, addr buf
            mov ecx,32
            lp:
            	shr eax,1
				jc met1
				dec ecx
				mov dl, tmp[0]
				mov strres[ecx], dl
				inc ecx
			met2:
				loop lp
				jmp _end
			met1:
				dec ecx
				mov dl, tmp[1]
				mov strres[ecx], dl
				inc ecx
				jmp met2
			_end:
             invoke  StdOut, addr strres
            invoke  StdOut, addr szHelloWorld
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
