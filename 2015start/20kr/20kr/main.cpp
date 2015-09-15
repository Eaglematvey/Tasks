#include<iostream>

using namespace std;

int quater(int x, int y)
{
	int quat=1;
	_asm{
		cmp x,0
		jge m14q

		cmp y, 0
		jge m2q
		mov quat,3
		jmp _end
	m2q:
		mov quat,2
		jmp _end
	m14q:
		cmp y,0
		jge m1q
		mov quat,4
		jmp _end
	m1q:
	    mov quat,1
		_end:
	}
	return quat;
}
struct complex
{
	int cre;
	int cim;
};
struct doublecom
{
	double r;
	double fi;
};
doublecom trigcoml;
complex Cnum;
void subcompl(int re1, int im1,int re2,int im2)
{
	int resre =0,resim = 0;
	_asm{
		mov eax, re1
			mov ebx, im1
			sub eax, re2
			sub ebx, im2
			mov resre, eax
			mov resim, ebx
	}
	Cnum.cre = resre;
	Cnum.cim = resim;
}

void trigform(double re, double im)
{
	double resr = 0, resfi = 0;
	_asm{
		finit
		fld re
		fld im
		fpatan
		fstp resfi
		fld re
		fmul st(0), st(0)
		fld im
		fmul st(0), st(0)
		faddp st(1), st(0)
		fsqrt
		fstp resr
	}
	trigcoml.r = resr;
	trigcoml.fi = resfi;
}
int arr1[1000], arr2[1000], arrmul[1000];
int* matrmul()//(int* arr1, int* arr2, int* arrmul, int n)
{
	_asm
	{
		xor edx,edx
		mov eax,arr1[0] 
		mov ebx, arr2[0]
		mul ebx
		add arrmul[0],eax
		xor edx,edx
		mov eax, arr1[4]
		mov ebx, arr2[8]
		mul ebx
		add arrmul[0], eax
		xor edx,edx
		mov eax, arr1[0]
		mov ebx, arr2[4]
		mul ebx
		add arrmul[4], eax
		xor edx,edx
		mov eax, arr1[4]
		mov ebx, arr2[12]
		mul ebx
		add arrmul[4], eax
		xor edx, edx
		mov eax, arr1[8]
		mov ebx, arr2[0]
		mul ebx
		add arrmul[8], eax
		xor edx, edx
		mov eax, arr1[12]
		mov ebx, arr2[4]
		mul ebx
		add arrmul[8], eax
		xor edx, edx
		mov eax, arr1[8]
		mov ebx, arr2[4]
		mul ebx
		add arrmul[12], eax
		xor edx, edx
		mov eax, arr1[12]
		mov ebx, arr2[12]
		mul ebx
		add arrmul[12], eax
	}
	return arrmul;
}
int main()
{
	int x = 1, y = -1, quat, // 1st
		temp = 0;

	int re1=2, im1 =1 , re2 =-1, im2 =2; //2nd
	double  cre1 = 1.2, cre2 = 2.1; // 3rd
	int n = 2;
	
	for (int i = 0; i < n*n; i++)
	{
		arr1[i] = 2;
		arr2[i] = 3;
		arrmul[i] = 0;
	}
	_asm
	{
		push y
	    push x
		call quater
		pop ebx 
		pop ebx
		mov quat,eax
		mov temp,esp
		push im2
		push re2
		push im1
		push re1
		call subcompl
		mov esp,temp

    }
	trigform(cre1, cre2);
	//matrmul(arr1, arr2, arrmul, n);
	matrmul();
	cout <<"1st:"<< quat << endl;
	cout << "2nd:" << endl<< Cnum.cre << endl << Cnum.cim << endl;
	cout << "3rd:" << endl << trigcoml.r <<endl<< trigcoml.fi << endl;
	cout << "4th:" << endl;
	for (int i = 0; i < 4; i++)
		cout << arrmul[i] << endl;
	return 0;
}