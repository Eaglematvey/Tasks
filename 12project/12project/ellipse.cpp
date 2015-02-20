#include"ellipse.h"
#include<iostream>
ellipse::ellipse()
{
	a = 2; b = 2;
}
ellipse::ellipse(double aval, double bval)
{
	a = aval;
	b = bval;
}

istream& operator >> (istream& is, ellipse& el)
{
	double a, b;
	 is >> a;
	 is >> b;
	 el = ellipse(a, b);
     return is;
}
