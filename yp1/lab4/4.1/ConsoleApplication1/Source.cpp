#include<iostream>

using namespace std;
extern "C" double _fastcall Equat(double*);
extern "C" double _fastcall Func();
extern "C" int a;
extern "C" int b;
extern "C" int c;

int a = -3;
int b = 3; 
int c = -1;

int main()
{
	cout << "a:";
	cin >> a;
	cout << "b:";
	cin >> b;
	cout << "c:";
	cin >> c;
	cout<<"Result:" << Func() << endl;
	return 0;
}