.586
.model flat 
option casemap:none 
extern _a:dword
extern _b:dword
extern _c:dword
.data 
x dq ?
num dd ?
max dq -10.0
min dq 10.0
avge dq 0.0
temp2 dq 2.0
.code

@Equat@4 proc
finit
fld qword ptr [ecx]
fimul _b
fld qword ptr [ecx]
fmul qword ptr [ecx]
fimul _a
fld qword ptr [ecx]
fmul qword ptr [ecx]
fmul qword ptr [ecx]
faddp st(1),st(0)
faddp st(1),st(0)
fiadd _c
ret 
@Equat@4 endp

@Func@0 proc
finit
        mov ecx,100000
	lp:
	    mov num,ecx
		fld min 
		fld max
		faddp st(1),st(0)
		fdiv temp2
		fstp avge
		lea ecx, avge
		call @Equat@4
		fstp x
		lea ecx, min
		call @Equat@4
		fmul x
		ftst
		fstsw ax
	    sahf 
		jbe greater
		fld avge
		fstp min
		jmp met 
	greater:
	    fld avge
		fstp max
	met:
	 mov ecx,num
	loop lp
	fld avge
ret
@Func@0 endp
end
