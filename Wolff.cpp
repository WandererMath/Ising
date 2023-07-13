#pragma once
#pragma comment(linker, "/STACK:8000000")

#include <iostream>
#include <stdlib.h>
#include <list>
#include <time.h>
#include <cmath>
#include <vector>
#include <GL/glut.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;

const int X = 100;
const int Y = 100;
const int total = X * Y;
const int initial = 3;
const int N = 1000000;

float T = 2.3;
float J = 1;
float H = 0;
bool S[X][Y];
int num_up = 0;
vector<double> pp(N);
vector<double> pv(N);

#define M_RATIO ((float)num_up/total-0.5)*2

float absolute(float a) {
	if (a > 0)
		return a;
	return -a;
}
void init() {
	srand(time(NULL));
	num_up = 0;
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
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
	if (E < 0 || (float)rand() / RAND_MAX < exp(-E / T)) {
		S[x][y] = !S[x][y];
		if (S[x][y])
			num_up += 1;
		else
			num_up -= 1;
	}
}

void flip_wolff(int x, int y) {
	if (S[x][y])
		num_up -= 1;
	else
		num_up += 1;
	S[x][y] = !S[x][y];
	for (auto i : { -1, 1 }) {
		if (x + i < 0 || x + i >= X)
			continue;
		if (S[x][y] != S[x + i][y] /*) {//*/ && (float)rand() / RAND_MAX < 1 - exp(-2 * J / T)) {
			flip_wolff(x + i, y);
		}
	}
	for (auto i : { -1, 1 }) {
		if (y + i < 0 || y + i >= Y)
			continue;
		if (S[x][y] != S[x][y + i] /*) {//*/ && (float)rand() / RAND_MAX < 1 - exp(-2 * J / T)) {
			flip_wolff(x, y + i);
		}
	}
}
void flip_cluster() {
	int x = rand() % X;
	int y = rand() % Y;
	flip_wolff(x, y);
}

void mc_wolff(int N) {
	for (int i = 0; i < N; i++) {
		flip_cluster();
		pp.at(i) = (M_RATIO);
	}
}
void mc(int N) {
	for (int i = 0; i < N; i++) {
		flip();
		pv.at(i) = M_RATIO;
		//cout << M_RATIO<<endl;
	}
	
}



int main() {
	cout << "GOOD";
	init();
	T = 1;/*
	for (int i = 0; i < N; i++) {
		//cout << "OK";
		flip_cluster();
		pp.at(i) = M_RATIO;
	}*/
	//plt::named_plot( "Wolff", pp);
	//cout << "Nice";
	init();
	mc(N);
	plt::named_plot("Non-Wolff", pv);
	//plt::legend();
	plt::xlabel("Simulation Steps");
	plt::ylabel("Magnetization per Spin");
	plt::title("T=1 Non-Wolff");
	plt::save("D:/Tasks/CMS/R1/P6.jpg", 300);
	plt::show();
	return 0;
}


int main2()
{
	init();
	vector<double> Temperatures(500);
	vector<double> Ratios(500);
	T = 0.03;
	for (int i = 0; i < 500; i += 1) {
		
		if (T > 2.2 && T < 2.4) {
			for (int i = 0; i < 2000; i++) {
				flip_cluster();
			}
			cout << i;
		}
		else {
			mc(N);
		}
		Temperatures.at(i) = T;
		Ratios.at(i) = absolute(M_RATIO);
		T += 0.01;
	}
	plt::xlabel("Temperature");
	plt::ylabel("Magnetization per Spin");
	plt::scatter(Temperatures, Ratios);
	plt::save("D:/Tasks/R1/P1.jpg", 300);
	plt::show();

	return 0;
}
