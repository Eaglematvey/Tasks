#include<iostream>

using namespace std;

int main()
{
	int temp1 = 2,
		pow_of_x = 0,
		j = 1,
		n = 1;
	long long m = 4;
	long double res = 0,
		x = 1.2;
	cout << "Enter m:" << endl;
	cin >> m;
	cout << "Enter n:" << endl;
	cin >> n;
	cout << "Enter x:" << endl;
	cin >> x;
	_asm{
	
		finit
		fild m
		fimul temp1
		dec temp1
		fiadd temp1
		fild m
		fiadd temp1
		fild m
		fmulp st(1), st(0)
		fmulp st(1), st(0)
		add temp1,5
		fidiv temp1
		fldz
		fld1
		fld1
	    fxch st(3)
		mov ecx,n
		cmp ecx, 0
		je progend
		; ---------------------------------------
		; top = m*(m + 1)(2 * m + 1) / 6; --st(0)
		; temp_x -- st(1)
		; bottom -- st(2)
		; result  -- st(3)
		; --------------------------------------
	cycle:
		fild m
		fiadd j
		fmul st(0), st(0)
		faddp st(1), st(0)
		
		fxch st(1)
		fmul x
		inc pow_of_x
		fld st(0)
		fimul pow_of_x
		fimul pow_of_x
		fimul pow_of_x
		faddp st(3), st(0)
		fmul x
		inc pow_of_x
		fld st(0)
		fimul pow_of_x
		fimul pow_of_x
		fimul pow_of_x
		faddp st(3), st(0)

		fxch st(1)
		fld st(0)
		fdiv st(0),st(3)
		fmulp st(4), st(0)
		inc j
		loop cycle

		fxch st(3)
		fst res
		progend:
	}
	cout << res << endl;
	return 0;
}