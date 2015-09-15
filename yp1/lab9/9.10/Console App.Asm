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
    resultstr           db "Result:",13,10,0
    Space DB " ",0
    b db 0
STREND  DB      13,10,0            
NTEMP DB     100 DUP(?),0
MESSG1  DB      "Enter one by one:",13,10,0
MESSG2  DB      "Enter N:",13,10,0
NCTR DB      0
SorT PROTO tab:DWORD,n:DWORD
StrXchg PROTO n:DWORD
StrXsum PROTO n:DWORD
MyLen PROTO strin:DWORD
.data?
NTAB DD      100 DUP(?)
  sav1 dd ?
  sav2 dd ?
  sav dd ?
  n4 dd ?
  N  dd ?
.code
MainProc	proc
       
        Invoke StdOut,addr MESSG2
        Invoke StdIn,addr buf,300
        Invoke atol,addr buf
        mov N,EAX
        XOR EDX,EDX
        MUL N
        CMP EAX,0
        JE _END
        PUSH EAX
        Invoke StdOut,addr MESSG1
        POP ECX
        XOR EBX,EBX
A20LOOP:
        PUSH ECX
        
        Invoke StdIn,ADDR NTEMP,100
        Invoke StripLF, ADDR NTEMP
        Invoke atol,ADDR NTEMP
        MOV NTAB[EBX*4],EAX
        INC EBX
        POP ECX
        INC NCTR
        LOOP A20LOOP
A30:                            
        CMP     NCTR,1     
        JBE     A40            
        Invoke SorT,ADDR NTAB,N
        Invoke StdOut,ADDR STREND
        Invoke StdOut,ADDR resultstr
A40: 
       
       MOV ECX,N
       XOR EBX,EBX
A45LOOP:
        PUSH ECX
        MOV ECX,N
A50LOOP: 
       PUSH ECX
       Invoke dwtoa, NTAB[EBX*4],ADDR NTEMP
       Invoke StdOut,ADDR NTEMP
       Invoke MyLen,ADDR NTEMP
       MOV ECX,12
       SUB ECX,EAX
A55LOOP:
       PUSH ECX
       Invoke StdOut,ADDR Space
       POP ECX
       loop A55LOOP
       INC EBX
       POP ECX
       LOOP A50LOOP
       
       Invoke StdOut,ADDR STREND
       Invoke StdOut,ADDR STREND
       POP ECX
       LOOP A45LOOP
_END:         
       Invoke  StdOut, addr szHelloWorld
       Invoke  StdIn, addr buf, 300
       Invoke  ExitProcess, 0
MainProc    endp


SorT proc tab:dword,n:dword
        mov eax,n
        xor edx,edx
        mov ebx,4
        mul ebx
        mov n4,eax
        push n
        pop ecx
cycl_1: push ecx        
        mov eax, n
        dec eax
        push eax
        pop ecx
        mov esi, tab
        
    
cycl_2: mov eax, esi    
        add esi,n4
        mov ebx,esi
        sub esi,n4
        push ecx
        invoke StrXsum,n
        pop ecx
        cmp  sav1,edi
        js swap
    
just_:  add esi,n4
        loop cycl_2
        
        pop ecx
        loop cycl_1
            
        ret
    
swap:   push ecx
        invoke StrXchg ,n
        pop ecx
        jmp just_ 
ret
SorT endp
StrXchg proc n:DWORD
        mov ecx,n
        xor edx,edx
cycle:
        mov edi,dword ptr [eax+edx*4]
        mov sav,edi
        mov edi,dword ptr [ebx+edx*4]
        mov dword ptr [eax+edx*4],edi
        mov edi,sav
        mov dword ptr [ebx+edx*4],edi
        inc edx
        loop cycle
ret 

StrXchg endp

StrXsum proc n:DWORD
        mov b,0
_start:
       mov ecx,n
       xor edi,edi
cycle:
       dec ecx
       mov edx,[ebx+ecx*4]
       inc ecx
       add edi,edx
       loop cycle
  
       cmp b,0
       je _secondloop
       jmp _end
_secondloop:
       xchg ebx,eax
       mov b,1
       mov sav1,edi
       jmp _start
_end:
       xchg ebx,eax
       mov sav2,edi
ret 
StrXsum endp


MyLen proc strin:dword
		cld
		mov edi, strin
		mov ecx, 100
		mov al, 0

  repne scasb

		mov eax, 100
		sub eax, ecx
		dec eax
		
		ret
MyLen endp
end MainProc