#include "Person.h"

void drawCirclePoint(int x, int y)
{
	glPointSize(.5);
	glColor3f(1.0,1.0,1.0);

	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
		glVertex2i(-x,y);
		glVertex2i(x,-y);
		glVertex2i(-x,-y);
		glVertex2i(y,+x);
		glVertex2i(-y,x);
		glVertex2i(y,-x);
		glVertex2i(-y,-x);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
}//end drawCirclePoint

void circleMidpoint()
{
	int radius = 60; //1 foot?
	int x = 0;
	int y = radius;

	float pK = (5/4) - radius;//p0

	//draw the first point
	drawCirclePoint(x, y);

	while(x < y)
	{
		if(pK < 0)
		{
			x++;
			pK += 2*x+1;
		}//end if
		else
		{
			x++;
			y--;
			pK += 2*(x-y)+1;
		}
		
		drawCirclePoint(x, y);//Draw additional points
	}//end while

}//end circleMidpoint

void Person::drawSquare()
{
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
		glVertex2f(0,0);
		glVertex2f(0,120);
		glVertex2f(120,120);
		glVertex2f(120,0);
	glEnd();
}//end drawSquare

void Person::drawHand()
{
	glPushMatrix();
		glScalef(.25,.25,0);
		glCallList(circleIndex);
	glPopMatrix();
}//end drawHand

void Person::drawArm()
{
	glPushMatrix();
		glPushMatrix();
			glScalef(.25,2.5,0);
			glCallList(squareIndex);
		glPopMatrix();
		glTranslatef(.125,0,0);
		drawHand();
	glPopMatrix();
}//end drawArm

void Person::drawFoot()
{
	glPushMatrix();
		glScalef(.5,0,0);
		glCallList(circleIndex);
	glPopMatrix();
}//end drawFoot

void Person::drawLeg()
{
	glPushMatrix();
		glPushMatrix();
			glScalef(.5,2.5,0);
			glCallList(squareIndex);
		glPopMatrix();
		glTranslatef(.5,0,0);
		drawFoot();
	glPopMatrix();
}//end drawLeg


void Person::drawPerson()
{
	//drawTorso();
	//drawHead();

	//Draw the left arm
	drawArm();

	//Draw the right arm

	drawLeg();
	//drawLeftLeg();

}

Person::Person()
{
	//Compile the basic structures, a circle & square that will have transformations applied to model the person
	circleIndex = glGenLists(1);

	glNewList(circleIndex, GL_COMPILE);
		circleMidpoint();
	glEndList();

	squareIndex = glGenLists(1);

	glNewList(squareIndex, GL_COMPILE);
		drawSquare();
	glEndList();
}//end Constructor