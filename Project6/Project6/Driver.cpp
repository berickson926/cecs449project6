#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/Glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>

#include "Person.h"

using namespace std;

#define PI 3.14159265

int screenWidth = 500;
int screenHeight = 500;
int lineWidth = 2;
int radius = 220;
int L = 250;

Person *person = new Person();

void drawPerson()
{
	glColor3f(1,0,0);
	
	
	person->drawPerson();
	glFlush();

 }//end drawPerson

void drawText()
{
	
}//End DrawText

void reshape(int w, int h)
{
	//update screen dim
	screenWidth = w;
	screenHeight =h;

	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat aspect = (GLfloat) screenWidth / (GLfloat)screenHeight;

	////setup worldwindow
	glMatrixMode(GL_PROJECTION);				
	glLoadIdentity();							

	//glViewport(0,0,screenWidth, screenHeight);

	if(screenWidth <= screenHeight)
		gluOrtho2D(-L, L, -L/aspect, L/aspect);
	else
		gluOrtho2D(-L*aspect, L*aspect, -L, L);
	
	glutPostRedisplay();
}//end reshape

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//Paint black background

	//Person Screen on the left
	glViewport(0,0, screenWidth, screenHeight);
	drawPerson();

	//Text Screen on the right
	//glViewport(screenWidth/2, 0, screenWidth/2, screenHeight);
	//drawText();

	glutSwapBuffers();

}//end display

void initializeWindow()
{
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("People & Fonts");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-L,L,-L,L);
	
}//end initialize

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	initializeWindow();//Initial setup of clipping & screen windows

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	//glutIdleFunc(timeUpdate);//Check for a new time and redraw

	glutMainLoop();

}//end main