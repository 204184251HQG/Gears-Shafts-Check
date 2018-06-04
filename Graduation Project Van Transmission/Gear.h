#ifndef GEAR_H_
#define GEAR_H_

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <string>
using namespace std;
class Gear
{
public:
	Gear(string i,double mod,unsigned int tee,bool hel,double bey, double x=0):
		name(i),module(mod),z(tee),helical(hel),beyta(bey),ko(1.5),b(7 * mod), xigma(x){}
	Gear(string i,double mod, unsigned int tee, double x=0):
		name(i),module(mod), z(tee), helical(0), beyta(0),ko(1.65),b(7 * mod), xigma(x){}

	double bendstress();
	void outbendstress() { cout << name+" heli:"<<helical <<"  bendstress : " << bendstress() <<" Mpa"; }
	double contactstress(const Gear &mgear);
	void solveftfrfn(const Gear &mgear, double &ft, double &fr, double &fn)const;
	void outcontactstress(const Gear &mgear) { cout <<  "         contactstress : " << contactstress(mgear) << " Mpa" << endl; }
	void setparameters(double Tg, double Kf, double  Kc, double Y, int mate = 1) { tmax = Tg, kf = Kf, kc = Kc, y = Y; b = kc*module; mateid = mate; }

	string name;
	double module;
	unsigned int z;
	bool helical;
	double beyta;
	double xigma;
	double tmax;
	double elastic=206000;
	int mateid;

private:	
	double kc=8;
	double ko;
	double kf=1.1;
	double y=0.13;
	double b;
	Gear()=default;
};



double inv(const double &x);
double ainv(const double &x);
double get_xigma_a(double m, double z1, double z2, double xigema);
double get_xigma(double m, double z1, double z2, double xa);
float totalz(float b, float A, float m);
float solvebeyta(float z, float A, float m);
float optbeytan(float z1, float z2, float zl, float zh, float b);

#endif
