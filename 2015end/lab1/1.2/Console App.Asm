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
    szEndProg   db   "Press ENTER to continue...", 13, 10, 0
    szEnterN    db   "Enter n:",13,10,0
    szEnterM    db   "Enter m:",13,10,0
    szNewLine   db    13,10,0
.data?
     buf            db    300 dup(?)
    
.code
MainProc	proc
            invoke  StdOut, addr szEnterN 
            invoke  StdIn, addr buf, 300
            Invoke StripLF,ADDR buf
            Invoke atol,ADDR buf
            mov edi,eax
            
            invoke  StdOut, addr szEnterM
            invoke  StdIn, addr buf, 300
            Invoke StripLF,ADDR buf
            Invoke atol,ADDR buf
            mov ecx,eax
            mov eax,edi
            mov ebx,10
            xor esi,esi
            
            cmp ecx,0
            jle finish
            
            cmp eax,0
            jg _cycle
            neg eax
            _cycle:
                xor edx,edx
                div ebx
                add esi,edx
                cmp eax,0
                je finish
            loop _cycle
         finish:
         
            invoke  StdOut, addr szNewLine
            invoke  ltoa, esi, addr buf
            invoke  StdOut, addr buf
            invoke  StdOut, addr szNewLine

            invoke  StdOut,addr szEndProg
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp
end MainProc