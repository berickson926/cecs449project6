/*
	CECS 449 Project 6
	Author: Bret Erickson
	Due: 4/8/13
	Description: Application peforms three modelling procedures. One window is created for each model.
		
	1. 2D model of a 'person'
	2. Modelling of a custom stroke font with sample text that user can manipulate with keyboard input (rotate, move up/down, zoom in/out)
	3. Modelling of predefined opengl font with sample text. User can minipulate with 2D transformations as model No. but independently in its own window.

	Requires class files FontWriter & Person

	TODO: refactor redundant keyboard and resize callbacks
 */


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

//window variables
int screenWidth1 = 400;
int screenHeight1 = 400;

int screenWidth2 = 400;
int screenHeight2 = 400;

int screenWidth3 = 400;
int screenHeight3 = 400;

int L1, L2, L3;  //TODO: int[] here?                                     

int personWindow, strokeFontWindow, openGLFontWindow; //Window ID for context switching

//2D transformation variables
//TODO: more meaningful variables
int rotateAngle, yDisplacement, rotateAngle2, yDisplacement2;
float zoom, zoom2;                                           

//Class object references
Person *person;                                       //Object implementation of single person rendering
FontWriter *fontWriter;                               //Object that implements stroke font functionality

//Pre:None
//Post:Draws
void drawPerson()
{
	glColor3f(1,0,0);
	person->drawPerson();
	glFlush();

 }//end drawPerson

//Pre:ydisplacement, zoom, rotateAngle are not null
//Post: calls fontWriter's display method and performs the following 2Dtransformations
//		translate based on yDisplacement
//		scale based on zoom
//		rotate based on rotateAngle
void drawText()
{
	glPushMatrix();
		glTranslatef(1, yDisplacement, 1);
		glScalef(zoom,zoom,1);
		glRotatef(rotateAngle,0,0,1);
		fontWriter->display();
	glPopMatrix();
}//End drawText

//Pre: integers screen width w, screen height h
//Post: update new screenWidth, screenHeight for window 1 (person)
//		reset color bit
//		calc aspect ratio and resize clipping window/viewport to remove distortion
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

//Pre: integers screen width w, screen height h
//Post: update new screenWidth, screenHeight for window 2 (strokeFont)
//		reset color bit
//		calc aspect ratio and resize clipping window/viewport to remove distortion
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

//Pre: integers screen width w, screen height h
//Post: update new screenWidth, screenHeight for window 3 (OpenglFont)
//		reset color bit
//		calc aspect ratio and resize clipping window/viewport to remove distortion
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

//Pre: font const, string constant
//Post: Writes one character from the string at a time, using the defined font to decide how to draw the characters.
//		**hardcoded translation used to center expected output of "DDD"
void draw_string_stroke(void *font, const char* string)
{ 
	glPushMatrix();
		glTranslatef(-125,-50,0);
		while(*string)
			glutStrokeCharacter(font, *string++);
	glPopMatrix();
}//end draw_string_stroke

//Pre: yDisplacement2, zoom2, rotateAngle2 are not null
//Post: Clear background to black. 
//		Sets draw color to white.
//		based on yDiscplacement2, rotateAngle2, zoom2, draws the opengl stroke font:
//				font type Roman, text string "DDD"
//		and performs a translation, scale and rotation on the text
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

	glutSwapBuffers();
}//end displayOpenGLFont()

//Pre: None
//Post: Clears background to black. Draws 2d person model
void displayPerson()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//Paint black background

	//Person Screen on the left
	glViewport(0,0, screenWidth1, screenHeight1);
	drawPerson();
	
	glutSwapBuffers();
}//end displayPerson

//Pre: None
//Post: Clears background to default black then draws stroke font text
void displayText()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);	//Paint black background

	//Person Screen on the left
	glViewport(0,0, screenWidth2, screenHeight2);
	drawText();
	
	glutSwapBuffers();
}//end displayText

//Pre: char mapping of keyboard input, x,y coord
//Post: Refreshes display after modifying 2D transformation variables
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

//Pre: char mapping of keyboard input, x,y coord
//Post: Refreshes display after modifying 2D transformation variables
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
//Post:Displays keyboard input format via console output.
//		Initializes three windows: Person model, stroke font model, and opengl font model
//		Based on context focus, user can use keyboard input to modify the translation (Y-axis only) rotation angle and zoom
//		of the stroke font and opengel font independently from one another.
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
	glutInitWindowPosition(0,0);
	personWindow = glutCreateWindow("People");
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