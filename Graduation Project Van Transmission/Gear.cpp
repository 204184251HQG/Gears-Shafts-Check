#include "stdafx.h"
#include "Gear.h"


double Gear::bendstress()
{
	double bs;
	if(helical)
		bs = 2 * tmax*cos(beyta*M_PI/180)*ko / 3.1415926 / pow(module, 3) / z / kc / y/ 2.0;
	else
		bs = 2 * tmax*ko*kf / 3.1415926 / pow(module, 3) / z / kc / y;
	return bs;
}
double Gear::contactstress(const Gear &mgear)
{
	double alfa = 20.0 * M_PI / 180;
	double a = module*(z + mgear.z) / 2;
	double xalfa = ainv(2 * (xigma+mgear.xigma)*tan(alfa) / (z + mgear.z) + inv(alfa));
	double bey = beyta*M_PI / 180.0;
	double F = 2 * tmax / (module*z)/(cos(xalfa)*cos(bey));
	double rz = kf == 1.1 ? module*z / cos(bey) / 2 : module*mgear.z / cos(bey) / 2;
	double rb = !(kf == 1.1) ? module*z / cos(bey) / 2 : module*mgear.z / cos(bey) / 2;
	double roz = rz*sin(xalfa) / pow(cos(bey), 2);
	double rob = rb*sin(xalfa) / pow(cos(bey), 2);
	double cs = 0.418*sqrt(F*elastic/b*(1/roz+1/rob));
	return cs;
}
void Gear::solveftfrfn(const Gear &mgear, double &ft, double &fr, double &fn)const
{
	double alfa = 20.0 * M_PI / 180;
	double a = module*(z + mgear.z) / 2;
	double xalfa = ainv(2 * (xigma + mgear.xigma)*tan(alfa) / (z + mgear.z) + inv(alfa));
	double bey = beyta*M_PI / 180.0;
	ft = 2 * tmax / (module*z/ cos(bey));
	fr = ft*tan(xalfa) / cos(bey);
	fn = ft / (cos(xalfa)*cos(bey));
}

double inv(const double &x)
{
	return tan(x) - x;
}

double ainv(const double &x)
{
	double min = 0, max = M_PI / 2, y = (min + max) / 2;
	while (abs(inv(y) - x)>0.000000001)
	{
		y = (min + max) / 2;
		if (inv(y) > x)
			max = y;
		else
			min = y;
	}
	return y;
}

double get_xigma_a(double m, double z1, double z2, double xigma)
{
	double alfa = 20.0 * M_PI / 180;
	double a = m*(z1 + z2) / 2;
	double xalfa = ainv(2 * xigma*tan(alfa) / (z1 + z2) + inv(alfa));
	double xa = a*cos(alfa) / cos(xalfa);
	return xa;
}

double get_xigma(double m, double z1, double z2, double xa)
{
	double alfa = 20.0 * M_PI / 180;
	double a = m*(z1 + z2) / 2;
	double xalfa = acos(a*cos(alfa) / xa);
	double xigma = (z1 + z2)*(inv(xalfa) - inv(alfa)) / 2 / tan(alfa);
	return xigma;
}
float totalz(float b, float A, float m)
{
	return A * 2 * cos(b*M_PI / 180) / m;
}
float solvebeyta(float z, float A, float m)
{
	return acos(m*z / 2.0 / A) * 180 / M_PI;
}
float optbeytan(float z1, float z2, float zl, float zh, float b)
{
	float n = z2 / (z1 + z2)*(1 + zh / zl);
	return atan(tan(b*M_PI / 180) / n) * 180 / M_PI;
}