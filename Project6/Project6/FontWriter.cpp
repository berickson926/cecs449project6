#include "FontWriter.h"

//Lowercase characters
CP ddata[] = {
	{ 5, 1, PT }, { 3, 0, PT }, { 2, 0, PT }, { 0, 2, PT }, { 0, 3, PT },
	{ 2, 5, PT }, { 3, 5, PT }, { 5, 4, STROKE }, { 5, 10, PT }, { 5, 0, END }
};

CP hdata[] = {
	{ 0, 2, PT }, { 0, 3, PT }, { 2, 5, PT }, { 3, 5, PT }, { 5, 4, PT }, {5,0,STROKE},
	{0,0,PT}, {0,10,END}
};

CP kdata[] = {
	{0,0,PT}, {0,10,STROKE},
	{0,4,PT}, {6,8,STROKE},
	{0,4,PT}, {7,0,END}
};

char *test1 = "h k d d k h";

void FontWriter::drawLetter(CP *l)
{
   glBegin(GL_LINE_STRIP);
   while (1) 
   {
      switch (l->type) 
	  {
         case PT:
            glVertex2fv(&l->x);
            break;
         case STROKE:
            glVertex2fv(&l->x);
            glEnd();
            glBegin(GL_LINE_STRIP);
            break;
         case END:
            glVertex2fv(&l->x);
            glEnd();
            glTranslatef(8.0, 0.0, 0.0);
            return;
      }
      l++;
   }
}

void FontWriter::printStrokedString(char *s)
{
   GLsizei len = strlen(s);
   glCallLists(len, GL_BYTE, (GLbyte *)s);
}

void FontWriter::display()
{
   glColor3f(1.0, 1.0, 1.0);
   glPushMatrix();
	   glScalef(2.0, 2.0, 2.0);
	   glTranslatef(-45,-5, 0.0);
	   this->printStrokedString(test1);
   glPopMatrix();
   
   glTranslatef(100,8,0);
   glFlush();
}

FontWriter::FontWriter()
{
	GLuint base;

   glShadeModel (GL_FLAT);

   base = glGenLists (128);
   glListBase(base);
   glNewList(base+'d', GL_COMPILE); drawLetter(ddata);
   glEndList();
   glNewList(base+'h', GL_COMPILE); drawLetter(hdata);
   glEndList();
   glNewList(base+'k', GL_COMPILE); drawLetter(kdata);
   glEndList();
   glNewList(base+' ', GL_COMPILE);

   
   glTranslatef(8.0, 0.0, 0.0); glEndList();

}//end constructor