// Graduation Project Van Transmission.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include "stdafx.h"
#include "Gear.h"
#include "Shaft.h"
#define _USE_MATH_DEFINES
#include <math.h>
 //"D:\\VS\\C++proj\\Graduation Project\\Graduation Project Van Transmission"
using namespace std;



int main()
{
	cout << "变速器齿轮与轴校核程序" << endl;
	string data = "geardata.txt";
	fstream geardata;
	geardata.open(data);
	if (!geardata)
	{
		cerr << "open file err" << endl;
		cout << "press any key to exit" << endl;
		return getchar();
	}
	cout << "齿轮校核：" << endl;
	int gearnumbers,shaftnumbers;
	vector<Gear> gears;
	vector<Shaft> shafts;
	string temp,word;
	getline(geardata, temp);
	getline(geardata, temp);
	istringstream firstline(temp);
	firstline >> word;
	if (word != "Gears_numbers")
	{
		cerr << "Gear_numbers err" << endl;
		cout << "press any key to exit" << endl;
		return getchar();
	}
	firstline >> word; gearnumbers = stoi(word);
	cout << "Gears_numbers:"<< gearnumbers << endl;
	getline(geardata, temp);
	for (int i = 0; i < gearnumbers; i++)
	{
		getline(geardata, temp);
		istringstream gear(temp);
		vector<string> vs;
		while (gear >> word)
			vs.push_back(word);
		if (vs.size() != 11)
		{
			cerr << "Gear "<<i+1<<" parameter numbers err" << endl;
			cout << "press any key to exit" << endl;
			return getchar();
		}
		Gear geartemp(vs[0].c_str(), stoi(vs[2]), stoi(vs[3]), (bool)stoi(vs[1]), stod(vs[4]), stod(vs[5]));
		geartemp.setparameters(stod(vs[9]), stod(vs[7]), stod(vs[6]), stod(vs[8]), stoi(vs[10]));
		gears.push_back(geartemp);
	}

	for (int i = 0; i < gearnumbers; i++)
	{
		gears[i].outbendstress(); gears[i].outcontactstress(gears[gears[i].mateid - 1]);
	}
	cout << "\n轴校核：" << endl;
	while (getline(geardata, temp))
	{
		firstline.clear(); firstline.str(temp);
		firstline >> word;
		if (word == "Shaft_numbers")
			break;
	}
	if (geardata.fail())
	{
		cerr << "\nend of the file" << endl;
		cout << "press any key to exit" << endl;
		return getchar();
	}

	firstline >> word; shaftnumbers = stoi(word);
	cout << "Shaft_numbers:" << shaftnumbers << endl;
	getline(geardata, temp);
	for (int i = 0; i < shaftnumbers; i++)
	{
		getline(geardata, temp);
		istringstream shaft(temp);
		vector<string> vs;
		while (shaft >> word)
			vs.push_back(word);
		if ((vs.size() < 3)|| (vs.size()%2==0))
		{
			cerr << "Shaft " << i + 1 << " parameter numbers err" << endl;
			cout << "press any key to exit" << endl;
			return getchar();
		}
		Shaft shafttemp(vs[0], stod(vs[1]), stod(vs[2]));
		for (int j = 3; j <= vs.size() - 2; j += 2)
		{
			shafttemp.deflection_strength(gears[stod(vs[j])-1], gears[gears[stod(vs[j])-1].mateid - 1], stod(vs[j+1]));
		}
		cout << "\n" << endl;
	}

	cout << "xig a:"<<get_xigma_a(5, 13, 21, 0.75+0.25)<< endl;

	cout << "\nmade by 黄祺垄 and press any key to exit" << endl;
    return getchar();
}

