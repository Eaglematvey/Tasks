#include<iostream>
#include"ellipse.h"
using namespace std;

int main()
{
	ellipse el(1,3);
	cout << el.equation() << endl;
	cout << el.space() << endl;
	return 0;
}