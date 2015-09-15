#include<iostream>

using namespace std;

extern "C" double _fastcall Func(double*,double*);

int main()
{
	double accur = 0.0001;
	double x = 1, res;
	res = Func(&x, &accur);
	if (res == -1000)
		cout << "Don't converge!" << endl; //converge (-1,1]
	else
	    cout << res << endl;
	
	return 0;
}