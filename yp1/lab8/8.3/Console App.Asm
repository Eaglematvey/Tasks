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
    Space DB " ",0
i dd 1
j dd 1
m dd ?
numlen dd 0
mas db 1000 dup('0'),0
tmp db "0123456789ABCDEF",13,10,0
STREND  DB      13,10,0             
.code

MainProc	proc
       
        CLD
      mov i,1
		   
			xor ecx, ecx
		lpext:  
			mov j, 1
			lpin:
			 mov eax,i
			 mov ebx,j
			 xor edx,edx
			 mul ebx 
			 mov m,eax
		 met2 :
			 cmp m,0
			 jg met1

			 cmp numlen,1
			 je met3
		 met4:
			 cmp numlen,2
			 je met5
	    met6:
			 mov numlen,0
			mov mas[ecx], 32
			 inc ecx
			 inc j
			 cmp j,16
			 jl lpin
			 
		   mov mas[ecx], 13
		    inc ecx
		   mov mas[ecx],10
		   inc ecx
		   inc i
		   cmp i,16
		   jl lpext
			 
			 jmp _end
		 met1:
			 mov eax, m
			 xor edx, edx
			 mov ebx, 16
			 div ebx
			 mov m, eax
			 mov al, tmp[edx]
			 mov mas[ecx], al
			 inc ecx
			 inc numlen
			jmp met2
		met3:
			 dec ecx
			 mov  al, mas[ecx]
			 mov mas[ecx], 32
			 inc ecx
			 mov mas[ecx],  al
			 inc ecx
			 jmp met4
		 met5:
			 dec ecx
			 mov al, mas[ecx]
			 dec ecx
			 mov bl, mas[ecx]
			 mov mas[ecx],al
			 inc ecx
			 mov mas[ecx],bl
			 inc ecx
			 jmp met6
		_end :
		mov  mas[ecx],13
		inc ecx
		mov mas[ecx],10
		inc ecx
		mov mas[ecx],0
        
       Invoke StdOut,ADDR mas
    
            invoke  StdOut, addr szHelloWorld
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp
end MainProc
