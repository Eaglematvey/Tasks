.386
.model flat
option casemap : none

.data
n dd ? ; Размер массива
max dd ?
.code
@SorT@8 proc
        xchg edx,ecx
		mov n,ecx
        xor ecx, ecx
        push n
        pop ecx
    
cycl_1: push ecx        
        mov eax, n
        dec eax
        push eax
        pop ecx
        mov esi, edx
    
cycl_2: mov eax, [esi]     
        mov ebx, [esi+4]
        cmp ebx, eax
        js swap
    
just_:  add esi, 4     
        loop cycl_2
        
        pop ecx
        loop cycl_1
            
        ret
    
swap:   mov [esi], ebx  
        mov [esi+4], eax
        jmp just_ 
ret
@SorT@8 endp

end

