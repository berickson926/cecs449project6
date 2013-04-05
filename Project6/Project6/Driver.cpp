#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/Glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>

#include "Person.h"
#include "FontWriter.h"

using namespace std;

int screenWidth = 500;
int screenHeight = 500;

int L = 450;

int rotateAngle, yDisplacement;
float zoom;

Person *person;
FontWriter *fontWriter;

void drawPerson()
{
	glColor3f(1,0,0);

	person->drawPerson();
	glFlush();

 }//end drawPerson

void drawText()
{
	glPushMatrix();
		glTranslatef(1, yDisplacement, 1);
		glScalef(zoom,zoom,1);
		glRotatef(rotateAngle,0,0,1);
		fontWriter->display();
	glPopMatrix();
}//End drawText

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

	glViewport(0,0,screenWidth, screenHeight);

	if(screenWidth <= screenHeight)
		gluOrtho2D(-L, L, -L/aspect, L/aspect);
	else
		gluOrtho2D(-L*aspect, L*aspect, -L, L);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}//end reshape

void display()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//Paint black background

	//Person Screen on the left
	glViewport(0,0, screenWidth, screenHeight);
	//drawPerson();

	//Text Screen on the right
	//glViewport(screenWidth/2, 0, screenWidth/2, screenHeight);
	drawText();

	//Draw x-y axis for debugging purposes
	glColor3f(1,1,1);
	glBegin(GL_LINES);
		glVertex2i(0, -L);
		glVertex2i(0, L);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(-L, 0);
		glVertex2i(L, 0);
	glEnd();
	
	glutSwapBuffers();
}//end display

void initialize()
{
	cout << "Keyboard commands: "<< endl;
	cout << "\t W = Translate up on Y-axis" << endl;
	cout << "\t S = Translate down on Y-Axis" << endl;
	cout << "\t Q = Rotate text counter clockwise" << endl;
	cout << "\t E = Rotate text clockwise" << endl;
	cout << "\t A = Zoom out " << endl;
	cout << "\t D = Zoom in " << endl;

	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("People & Fonts");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-L,L,-L,L);
	
	person = new Person();
	fontWriter = new FontWriter();

	zoom = 1;
	rotateAngle = yDisplacement = 0;
}//end initialize

void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'q':
		//Rotate left
		rotateAngle++;
		glutPostRedisplay();
		break;

	case 'e':
		//Rotate right
		rotateAngle--;
		glutPostRedisplay();
		break;

	case 'w':
		//Move up
		yDisplacement += 2;
		glutPostRedisplay();
		break;

	case 's':
		//Move down
		yDisplacement -= 2;
		glutPostRedisplay();
		break;

	case 'a':
		//Zoom out
		zoom -= .1;
		glutPostRedisplay();
		break;

	case 'd':
		//Zoom in
		zoom += .1;
		glutPostRedisplay();
		break;

	case ' ':
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
	}
}//end keyboard

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	initialize();//Initial setup

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

}//end main