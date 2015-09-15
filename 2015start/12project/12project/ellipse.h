#pragma once 
#include<string>
#include<iostream>
#include<assert.h>
using namespace std;

class ellipse
{
protected:
	double a;
	double b;
	
public:
	ellipse();
	ellipse(double ,double);
	ellipse(const ellipse&);
	virtual ~ellipse(){};
	virtual double space()
	{
		return a*b*3.14159265;
	};
	virtual string equation()
	{
		return"x^2/a^2 + y^2/b^2 = 1";
	};
	
	friend istream& operator >> (istream&, ellipse&);
};