#include "stdafx.h"
#include "Fonts.h"

Fonts::Fonts()
{
	this->w = GLUT_WINDOW_WIDTH;
	this->h = GLUT_WINDOW_HEIGHT;

	
}

void Fonts::printtext(int x, int y, string String)
{
	//(x,y) is from the bottom left of the window
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0f, 1.0f);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	int wielkosc=0;
	const unsigned char *s;
	int dl;

	for (int i = 0; i < String.size(); i++)
	{
		wielkosc = wielkosc + glutBitmapWidth(GLUT_BITMAP_9_BY_15, String[i]);
	}

	glTranslatef(0,0,0);
	glRasterPos2i(0, h*0.1);

	//printf("Wielkosc %d\n",wielkosc/13, pos);


	for (int i = 0; i<String.size(); i++)
	{
		
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);
	}
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Fonts::WeaponName(string String)
{
	//(x,y) is from the bottom left of the window
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0f, 1.0f);
	glColor3f(1, 1, 1);
	glScalef(1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	int wielkosc = 0;
	const unsigned char *s;
	int dl;

	for (int i = 0; i < String.size(); i++)
	{
		wielkosc = wielkosc + glutBitmapWidth(GLUT_BITMAP_9_BY_15, String[i]);
	}
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2i(85, h*0.18);

	//printf("Wielkosc %d\n",wielkosc/13, pos);
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);

	for (int i = 0; i<String.size(); i++)
	{

		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);
	}
	glPopAttrib();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


}



