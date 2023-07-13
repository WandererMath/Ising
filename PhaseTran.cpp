#pragma once

#include <iostream>
#include <stdlib.h>
#include <list>
#include <time.h>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

const int X = 100;
const int Y = 100;
const int total = X * Y;
const int initial = 2;
const int N = 100000;

float T = 2.2;
float J = 1;
float H = 0;
bool S[X][Y];
int num_up = 0;
vector<float> U(1000);
float energy=0;


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
		energy += E;
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
	}
}

void wolff(int N=2000) {
	for (int i = 0; i < 2000; i++) {
		flip_cluster();
	}
}

int main1() {
	init();
	T = 0.5;
	mc(500000);
	energy = 0;
	int i = -1;

	fstream f("Results.txt", ios::out );
	while (T < 4) {
		T += 0.01;
		i += 1;

		mc(N);
		U.at(i) = energy;
		f << T << "\t" << energy << endl;

	}
	f.close();

	return 0;
}

int main() {
	init();
	T = 0.5;
	mc(500000);
	energy = 0;
	int i = -1;

	fstream f("Results.txt", ios::out);
	while (T < 4) {
		T += 0.01;
		i += 1;
		if (T >= 2.2 && T < 2.4)
			wolff();
		else
			mc(N);
		U.at(i) = energy;
		f << T << "\t" << energy << endl;

	}
	f.close();

	return 0;
}

