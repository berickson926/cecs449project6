#ifndef FONTWRITER_H
#define FONTWRITER_H

#include <string.h>
#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/Glut.h>
#include <stdlib.h>
#include <iostream>

#define PT 1
#define STROKE 2
#define END 3

typedef struct charpoint 
{
   GLfloat   x, y;
   int    type;
} CP;

class FontWriter
{
private:
	static void printStrokedString(char *s);
	static void drawLetter(CP *l);
public:
	
	//Default Constructor
	FontWriter();

	//Pre:None
	//Post:Draws predefined text centered at origin 
	void display();
};

#endif