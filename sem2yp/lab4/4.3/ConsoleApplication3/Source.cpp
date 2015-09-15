#include<iostream>

using namespace std;

extern "C" double _fastcall Func();
extern "C" double _fastcall IntegFunc(double*);

int main()
{
	
	cout << Func() << endl;

	return 0;
}