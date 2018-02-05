#pragma once
#include <iostream> 
#include <GL\glut.h>
using namespace std;

const int WinX = 10, WinY = 10;
const int WindowWidth = 700, WindowHeight = 500;
int X1 = 0, Y1 = 0, R = 100;

void Draw();
void Timer(int);
void Initialize();
__declspec(dllexport) void DrawCircle(int argc, char ** argv);

