#pragma once
#include"ellipse.h"

class circle: public ellipse
{
private:
	double r;
public:
	circle();
	circle(double);
	circle(const circle&);
	virtual ~circle(){};
	virtual double space()
	{
		return pow(r,2)*3.14159265;
	};
	virtual string equation()
	{
		return"x^2 + y^2 = r^2";
	};

	friend istream& operator >> (istream&, circle&);
};