#include <iostream>
using namespace std;

int main()
{
	int  _lin,_col;
	cout << "Number of lines:";
	cin >> _lin;
	cout << "Number of columnes:";
	cin >> _col;
	int* mat = new int[_lin*_col];
	cout << "Enter matrix: " << endl;
	for (int j = 0; j < _col*_lin; ++j)
		cin >> mat[j];
	__asm {
		mov ebx, mat
		mov ecx, _lin
		xor edx, edx
		mov eax, _col
		mul ecx
		cmp ecx,0
		je _end
		mov ecx,eax
	_begin_:
		not dword ptr [ebx]
		add ebx,4
		loop _begin_
		_end:
	};
	cout << endl;
	int c = 0;
	for (int j = 0; j < _col*_lin; j++)
	{
		cout << mat[j] << ' ';
		c++;
		if (c == _col)
		{
			c = 0;
			cout << endl;
		}
	}
	delete[] mat;
	return 0;
}