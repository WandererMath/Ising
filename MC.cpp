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
const int initial = 3;
const int N = 100000;//1e6

float T = 2.2;//0.001
float J = 1;
float H = 0;
bool S[X][Y];
int num_up=0;
//float progress[100000];
vector<double> pp(N);


#define M_RATIO ((float)num_up/total-0.5)*2


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


int main0()
{
	init();
	vector<double> Temperatures(500);
	vector<double> Ratios(500);
	T = 0.03;
	for (int i=0; i < 500; i += 1) {
		cout << i;
		mc(N);
		Temperatures.at(i) = T;
		Ratios.at(i) = M_RATIO;
		T += 0.01;
	}
	plt::xlabel("Temperature");
	plt::ylabel("Magnetization per Spin");
	plt::scatter(Temperatures, Ratios);
	plt::save("D:/Results2/M-T.png", 300);
	plt::show();

	return 0;
}

int main() {
	init();
	T = 2.2;
	mc(N);
	plt::plot(pp);
	plt::xlabel("Simulation Steps");
	plt::ylabel("Magnetization per Spin");
	plt::title("T=2.2");
	plt::save("D:/Results2/MC22b.jpg", 300);
	return 0;
}

