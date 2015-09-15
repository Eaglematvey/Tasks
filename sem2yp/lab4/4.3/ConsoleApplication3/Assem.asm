.586
.model flat 
option casemap:none 
.data 
temp2 dq 2.0
step dq 0.000001
min dq 0.00000
max dq 0.000001
sum dq 0.000000
twopi dq ?
temp dq ?
.code

@IntegFunc@4 proc
finit
fld qword ptr [ecx]
fmul qword ptr [ecx]
fld  qword ptr [ecx]
fsin
faddp st(1),st(0)
ret
@IntegFunc@4 endp

@Func@0 proc
finit
fldpi
fmul temp2
fstp twopi
lea ecx, twopi
call @IntegFunc@4
fstp temp
lea ecx,min
call @IntegFunc@4
fadd temp
fld sum 
faddp st(1),st(0)
fdiv temp2
fstp sum
lp:

lea ecx, max
call @IntegFunc@4
fld sum
faddp st(1),st(0)
fstp sum
fadd step
fld max
fadd step
fst max
fcomp twopi
fstsw ax
sahf
jb lp
fld sum
fmul step
ret
@Func@0 endp

end