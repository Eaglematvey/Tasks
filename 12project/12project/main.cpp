#include<iostream>
#include"ellipse.h"
#include"circle.h"
using namespace std;

int main()
{
	ellipse * e[2];
	e[0] = new ellipse(3,3);
	e[1] = new circle(4);
	cout << e[0]->equation() << endl;
	cout << e[0]->space() << endl;
	cout << e[1]->equation() << endl;
	cout << e[1]->space() << endl;
	return 0;
}