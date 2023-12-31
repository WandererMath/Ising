#pragma once
#pragma comment(linker, "/STACK:8000000")

#include <iostream>
#include <stdlib.h>
#include <list>
#include <time.h>
#include <cmath>
#include <vector>
#include <GL/glut.h>
using namespace std;

const int X = 100;
const int Y = 100;
const int total = X * Y;
const int initial = 2;
const int N = 100000;//1e6

float T = 2.4;//0.001
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
	S[x][y] = !S[x][y];
	for (auto i : { -1, 1 }) {
		if (x + i < 0 || x + i >= X)
			continue;
		if (S[x][y] != S[x + i][y]  && (float)rand() / RAND_MAX <1- exp(-2 * J / T)) {
			flip_wolff(x + i, y);
		}
	}
	for (auto i : { -1, 1 }) {
		if (y + i < 0 || y + i >= X)
			continue;
		if (S[x][y] != S[x][y+i] && (float)rand() / RAND_MAX < 1-exp(-2 * J / T)) {
			flip_wolff(x, y+i);
		}
	}
}

void flip_cluster() {
	int x = rand() % X;
	int y = rand() % Y;
	flip_wolff(x, y);
}

void mc(int N) {
	for (int i = 0; i < N; i++) {
		flip_cluster();
		pp.at(i) = (M_RATIO);

	}
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	flip_cluster();
	glColor3f(0, 0, 1);
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (S[i][j]) {

				glRecti(scale * i, scale * j, scale * i + scale, scale * j + scale);
			}
		}
	}
	glutSwapBuffers();
}

void timer(int value) {


	glutPostRedisplay();
	glutTimerFunc(50, timer, 0);
}

int main(int argc, char** argv)
{
	init();
	cin >> T;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(scale * 100, scale * 100);
	glutCreateWindow("Wolff");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, scale * 100, 0, scale * 100, -1, 1);

	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
	return 0;
}




