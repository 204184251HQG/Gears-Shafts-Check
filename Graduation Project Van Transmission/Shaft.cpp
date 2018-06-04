#include "stdafx.h"
#include "Gear.h"
#include "Shaft.h"

void Shaft::deflection_strength(const Gear &gear1, const Gear &gear2, float a)
{
	double ft = 0, fr = 0, fn = 0;
	double b = length - a;
	gear1.solveftfrfn(gear2, ft, fr, fn);
	double fc = fr*pow(a, 2)*pow(b, 2) / (3 * elastic*M_PI*pow(d, 4) / 64 * length);
	double fs = ft*pow(a, 2)*pow(b, 2) / (3 * elastic*M_PI*pow(d, 4) / 64 * length);
	double f = sqrt(fc*fc + fs*fs);
	double xig = fr*a*b*(b - a) / (3 * elastic*M_PI*pow(d, 4) / 64 * length);
	

	double Mc = fr*a*b / length;
	double Ms = ft*a*b / length;
	double Tn = gear1.tmax;
	double M = sqrt(Mc*Mc + Ms*Ms + Tn*Tn);
	double lvmda = 32 * M / M_PI / pow(d, 3);
	
	cout << id + " with " + gear1.name + " fc(mm): " << fc << "  fs(mm): " << fs << "  f(mm): " << f << "  ¦Ò(rad): " << xig << "  ¦Ò(Mpa): " << lvmda << endl;
}