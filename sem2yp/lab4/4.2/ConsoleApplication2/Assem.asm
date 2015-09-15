.586
.model flat 
option casemap:none 
.data 
k dq 1.0
temp4 dq 4.0
temp2 dq 2.0
temp1 dq 1.0
temp dq 1.0
sum dq 0.0
.code

@Func@0 proc
finit
         mov ecx,1000
	lp:
		fld k
		fmul k
		fmul temp4
		fsub temp1
		fmul k
		fstp temp
		fld temp1
		fdiv temp
		fld sum
		faddp st(1),st(0)
		fstp sum
		fld k
		fadd temp1
		fstp k
	loop lp
	fld sum
	fadd temp1
	fdiv temp2
ret
@Func@0 endp
end