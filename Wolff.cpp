#pragma once

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
const int N = 1000;//1e5

float T = 2.2;//0.001
float J = 1;
float H = 0;
bool S[X][Y];
int num_up = 0;
float scale = 7;
//float progress[100000];
vector<double> pp(N);


#define M_RATIO (float)num_up/total


void init() {
	srand(time(NULL));
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
		for (auto j : { -1, 1 }) {
			if (x + i < 0 || x + i >= X || y + j < 0 || y + j >= Y)
				continue;
			if (S[x][y] != S[x + i][y + j] && (float)rand() / RAND_MAX < exp(-2 * J / T)) {
				flip_wolff(x + i, y + j);
			}
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




int main0() {
	init();
	cout << num_up;
	for (int i = 0; i < N; i++) {
		flip_cluster();
		pp.at(i) = M_RATIO;
	}
	plt::plot(pp);
	plt::save("MC_W1.jpg");
}


int main()
{
	init();
	vector<double> Temperatures(500);
	vector<double> Ratios(500);
	//cout << "GOOD";
	T = 0.2;
	for (int i = 0; i < 50; i += 1) {

		mc_wolff(N);
		Temperatures.at(i) = T;
		Ratios.at(i) = M_RATIO;
		T += 0.1;
		cout << i;
	}
	plt::scatter(Temperatures, Ratios);
	plt::save("./W_M-T.png", 300);
	plt::show();

	return 0;
}
