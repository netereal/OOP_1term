#define _CRT_SECURE_NO_WARNINGS
#include <GL\glut.h>
#include <GL\freeglut.h>
#include <GL\glu.h>
#include <stdio.h>
#include <cmath>
using namespace std;

const int WindowX = 20, WindowY = 20;
const int WindowHeight = 650, WindowWidth = 1200;
int radius = 30;

bool fly = false;
float angle = 0;
int length = 30;
float G = 9.81;


class Circle
{
public:
	float x, y, r;
	float vx, vy;
	Circle() {};
	Circle(float _x, float _y, float(_r))
	{
		x = _x; y = _y; r = _r;
		vx = 0; vy = 0;
	}
	void Draw()
	{
		glBegin(GL_POINTS);
		int _x = 0, _y = r;
		int delta = 1 - 2 * r;
		int error = 0;
		while (_y >= 0)
		{
			glVertex2f(x + _x, y + _y);
			glVertex2f(x + _x, y - _y);
			glVertex2f(x - _x, y + _y);
			glVertex2f(x - _x, y - _y);
			error = 2 * (delta + _y) - 1;
			if ((delta < 0) && (error <= 0))
			{
				delta += 2 * ++_x + 1;
				continue;
			}
			error = 2 * (delta - _x) - 1;
			if ((delta > 0) && (error > 0))
			{
				delta += 1 - 2 * --_y;
				continue;
			}
			_x++;
			delta += 2 * (_x - _y);
			_y--;
		}
		glEnd();
	}
	void Update(float d_time) 
	{
		vy += -G*d_time;
		y += -G*d_time*d_time + vy*d_time;
		x += vx*d_time;
	}
};
Circle ball;

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glColor3f(0.0, 0.0, 0.0);
	
	glBegin(GL_LINE_STRIP);
	glVertex2f(-WindowWidth / 2, -WindowHeight / 2 + 20);
	glVertex2f(WindowWidth / 2, -WindowHeight / 2 + 20);
	glEnd();
	ball.Draw();

	if (!fly)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2f(ball.x, ball.y);
		glVertex2f(ball.x + length*cos(angle), ball.y + length*sin(angle));
		glEnd();
	}

	glutSwapBuffers();
}
void Timer(int)
{
	if (angle > 3.14 || angle < -3.14) angle = 0;
	if (fly) ball.Update(0.1);
	if (ball.y - ball.r < -WindowHeight / 2 + 20)
	{
		fly = false;
		ball = Circle(-WindowWidth / 2 + 50, -WindowHeight / 2 + 50, radius);
	}
	if (ball.x + ball.r > WindowWidth / 2) ball.x = WindowWidth / 2 - ball.r;
	if (ball.y + ball.r > WindowHeight / 2) ball.y = WindowHeight / 2 - ball.r;
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 0);
}
void Keyboard(unsigned char key, int x, int y)
{
	if (!fly)
	switch (key)
	{
	case 'a': angle += 0.1; break;
	case 'd': angle -= 0.1; break;
	case 's': length--; break;
	case 'w': length++; break;
	case 'f': fly = true; ball.vx = length*cos(angle); ball.vy = length*sin(angle);
	}
}
void Initialize()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WindowWidth / 2, WindowWidth / 2, -WindowHeight / 2, WindowHeight / 2);
	glMatrixMode(GL_MODELVIEW);
	ball = Circle(-WindowWidth / 2 + 50, -WindowHeight / 2 + 50, radius);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitWindowPosition(WindowX, WindowY);
	glutCreateWindow("Pushka!");

	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Draw);
	glutTimerFunc(50, Timer, 0);

	Initialize();
	glutMainLoop();
	return 0;
}
