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

int screenWidth1 = 500;
int screenHeight1 = 500;

int screenWidth2 = 500;
int screenHeight2 = 500;

int L1, L2;

int rotateAngle, yDisplacement;
float zoom;

Person *person;
FontWriter *fontWriter;

int personWindow, strokeFontWindow;

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

void reshapePerson(int w, int h)
{
	//update screen dim
	screenWidth1 = w;
	screenHeight1 =h;

	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat aspect = (GLfloat) screenWidth1 / (GLfloat)screenHeight1;

	////setup worldwindow
	glMatrixMode(GL_PROJECTION);				
	glLoadIdentity();							

	glViewport(0,0,screenWidth1, screenHeight1);

	if(screenWidth1 <= screenHeight1)
		gluOrtho2D(-L1, L1, -L1/aspect, L1/aspect);
	else
		gluOrtho2D(-L1*aspect, L1*aspect, -L1, L1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}//end reshapePerson

void reshapeStrokeFont(int w, int h)
{
	//update screen dim
	screenWidth2 = w;
	screenHeight2 =h;

	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat aspect = (GLfloat) screenWidth2 / (GLfloat)screenHeight2;

	////setup worldwindow
	glMatrixMode(GL_PROJECTION);				
	glLoadIdentity();							

	glViewport(0,0,screenWidth2, screenHeight2);

	if(screenWidth2 <= screenHeight2)
		gluOrtho2D(-L2, L2, -L2/aspect, L2/aspect);
	else
		gluOrtho2D(-L2*aspect, L2*aspect, -L2, L2);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}//end reshapeStrokeFont

void displayPerson()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//Paint black background

	//Person Screen on the left
	glViewport(0,0, screenWidth1, screenHeight1);
	drawPerson();

	////Draw x-y axis for debugging purposes
	//glColor3f(1,1,1);
	//glBegin(GL_LINES);
	//	glVertex2i(0, -L1);
	//	glVertex2i(0, L1);
	//glEnd();

	//glBegin(GL_LINES);
	//	glVertex2i(-L1, 0);
	//	glVertex2i(L1, 0);
	//glEnd();
	
	glutSwapBuffers();
}//end displayPerson

void displayText()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//Paint black background

	//Person Screen on the left
	glViewport(0,0, screenWidth2, screenHeight2);
	drawText();
	
	glutSwapBuffers();
}//end displayText

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

//Pre: glutInit & glutInitDisplayMode must be called prior to execution
//Post:
void initialize()
{
	cout << "Keyboard commands: "<< endl;
	cout << "\t W = Translate up on Y-axis" << endl;
	cout << "\t S = Translate down on Y-Axis" << endl;
	cout << "\t Q = Rotate text counter clockwise" << endl;
	cout << "\t E = Rotate text clockwise" << endl;
	cout << "\t A = Zoom out " << endl;
	cout << "\t D = Zoom in " << endl;

	L1 = L2 = 450;

	glutInitWindowSize(screenWidth1, screenHeight1);
	//Create Two Windows, one for the Person the other for stroke font

	//First Window:
	personWindow = glutCreateWindow("People");
	glutInitWindowPosition(50, 50);
	//Register callbacks
	glutDisplayFunc(displayPerson);
	glutReshapeFunc(reshapePerson);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-L1,L1,-L1,L1);

	person = new Person();

	//Second Window:
	glutInitWindowPosition(600,0);
	strokeFontWindow = glutCreateWindow("Stroke Font");
	
	//Register Callbacks
	glutDisplayFunc(displayText);
	glutReshapeFunc(reshapeStrokeFont);
	glutKeyboardFunc(keyboard);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-L2,L2,-L2,L2);

	fontWriter = new FontWriter();

	zoom = 1;
	rotateAngle = yDisplacement = 0;
}//end initialize


void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	initialize();//Initial setup

	glutMainLoop();

}//end main