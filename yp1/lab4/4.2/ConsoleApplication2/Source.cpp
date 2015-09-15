#include<iostream>

using namespace std;

extern "C" double _fastcall Func();

int main()
{
	
	cout << Func() << endl;
	
	return 0;
}