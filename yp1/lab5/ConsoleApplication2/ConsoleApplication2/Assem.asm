.586
.model flat 
option casemap:none
.data 
_x dq ?
_accur dq ?
_k dq 1.0
temp1 dq 1.0
tempm1 dq -1.0
tempmist dq -1000.0
sum dq 0.0
.code

@Func@8 proc
finit   
fld qword ptr[ecx]
fcom tempm1
	fstsw ax
	sahf
	jbe _mist

fcom temp1
	fstsw ax
	sahf
	ja _mist
fstp _x
fld qword ptr[edx]
fstp _accur
		fld1
	_lp:
		fmul _x
		fmul tempm1
		fld st(0)
		fdiv _k
		fld _k
		fld1
		faddp st(1),st(0)
		fstp _k
		fld sum
		fadd st(0),st(1)
		fstp sum
		fabs
	fcomp _accur
	fstsw ax
	sahf
	ja _lp
	fld sum
	jmp _end
	_mist:
	fld tempmist
_end:
ret
@Func@8 endp
end