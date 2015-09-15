.586
.model flat
.data 
b db 0
_strl1 dd -1
_strl2 dd -1
decim  dd 10
.code

@Cats@8 proc
     mov _strl1,-1
    mov _strl2,-1
   mov ebx,ecx
    cld          
	   lea edi, [edx]
	   mov ecx,-1
	   mov al,0
	   repne scasb
	   sub _strl2,ecx
	   dec _strl2    
	     
	    lea edi,[ebx]
	    mov ecx,-1
	    mov al,0
	    repne scasb
	    sub _strl1,ecx
	    dec _strl1  
		  
	   mov ecx,_strl1
	   lea edi,[ebx]
	   lea esi,[edx]
	   repne scasb
	   mov ecx,_strl2
	   rep movsb
	   mov byte ptr [edi],0;
	  mov eax,ebx
ret 
@Cats@8 endp


@Sum@8 proc
   mov _strl1,-1
   mov _strl2,-1
   mov ebx,ecx
   cld          
	   lea edi, [ebx]
	   mov ecx,-1
	   mov al,0
	   repne scasb
	   sub _strl1,ecx
	   dec _strl1    
	        
	   lea edi, [edx]
	   mov ecx,-1
	   mov al,0
	   repne scasb
	   sub _strl2,ecx
	   dec _strl2

	   mov esi,_strl1
	   mov edi,_strl2
	   cmp esi,edi
	   jl met
	_back:
	   mov esi,ebx
	   mov edi,edx
	   xor eax,eax
  mov ebx,_strl1
    mov  ecx,_strl2

	xor edx,edx
lp: dec ecx
    dec ebx
mov al,[esi+ebx]
    add al,[edi+ecx]
	add al,dl
	sub al,48
	xor dl,dl
	cmp al,57
	jg _chk
_back2:
    mov [esi+ebx],al
    inc ecx
    loop lp
	dec ebx
	add [esi+ebx],dl
	 jmp _end
met:
	 xchg ebx,edx
	 mov b,1
	 mov eax,_strl2
	 mov ecx, _strl1
	 mov _strl2,ecx
	 mov _strl1,eax
	 jmp _back
_chk:  
      sub al,10
	  add dl,1
	   jmp _back2
	 _end:
     mov eax,esi
ret    
@Sum@8 endp
end 