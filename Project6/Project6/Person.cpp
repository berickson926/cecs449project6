#include "Person.h"

void drawCirclePoint(int x, int y)
{
	glPointSize(.5);
	glColor3f(1.0,1.0,1.0);

	//glEnable(GL_POINT_SMOOTH);
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
	//glDisable(GL_POINT_SMOOTH);
}//end drawCirclePoint

void circleMidpoint()
{
	int radius = 120; //1 foot?
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
		glTranslatef(15,0,0);
		drawHand();
	glPopMatrix();
}//end drawArm

void Person::drawFoot()
{
	glPushMatrix();
		glScalef(.5,.25,0);
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
		glTranslatef(60,0,0);
		drawFoot();
	glPopMatrix();
}//end drawLeg

void Person::drawHead()
{
	glPushMatrix();
		glScalef(.5,.5,0);
		glCallList(circleIndex);
	glPopMatrix();
}//end drawHead

void Person::drawTorso()
{
	glPushMatrix();
		glScalef(1.25,2.5,0);
		glCallList(squareIndex);
	glPopMatrix();
}//end drawTorso

void Person::drawPerson()
{
	/*
	Draw torso
    Draw head
    Draw right arm
    Draw left arm
    Draw right leg
    Draw left leg*/
	//////////////////////////////////////////////////////

	glPushMatrix();//(0,0)
		glPushMatrix();
			glTranslatef(-75,0,0);//Move to center of torso bottom: -3", 0"
			drawTorso();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 300, 0);//Move to top of torso, 0", 30"
			glPushMatrix();
				glTranslatef(0, 60, 0);//move to center of head: 0", 36"
				drawHead();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			//Right arm
			glTranslatef(150,10,0);
			glRotatef(20,0,0,1);
			drawArm();
		glPopMatrix();
		glPushMatrix();
			//left arm
			glScalef(-1,1,0);
			glTranslatef(150,10,0);
			glRotatef(20,0,0,1);
			drawArm();
		glPopMatrix();
		glPushMatrix();
			//Draw Right leg
			glTranslatef(15, 0, 0);
			glTranslatef(0, -300, 0);
			drawLeg();
		glPopMatrix();
		glPushMatrix();
			//Draw left leg
			glScalef(-1,1,0);
			glTranslatef(15, 0, 0);
			glTranslatef(0, -300, 0);
			drawLeg();
		glPopMatrix();
	glPopMatrix();

}//end drawPerson

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