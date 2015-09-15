.486
.model flat, stdcall                    
option casemap :none ; пустая , одни пробелы, одно слово

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
    szEndProg       db   "Press ENTER to continue...", 13, 10, 0
    szFormat        db   "%d.%s;",13,10,0
    num             dd    1
    szEnterStr      db   "Enter string:",13,10,0
         
.data?
buf            db    300 dup(?)
temp           db    300 dup(?)
outstr         db    300 dup(?)
      
    
.code
MainProc	proc
            invoke  StdOut, addr szEnterStr
            
            invoke  StdIn, addr buf, 300
            mov buf[eax-2], ' '
            dec eax
            mov ecx,eax
            lea edi, buf
            cld
            _start_cycle:
             jecxz finish
             mov al,' '
             repe scasb
             jecxz finish
             mov ebx,ecx
             mov esi,edi
             dec esi
             repne scasb
             sub ebx,ecx
             xchg ebx,ecx
             mov edx,edi
             lea edi,temp
             rep movsb
             mov al,0
             stosb
             mov edi,edx
             mov ecx,ebx
             pusha
             invoke wsprintf,addr outstr, addr szFormat,num, addr temp
             invoke  StdOut, addr outstr
             popa
             inc num
             jmp _start_cycle 
       finish:
            invoke  StdOut,addr szEndProg
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp
end MainProc