#include "Chest.h"
#include "stdafx.h"


chest::chest(float x, float y, float z,float rotate)
{
	//Wczytywanie tekstury obiektu
	opened = false;
	glEnable(GL_TEXTURE_2D);
	chest_texture = new CTexture("Data/Models/Environment/Chest/Chest.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	glDisable(GL_TEXTURE_2D);
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
	this->rotate = rotate;
	chest_obj = create_chest();
	chest_upper = create_chest_upper();
	chest_upper2 = create_chest_upper2();
	chest_upper3 = create_chest_upper3();
}

void chest::close()
{
	opened = false;
}

GLuint chest::create_chest()
{
	Time = 4700;
	GLuint obj;
	obj = glGenLists(1);

	glNewList(obj, GL_COMPILE);
	glBegin(GL_QUADS);
	//Podloze
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1.7);
	glVertex3f(1, 0, 1.7);
	glVertex3f(1, 0, 0);

#pragma region zewnetrzna strona
	glTexCoord2f(0.266, 0.72); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0, 0, 1.7);
	glTexCoord2f(0.266, 1); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0, 0.8, 1.7);
	glTexCoord2f(0.735, 1); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0, 0.8, 0);
	glTexCoord2f(0.735, 0.72); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0, 0, 0);
	
	glTexCoord2f(1, 0.68); glNormal3f(0.0f, 0.0f, 1.0f);  glVertex3f(1, 0, 1.7);
	glTexCoord2f(0.75, 1); glNormal3f(0.0f, 0.0f, 1.0f);  glVertex3f(1, 0.8, 1.7);
	glTexCoord2f(1, 1); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(0, 0.8, 1.7);
	glTexCoord2f(0.75, 0.68); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(0, 0, 1.7);

	glTexCoord2f(0.266, 0.44); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(1, 0, 0);
	glTexCoord2f(0.266, 0.72); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(1, 0.8, 0);
	glTexCoord2f(0.735, 0.72); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(1, 0.8, 1.7);
	glTexCoord2f(0.735, 0.44); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(1, 0, 1.7);

	glTexCoord2f(1, 0.68); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(0.75, 1); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(0, 0.8, 0);
	glTexCoord2f(1, 1); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(1, 0.8, 0);
	glTexCoord2f(0.75, 0.68); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(1, 0, 0);
#pragma endregion

#pragma region gorna strona

	//FRONT
	glTexCoord2f(0.296, 0.746); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0, 0.8, 0);
	glTexCoord2f(0.704, 0.746); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0, 0.8, 1.7);
	glTexCoord2f(0.704, 0.720); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.1, 0.8, 1.7);
	glTexCoord2f(0.296, 0.720); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.1, 0.8, 0);

	//TYL
	glTexCoord2f(0.296, 0.746); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.9, 0.8, 0);
	glTexCoord2f(0.704, 0.746); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.9, 0.8, 1.7);
	glTexCoord2f(0.704, 0.720); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(1, 0.8, 1.7);
	glTexCoord2f(0.296, 0.720); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(1, 0.8, 0);


	//BOKI
	glTexCoord2f(0.68, 0.72); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.1, 0.8, 0);
	glTexCoord2f(0.62, 0.72); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.1, 0.8, 0.1);
	glTexCoord2f(0.62, 1); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.9, 0.8, 0.1);
	glTexCoord2f(0.68, 1); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.9, 0.8, 0);

	glTexCoord2f(0.68, 0.72); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.1, 0.8, 1.6);
	glTexCoord2f(0.62, 0.72); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.1, 0.8, 1.7);
	glTexCoord2f(0.62, 1); glNormal3f(0.0f, 1.0f, 0.0f);	glVertex3f(0.9, 0.8, 1.7);
	glTexCoord2f(0.68, 1); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.9, 0.8, 1.6);







#pragma endregion


