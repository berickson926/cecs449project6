#ifndef CLASS_PERSON_H
#define CLASS_PERSON_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include <gl/glut.h>

class Person
{
private:

	void drawCircle();
	void drawSquare();

	void drawHand();
	void drawArm();

	void drawFoot();
	void drawLeg();

	void drawHead();
	void drawTorso();

	GLuint circleIndex, squareIndex;

public:

	Person();
	void drawPerson();
};

#endif//end CLASS_PERSON_H

