.586 
.model flat 
option casemap:none
.data
temp dq 0
temp2 dq 2.0
t dq ?
sum dd 0
.code

@Calcsin@4 proc
finit
fld qword ptr [ecx]
fsin
ret
@Calcsin@4 endp

@Calccos@4 proc
finit
fld qword ptr [ecx]
fcos
ret
@Calccos@4 endp


@Calcln@4 proc
finit
fldln2
fld qword ptr [ecx]
fyl2x
ret
@Calcln@4 endp



@Calcnumdiv@4 proc ;Number of dividers>0 of x from N(arithmetic function)  
finit
fld1
fld qword ptr [ecx]
fstp temp
mov sum,0

_lp:
fld qword ptr [ecx]
fprem
ftst
fstsw ax
sahf
je _zr
_back:
fstp t
fld1
faddp st(1),st(0)
fcom temp
fstsw ax
sahf
jbe  _lp
jmp _end
_zr:
inc sum
jmp _back
_end:
mov eax,sum
ret
@Calcnumdiv@4 endp

end