#pragma once

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
 int initial = 2;
const int N = 100000;//1e6

float T = 1;//0.001
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
	for (auto m : { -1,0, 1 }) {
		for (auto n : { -1,0, 1 }) {
			if (i + m < 0 || i + m >= X || j + n < 0 || j + n >= Y|| ( ((bool)m| (bool)n)==0 || ((bool)m & (bool)n)!=0))
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

void mc(int N) {
	for (int i = 0; i < N; i++) {
		flip();
		pp.at(i) = (M_RATIO);

	}
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	flip();
	glColor3f(0, 0, 1);
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (S[i][j]) {
				
				glRecti(scale* i, scale * j, scale * i + scale, scale * j + scale);
			}
		}
	}
	glutSwapBuffers();
}

void timer(int value) {


	glutPostRedisplay();
	glutTimerFunc(1, timer, 0);
}

int main(int argc, char** argv)
{
	init();
	cout << "T:";
	cin >> T;
	cout << "Init: ";
	cin >> initial;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(scale * 100, scale * 100);
	glutCreateWindow("MC");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, scale*100, 0, scale*100, -1, 1);

	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
	return 0;
}