#pragma region srodek
	//PRZOD

	 glTexCoord2f(0.0, 0.0); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(0.1, 0.1, 0.1);
	 glTexCoord2f(0.0, 0.235); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(0.1, 0.8, 0.1);
	 glTexCoord2f(0.5, 0.235); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(0.1, 0.8, 1.6);
	 glTexCoord2f(0.5, 0.0); glNormal3f(1.0f, 0.0f, 0.0f); glVertex3f(0.1, 0.1, 1.6);

	//TYL
	 glTexCoord2f(0.0, 0.0); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0.9, 0, 1.6);
	 glTexCoord2f(0.0, 0.235); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0.9, 0.8, 1.6);
	 glTexCoord2f(0.5, 0.235); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0.9, 0.8, 0.1);
	 glTexCoord2f(0.5, 0.0); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0.9, 0, 0.1);

	//BOK LEWY
	 glTexCoord2f(0.0, 0.0); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(0.9, 0, 0.1);
	 glTexCoord2f(0.0, 0.235); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(0.9, 0.8, 0.1);
	 glTexCoord2f(0.25, 0.235); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(0.1, 0.8, 0.1);
	 glTexCoord2f(0.25, 0.0); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(0.1, 0, 0.1);

	//BOK PRAWY
	 glTexCoord2f(0.0, 0.0); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(0.1, 0, 1.6);
	 glTexCoord2f(0.0, 0.235); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(0.1, 0.8, 1.6);
	 glTexCoord2f(0.25, 0.235); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(0.9, 0.8, 1.6);
	 glTexCoord2f(0.25, 0.0); glNormal3f(0.0f, 0.0f, -1.0f); glVertex3f(0.9, 0, 1.6);

	//DOL
	
	 glTexCoord2f(0.5, 0.0); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.1, 0.17, 0.1);
	 glTexCoord2f(0.0, 0.0); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.1, 0.17, 1.6);
	 glTexCoord2f(0.0, 0.235); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.9, 0.17, 1.6);
	 glTexCoord2f(0.5, 0.235); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.9, 0.17, 0.1);

#pragma endregion
	
	
	glEnd();
	glEndList();



	return GLuint(obj);
}

GLuint chest::create_chest_upper()
{
	GLuint obj = NULL;
	int Np = 48;
	float offset =0;
	obj = glGenLists(1);
	glNewList(obj, GL_COMPILE);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= Np/2; ++i) {
		float x = sin(2.0f * 3.1415 * ((float)i / Np));
		float z = cos(2.0f * 3.1415 * ((float)i / Np));
		glNormal3f(x, 0.0f, z);
		glTexCoord2f(0.265, 0.25+offset); glVertex3f(x, 1.0f, z);
		glNormal3f(x, 0.0f, z);
		glTexCoord2f(0.7353, 0.25+offset);	glVertex3f(x, -1.0f, z);
		offset = offset + 0.02;
	}
	glEnd();
	glEndList();

	return GLuint(obj);
}

GLuint chest::create_chest_upper2()
{

	GLuint obj = NULL;
	int Np = 48;
	float offset = 0;
	obj = glGenLists(1);
	glNewList(obj, GL_COMPILE);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i <= Np/2; ++i) {
		float x = sin(2.0f * 3.1415 * ((float)i / Np));
		float z = cos(2.0f * 3.1415 * ((float)i / Np));
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.265, 0.25 + offset);	glVertex3f(x, 1.0f, z);
		offset = offset + 0.02;
	}
	glEnd();
	glEndList();
	return GLuint(obj);
}

GLuint chest::create_chest_upper3()
{
	GLuint obj = NULL;
	int Np = 48;
	float offset = 0;
	obj = glGenLists(1);
	glNewList(obj, GL_COMPILE);
		glBegin(GL_QUADS);

		glTexCoord2f(0.299, 0.248); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0, -1, 1);
		glTexCoord2f(0.299, 0.608); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0, 1, 1);
		glTexCoord2f(0.703, 0.608); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0, 1, -1);
		glTexCoord2f(0.703, 0.248); glNormal3f(-1.0f, 0.0f, 0.0f); glVertex3f(0, -1, -1);
/*
		glTexCoord2f(0.68, 0.72); glVertex3f(0.1, 0.8, 1.6);
		glTexCoord2f(0.62, 0.72); glVertex3f(0.1, 0.8, 1.7);
		glTexCoord2f(0.62, 1);	glVertex3f(0.9, 0.8, 1.7);
		glTexCoord2f(0.68, 1); glVertex3f(0.9, 0.8, 1.6);
*/
		glEnd();
	glEndList();
	return GLuint(obj);
}

void chest::open()
{
	opened = true;
}

void chest::render()
{
	glPushMatrix();
	
	glTranslatef(coords[0], coords[1], coords[2]);
	
	glScalef(0.35, 0.35, 0.35);
	glRotatef(rotate, 0, 1, 0);
		glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, chest_texture->GetId());
	glCallList(chest_obj);
	glTranslatef(0.5, 0.8, 0.85);
	glTranslatef(0.5, 0, 0);
	if (opened)
		Time = Time + 17 ;
		glRotatef(-sin(Time*0.001) * 65 - 65, 0, 0, 1);

		if (sin(Time*0.001) * 65 <= -64.95)
			opened = false;
		if (sin(Time*0.001) * 65 >= 64.95)
			opened = false;
	
	
	glTranslatef(-0.5, 0, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.3, 0.85, 0.5);

	glCallList(chest_upper);
	glCallList(chest_upper2);
	glCallList(chest_upper3);
	glTranslatef(0, 0, 0);
	glRotatef(180, 1, 0, 0);
	glCallList(chest_upper2);
	glPopMatrix();
	
	

}
