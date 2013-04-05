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

int screenWidth1 = 400;
int screenHeight1 = 400;

int screenWidth2 = 400;
int screenHeight2 = 400;

int screenWidth3 = 400;
int screenHeight3 = 400;

int L1, L2, L3;                                       

int rotateAngle, yDisplacement, rotateAngle2, yDisplacement2;
float zoom, zoom2;                                           

Person *person;                                       //Object implementation of single person rendering
FontWriter *fontWriter;                               //Object that implements stroke font functionality

int personWindow, strokeFontWindow, openGLFontWindow; //Window ID for context switching

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

void reshapeOpenGLFont(int w, int h)
{
	//update screen dim
	screenWidth3 = w;
	screenHeight3 =h;

	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat aspect = (GLfloat) screenWidth3 / (GLfloat)screenHeight3;

	////setup worldwindow
	glMatrixMode(GL_PROJECTION);				
	glLoadIdentity();							

	glViewport(0,0,screenWidth2, screenHeight2);

	if(screenWidth2 <= screenHeight2)
		gluOrtho2D(-L3, L3, -L3/aspect, L3/aspect);
	else
		gluOrtho2D(-L3*aspect, L3*aspect, -L3, L3);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}//end reshapeOpenGLFont

void draw_string_stroke(void *font, const char* string)
{ 
	glPushMatrix();
		glTranslatef(-125,-50,0);
		while(*string)
			glutStrokeCharacter(font, *string++);
	glPopMatrix();
}//end draw_string_stroke

void displayOpenGLFont()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//Paint black background

	glViewport(0,0, screenWidth3, screenHeight3);

	glColor3f(1,1,1);
	glPushMatrix();
		glTranslatef(1, yDisplacement2, 1);
		glScalef(zoom2,zoom2,1);
		glRotatef(rotateAngle2,0,0,1);
		draw_string_stroke(GLUT_STROKE_ROMAN, "DDD");
	glPopMatrix();

	//Draw x-y axis for debugging purposes
	glColor3f(1,1,1);
	glBegin(GL_LINES);
		glVertex2i(0, -L3);
		glVertex2i(0, L3);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(-L3, 0);
		glVertex2i(L3, 0);
	glEnd();

	glutSwapBuffers();
}//end displayOpenGLFont()

void displayPerson()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//Paint black background

	//Person Screen on the left
	glViewport(0,0, screenWidth1, screenHeight1);
	drawPerson();
	
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

void keyboardOpenGLFont(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'q':
		//Rotate left
		rotateAngle2++;
		glutPostRedisplay();
		break;

	case 'e':
		//Rotate right
		rotateAngle2--;
		glutPostRedisplay();
		break;

	case 'w':
		//Move up
		yDisplacement2 += 2;
		glutPostRedisplay();
		break;

	case 's':
		//Move down
		yDisplacement2 -= 2;
		glutPostRedisplay();
		break;

	case 'a':
		//Zoom out
		zoom2 -= .1;
		glutPostRedisplay();
		break;

	case 'd':
		//Zoom in
		zoom2 += .1;
		glutPostRedisplay();
		break;

	case ' ':
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
	}
}//end keyboardOpenGLFont

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

	L1 = L2 = L3 = 450;

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
	glutInitWindowPosition(425,0);
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

	//Third window:
	glutInitWindowPosition(0,460);
	openGLFontWindow = glutCreateWindow("OpenGL Font");

	//Register Callbacks
	glutDisplayFunc(displayOpenGLFont);
	glutReshapeFunc(reshapeOpenGLFont);
	glutKeyboardFunc(keyboardOpenGLFont);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-L3, L3, -L3, L3);

	zoom2 = 1;
	rotateAngle2 = yDisplacement2 = 0;
}//end initialize


void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	initialize();//Initial setup

	glutMainLoop();

}//end main