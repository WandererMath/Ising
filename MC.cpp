#pragma once

#include <iostream>
#include <stdlib.h>
#include <list>
#include <time.h>
#include <cmath>
#include <vector>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;

const int X = 100;
const int Y = 100;
const int total = X * Y;
const int initial = 2;
const int N = 50000;//1e6

float T = 2.2;//0.001
float J = 1;
float H = 0;
bool S[X][Y];
int num_up=0;
//float progress[100000];
vector<double> pp(N);


#define M_RATIO (float)num_up/total


void init() {
	srand(time(NULL));
	for (int i=0; i < X; i++) {
		for (int j=0; j < Y; j++) {
			S[i][j] = rand() % initial;
			if (S[i][j])
				num_up += 1;
		}
	}
}

float dE(int i, int j) {
	float sum = 0;
	for (auto m : { -1, 1 }) {
		for (auto n : { -1, 1 }) {
			if (i + m < 0 || i + m >= X || j + n < 0 || j + n >= Y)
				continue;
			if (S[i + m][j + n] == S[i][j]) {
				sum += 2 * J;
			}
			else {
				sum -= 2 * J;
			}
		}
	}
	return sum;
}

void flip() {
	int x, y;
	float E;
	x = rand() % X;
	y = rand() % Y;
	E = dE(x, y);
	if (E < 0|| (float)rand() / RAND_MAX < exp(- E/T)) {
		S[x][y] = !S[x][y];
		if (S[x][y])
			num_up += 1;
		else
			num_up -= 1;
	}
}

void mc(int N) {
	for (int i = 0; i < N; i++) {
		flip();
		//progress[i] = M_RATIO;
		//cout << num_up<< endl;
		pp.at(i)=(M_RATIO);
	}
}


int main2()
{
	init();
	vector<double> Temperatures(500);
	vector<double> Ratios(500);
	//cout << "GOOD";
	for (int i=0; i < 500; i += 1) {

		mc(N);
		Temperatures.at(i) = T;
		Ratios.at(i) = M_RATIO;
		T += 0.01;
	}
	plt::scatter(Temperatures, Ratios);
	plt::save("./M-T.png", 300);
	plt::show();

	return 0;
}

int main() {
	init();
	mc(N);
	plt::plot(pp);
	plt::save("MC3.jpg");
	return 0;
}


int main_test()
{
	// Prepare data.
	int n = 5000;
	std::vector<double> x(n), y(n), z(n), w(n, 2);
	for (int i = 0; i < n; ++i) {
		x.at(i) = i * i;
		y.at(i) = sin(2 * 3.14 * i / 360.0);
		z.at(i) = log(i);
	}

	// Set the size of output image to 1200x780 pixels
	plt::figure_size(1200, 780);
	// Plot line from given x and y data. Color is selected automatically.
	plt::plot(x, y);
	// Plot a red dashed line from given x and y data.
	plt::plot(x, w, "r--");
	// Plot a line whose name will show up as "log(x)" in the legend.
	plt::named_plot("log(x)", x, z);
	// Set x-axis to interval [0,1000000]
	plt::xlim(0, 1000 * 1000);
	// Add graph title
	plt::title("Sample figure");
	// Enable legend.
	plt::legend();
	// Save the image (file format is determined by the extension)
	plt::show();
	plt::save("./basic.png");
	return 0;
}

