#include"Player.h"
#include"stdafx.h"

void CPlayer::WeaponPos()
{
	
	glTranslatef(pos.x, pos.y, pos.z);

	glTranslatef(actual_weapon->offset[0][0], actual_weapon->offset[0][1], actual_weapon->offset[0][2]);
	glRotatef(atan2(dir.x, dir.z) * 180 / 3.1415 + 90, 0, 1, 0);
	glTranslatef(actual_weapon->offset[1][0], actual_weapon->offset[1][1], actual_weapon->offset[1][2]);
	glRotatef(acos(dir.y) * 180 / 3.1415 - 90, 0, 0, 1);
	glTranslatef(actual_weapon->offset[2][0], actual_weapon->offset[2][1], actual_weapon->offset[2][2]);

	if (actual_weapon->shooting == true && actual_weapon->type != 1)
	{
		glTranslatef(sin(T*0.05)*actual_weapon->recoil*0.05 + actual_weapon->offset[3][0] + (sin(distance / 2.7)*0.0005) + sin(T*0.002)*0.0012, actual_weapon->offset[3][1] + sin(distance / 2.2)*0.005 + cos(T*0.003)*0.0016, actual_weapon->offset[3][2] + sin(distance / 2.2)*0.005 + sin(T*0.0009)*0.0026);
		glRotatef(-sin(T*0.09)*actual_weapon->recoil*8, 0, 0, 1);
	}
	else


		glTranslatef(actual_weapon->offset[3][0] + (sin(distance / 2.7)*0.0007) + sin(T*0.002)*0.0015, actual_weapon->offset[3][1] + sin(distance / 2.2)*0.007 + cos(T*0.003)*0.0019, actual_weapon->offset[3][2] + sin(distance / 2.2)*0.008 + sin(T*0.0009)*0.0029);
	
	//glTranslatef(sin(T*0.003)*0.004,0 ,0);
	//glRotatef(-sin(T*0.05)*1.5, 0, 0, 1);
	
	//Reloading broni
	actual_weapon->Status();

}

void CPlayer::PlayerRemoveHealth(int damage)
{
	health -= damage;
	if (health < 0){
		player_dead = true;
		health = 0;
	}
		
}

void CPlayer::AddMoney(int price)
{
	money += price;
}

void CPlayer::DrawTextHUD(char *znaki)
{
	int resolution[2];
	resolution[0] = glutGet(GLUT_SCREEN_WIDTH);
	resolution[1] = glutGet(GLUT_SCREEN_HEIGHT);
	int min_pos = 500;
	int max_pos = 500;


	#pragma region KONFIGURACJA

	float color[3] = { 0.0f, 1.0f, 0.35f }; //Kolor podswietlenia broni
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, glutGet(GLUT_SCREEN_WIDTH), 0.0, glutGet(GLUT_SCREEN_HEIGHT), -1.0, 1.0);
	gluPerspective(45.0f, GLUT_SCREEN_WIDTH / GLUT_SCREEN_HEIGHT, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
	int width = glutGet(GLUT_SCREEN_WIDTH);
	int height = glutGet(GLUT_SCREEN_HEIGHT);

	glColor3f(1, 1, 1);

#pragma endregion	

	
	#pragma region TEKST
	//BRON W PIERWSZYM SLOCIE
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_TEXTURE_2D);
	int offset_x;
	int offset_y;

	int offsets[2] = { 0.062,0.124 };

	int i = 0;
	int j = 0;
	for (int i = 0; i < 24;i++)
	{
		if (i % 16 == 0 && i!=0)
			j++;
		//Duze litery od A do P

		if ((int)znaki[i] <= 65 && (int)znaki[i] >= 80)
		{
			offset_x = (int)znaki[i] - 64;
			offset_y = 1;
		}
		//Duze litery od R do Z
		if ((int)znaki[i] >= 82 && (int)znaki[i] <= 90)
		{
			offset_x = (int)znaki[i] - 81;
			offset_y = 2;
		}

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, font_texture->GetId());
		glBegin(GL_QUADS);
			glTexCoord2f(0.0625 * i, 1 - (j + 1)*0.125);			glVertex2i(resolution[0] / 2 + (i * 60) - 600, 150);
			glTexCoord2f(0.0625 * i, 1 - j*0.125);				glVertex2i(resolution[0] / 2 + (i*60) - 600, 200);
			glTexCoord2f(0.0625 * (i + 1),1 - j*0.125);		glVertex2i(resolution[0] / 2 + 50 + (i * 60) - 600, 200);
			glTexCoord2f(0.0625 * (i + 1),1 - (j+1)*0.125 );	glVertex2i(resolution[0] / 2 + 50 + (i * 60) - 600, 150);
		glEnd();
		glPopMatrix();
	}
	glPopAttrib();

#pragma endregion


	#pragma region PRZYWROCENIE POPRZEDNICH USTAWIEN
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRasterPos2d(10, 10);
	glScalef(0.1, 0.1, 0.1);
	glPopMatrix();

	#pragma endregion

}

