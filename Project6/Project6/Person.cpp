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
	int radius = 12; //1 foot?
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
	drawHand();
}//end drawArm

void Person::drawPerson()
{
	//drawTorso();
	//drawHead();
	
	circleIndex = glGenLists(1);

	glNewList(circleIndex, GL_COMPILE);
		circleMidpoint();
	glEndList();

	glCallList(circleIndex);
	//glCallList(circleIndex);
	//drawHand();
	//drawLeftArm();

	//drawLeg();
	//drawLeftLeg();

}

Person::Person()
{
	circleIndex = glGenLists(1);

	glNewList(circleIndex, GL_COMPILE);
		circleMidpoint();
	glEndList();

	/*squareIndex = glGenLists(1);

	glNewList(squareIndex, GL_COMPILE);
		drawSquare();
	glEndList();*/
}//end Constructor