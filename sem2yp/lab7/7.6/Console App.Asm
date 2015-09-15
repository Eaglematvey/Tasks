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
  
    
    strend db 13,10,0
       strres              dd 0
       b db 0
       enterstr            db   "Enter string:",13,10,0
    .data?
      buf                 db  300 dup(?)
    strl                dd ?
 
    
;.code
;_numstr PROTO stdcall str1:dword
.code
numstr PROTO str1:dword
MainProc	proc
            invoke  StdOut, addr enterstr
            cld
            invoke  StdIn, addr buf, 300
            invoke  StripLF,addr buf
            lea esi, buf
            _lp:
            invoke numstr,esi
            cmp al,0
            jne _lp
            invoke  StdOut, addr strend
            invoke  ltoa, strres, addr buf
            invoke  StdOut, addr buf
            invoke  StdOut, addr strend
            invoke  StdOut, addr szHelloWorld
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp
numstr proc str1:dword
    mov ebx,1
    mov esi,str1
    lodsb 
    cmp al,32
    je _endp
    cmp al,0
    je _endp
    jmp _incycle
_lpp:
   lodsb 
   cmp al,0
   je _numfound
   cmp al,32
   je _numfound
_incycle:
   cmp al,48
    jge _check
_back:
   mov ebx,0
    jmp _lpp
_check:
    cmp al,57
    jle _lpp
    jmp _back
_numfound:
    mov edx,strres
    add edx,ebx
    mov strres,edx
_endp:
;mov b,al
    ret
numstr endp
end MainProc