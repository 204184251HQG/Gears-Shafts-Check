#ifndef SHAFT_H_
#define SHAFT_H_
#include "stdafx.h"
#include "Gear.h"
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
class Shaft
{
public:
	Shaft(string i,double D,double L):id(i),d(D), length(L) {}
	void deflection_strength(const Gear &gear1, const Gear &gear2, float a);

	string id;
	double d;
	double length;
	double elastic = 210000;
private:
	Shaft() = default;
};



#endif


