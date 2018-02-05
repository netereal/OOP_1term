#include "Lab2Dll.h"
using namespace std;

void Draw()	// Функция, которая будет нам все рисовать 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	int x = 0, y = R;
	int delta = 1 - 2 * R;
	int error = 0;
	while (y >= 0)
	{
		glVertex2f(X1 + x, Y1 + y);
		glVertex2f(X1 + x, Y1 - y);
		glVertex2f(X1 - x, Y1 + y);
		glVertex2f(X1 - x, Y1 - y);
		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0))
		{
			delta += 2 * ++x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if ((delta > 0) && (error > 0))
		{
			delta += 1 - 2 * --y;
			continue;
		}
		x++;
		delta += 2 * (x - y);
		y--;
	}
	glEnd();
	glutSwapBuffers();
}
void Timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}
void Initialize()	// Функция, которая подготавливает экран 
{
	glClearColor(1.0, 1.0, 1.0, 1.0);	// Зарисовываем окно в белый 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WindowWidth / 2, WindowWidth / 2, -WindowHeight / 2, WindowHeight / 2);	// Задаем декартову систему координат для нашего окна
	glMatrixMode(GL_MODELVIEW);
}

void DrawCircle(int argc, char ** argv)
{
	glutInit(&argc, argv);	// Инициализируем библиотеку
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	// Иниализируем дисплей - то, как и чем будем выводить картинку. Параметры: простая неповижная картинка | использовать RGB
	glutInitWindowSize(WindowWidth, WindowHeight);	// Инициализируем размеры окна
	glutInitWindowPosition(WinX, WinY);
	glutCreateWindow("Lab 2");	// Создаем окно с заданным заголовком

	glutDisplayFunc(Draw);	// Регистрируем функцию Draw
	glutTimerFunc(50, Timer, 0);
	Initialize();
	glutMainLoop();	// Запускаем главный цикл программы
}
