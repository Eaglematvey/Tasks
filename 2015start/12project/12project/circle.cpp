#include"circle.h"
#include<iostream>
circle::circle()
{
	a = 1; b = 1; r = 2;
}
circle::circle(double rval)
{
	a = 1;
	b = 1;
	r = rval;
}

istream& operator >> (istream& is, circle& cl)
{
	double r;
	is >> r;
	cl = circle(r);
	return is;
}
