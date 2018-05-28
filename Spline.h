#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <time.h>

using namespace std;

class Spline
{
	vector<float> a, b, c, d;
	vector<Object> obj;
public:
	Spline(vector<Object> ob);
	
};
