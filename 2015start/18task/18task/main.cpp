#include<iostream>//����� ����� ��������� ���� ����������� ����� �� 1 �� ��������� �����.

using namespace std;

int main()
{
	int num;
	long long res = 0;
	cin >> num;
	_asm
	{
		cmp num, 0
			jle met
			mov ecx, num
		lp :
		mov eax, ecx
			mul eax
			add dword ptr res, eax
			adc dword ptr res + 4, edx
			loop lp

		met :
	}
	cout << res << endl;
	return 0;
}