#include "Player.h"
#include"stdafx.h"

class GameManager;

void CPlayer::PlayerUpdate()
{
	if (player_dead == false) {

		if (update_time > 2000) {
			if (health < 100)
			{
				health += 8;
				update_time = 0;
			}
			if (health > 100)
				health = 100;
		}
		update_time += 16;

	}

}

void CPlayer::LoadBMPHUD()
{


#pragma region Laduje cyfry
	HUD_Numbers[0] = LoadObj("Data/GUI/Numbers/0.obj");
	HUD_Numbers[1] = LoadObj("Data/GUI/Numbers/1.obj");
	HUD_Numbers[2] = LoadObj("Data/GUI/Numbers/2.obj");
	HUD_Numbers[3] = LoadObj("Data/GUI/Numbers/3.obj");
	HUD_Numbers[4] = LoadObj("Data/GUI/Numbers/4.obj");
	HUD_Numbers[5] = LoadObj("Data/GUI/Numbers/5.obj");
	HUD_Numbers[6] = LoadObj("Data/GUI/Numbers/6.obj");
	HUD_Numbers[7] = LoadObj("Data/GUI/Numbers/7.obj");
	HUD_Numbers[8] = LoadObj("Data/GUI/Numbers/8.obj");
	HUD_Numbers[9] = LoadObj("Data/GUI/Numbers/9.obj");
	HUD_Numbers[10] = HUD_Numbers[0];
	HUD_Numbers[11] = LoadObj("Data/GUI/Numbers/dollar.obj");
	HUD_Slash = LoadObj("Data/GUI/Numbers/slash.obj");

	HUD_elements[0] = LoadObj("Data/GUI/Numbers/reloading.obj");
	HUD_elements[1] = LoadObj("Data/GUI/Numbers/dot.obj");

#pragma endregion

#pragma region Nazwy broni
	HUD_Weapon_Name[0] = LoadObj("Data/GUI/MP5K.obj");
	HUD_Weapon_Name[1] = LoadObj("Data/GUI/M4A4.obj");
	HUD_Weapon_Name[2] = LoadObj("Data/GUI/AKS74U.obj");
	HUD_Weapon_Name[3] = LoadObj("Data/GUI/SCARH.obj");
	HUD_Weapon_Name[4] = LoadObj("Data/GUI/M9.obj");
	HUD_Weapon_Name[5] = LoadObj("Data/GUI/AUG.obj");
	HUD_Weapon_Name[6] = LoadObj("Data/GUI/M249.obj");
	HUD_Weapon_Name[7] = LoadObj("Data/GUI/DESERTDEAGLE.obj");
	HUD_Weapon_Name[8] = LoadObj("Data/GUI/BIZON.obj");
	HUD_Weapon_Name[9] = LoadObj("Data/GUI/Blaster.obj");
#pragma endregion

#pragma region Miniaturki
	HUD_Weapons[0] = new CTexture("Data/GUI/Guns/MP5K.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	HUD_Weapons[1] = new CTexture("Data/GUI/Guns/M4A4.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	HUD_Weapons[2] = new CTexture("Data/GUI/Guns/AKS74U.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	HUD_Weapons[3] = new CTexture("Data/GUI/Guns/SCARH.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	HUD_Weapons[4] = new CTexture("Data/GUI/Guns/M9.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	HUD_Weapons[5] = new CTexture("Data/GUI/Guns/AUG.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	HUD_Weapons[6] = new CTexture("Data/GUI/Guns/M249.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	HUD_Weapons[7] = new CTexture("Data/GUI/Guns/DESERTDEAGLE.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	HUD_Weapons[8] = new CTexture("Data/GUI/Guns/BIZON.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	HUD_Weapons[9] = new CTexture("Data/GUI/Guns/BLASTER.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Empty = new CTexture("Data/GUI/Guns/EMPTY.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	Zombie_left = new CTexture("Data/GUI/zombie_bar.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Health_bar = new CTexture("Data/GUI/health_bar.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Fala = LoadObj("Data/GUI/fala.obj");
	others[0] = LoadObj("Data/GUI/nastepna_fala.obj");

	Kup_Bron[0] = LoadObj("Data/GUI/cena.obj");
	Kup_Bron[1] = LoadObj("Data/GUI/amunicja.obj");
	Press = LoadObj("Data/GUI/press.obj");
	GameOver = LoadObj("Data/GUI/game_over.obj");
#pragma endregion


#pragma region czcionki
	font_texture = new CTexture("Data/Fonts/font.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	if (font_texture)
		printf("Pomyslnie wczytano czcionke\n");
	else
		printf("Nie wczytano czcionki\n");
#pragma endregion

}


void CPlayer::HUD(int id, int first_weapon, int second_weapon, int magazine_ammo, int max_ammo, GameManager *game_manager, BuyWeapon *buy_weapon) {

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


#pragma region CELOWNIK
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	float delta = 0;

	if (actual_weapon->shooting == true)
		delta = sin(T*0.04 / actual_weapon->weapon_cooldown * 100) * 6;
	int middle[8] = { width / 2 - 7, height / 2 - 7, width / 2 - 7, height / 2 + 7, width / 2 + 7, height / 2 + 7, width / 2 + 7, height / 2 - 7 };
	//glTranslatef(T*0.001, 0, 0);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 0.75);
	glVertex2f(middle[0] - 25 - 12 - delta, middle[1] + 4);
	glVertex2f(middle[2] - 25 - 12 - delta, middle[3] - 5);
	glVertex2f(middle[4] - 15 - 12 - delta, middle[5] - 5);
	glVertex2f(middle[6] - 15 - 12 - delta, middle[7] + 4);

	glVertex2f(middle[0] + 15 + 12 + delta, middle[1] + 4);
	glVertex2f(middle[2] + 15 + 12 + delta, middle[3] - 5);
	glVertex2f(middle[4] + 25 + 12 + delta, middle[5] - 5);
	glVertex2f(middle[6] + 25 + 12 + delta, middle[7] + 4);

	glVertex2f(width / 2 - 3, height / 2 - 20 - delta);
	glVertex2f(width / 2 - 3, height / 2 - 44 - delta);
	glVertex2f(width / 2 + 3, height / 2 - 44 - delta);
	glVertex2f(width / 2 + 3, height / 2 - 20 - delta);

	glVertex2f(width / 2 - 3, height / 2 - 20 + 63 + delta);
	glVertex2f(width / 2 - 3, height / 2 - 44 + 63 + delta);
	glVertex2f(width / 2 + 3, height / 2 - 44 + 63 + delta);
	glVertex2f(width / 2 + 3, height / 2 - 20 + 63 + delta);

	glEnd();



	glPopMatrix();
	glPopAttrib();


#pragma endregion


#pragma region PIENIADZE
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(width*0.475, height * 0.02, 0);
	glColor4f(1, 0.96, 0, 0.75f);
	glRotatef(90, 1, 0, 0);
	glScalef(48, 48, 48);
	int tmp;

	tmp = money / 10000;
	glCallList(HUD_Numbers[tmp]);
	glTranslatef(0.45, 0, 0);

	//Tysiace
	tmp = money - (money / 10000) * 10000;
	glCallList(HUD_Numbers[tmp / 1000]);
	glTranslatef(0.45, 0, 0);

	//Setki
	tmp = tmp - (tmp / 1000 * 1000);

	glCallList(HUD_Numbers[tmp / 100]);
	glTranslatef(0.45, 0, 0);

	//Dziesiatki
	tmp = tmp - (tmp / 100 * 100);

	glCallList(HUD_Numbers[tmp / 10]);
	glTranslatef(0.45, 0, 0);

	//Jednosci
	tmp = tmp - (tmp / 10 * 10);
	glCallList(HUD_Numbers[tmp]);
	glTranslatef(0.45, 0, 0);
	glCallList(HUD_Numbers[11]);

	glPopMatrix();
	glPopAttrib();
#pragma endregion


#pragma region NAPIS PRZELADOWANIA
	//NAPIS PRZELADOWANIA
	if (actual_weapon->reloading == true)
	{
		int interval = actual_weapon->reload_end - T;
		glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();
		glColor4f(1, 1, 1, 0.75);
		glTranslatef(width*0.5, height * 0.15, 0);
		glRotatef(90, 1, 0, 0);
		//glRotatef(T*0.001, 0, 0, 1);
		glScalef(45, 45, 45);
		glCallList(HUD_elements[0]);
		glTranslatef(3.5, 0, 0);
		glCallList(HUD_Numbers[(int)interval / 1000]);
		glTranslatef(0.35, 0, 0);
		glCallList(HUD_elements[1]);
		int tmp = interval - (interval / 1000 * 1000);
		glTranslatef(0.35, 0, 0);
		glCallList(HUD_Numbers[tmp / 100]);
		glTranslatef(0.35, 0, 0);
		tmp = tmp - (tmp / 100 * 100);
		glCallList(HUD_Numbers[tmp / 10]);
		glPopMatrix();
		glPopAttrib();
	}


#pragma endregion


#pragma region NAPIS BRONI
	//NAPIS BRONI
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glColor3f(1, 1, 1);

	glTranslatef(width*0.86, height * 0.28, 0.2);
	glRotatef(90, 1, 0, 0);
	//glRotatef(T*0.001, 0, 0, 1);
	glScalef(55, 55, 55);
	if (id < 0 || id>9)
		glCallList(HUD_Weapon_Name[0]);
	else
		glCallList(HUD_Weapon_Name[id]);
	glPopMatrix();
	glPopAttrib();


	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(width*0.825, height * 0.21, 0.2);
	glRotatef(90, 1, 0, 0);
	glScalef(42, 42, 42);
	if (actual_weapon->special == true)
		glTranslatef(1.0, 0, 0);
	glCallList(HUD_Numbers[magazine_ammo / 10]);
	glTranslatef(0.45, 0, 0);
	glCallList(HUD_Numbers[magazine_ammo % 10]);
	if (actual_weapon->special == false)
	{
		glTranslatef(0.45, 0, 0);
		glCallList(HUD_Slash);
		glTranslatef(0.45, 0, 0);
		glCallList(HUD_Numbers[max_ammo / 100]);
		glTranslatef(0.45, 0, 0);
		glCallList(HUD_Numbers[(max_ammo - (max_ammo / 100) * 100) / 10]);
		glTranslatef(0.45, 0, 0);
		glCallList(HUD_Numbers[max_ammo % 10]);
	}
	glPopMatrix();
	glPopAttrib();


	//Background info o broni
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glTranslatef(width*0.86, height * 0.26, 0);

	glScalef(1.1, 1, 1);
	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 0.4f);
	glVertex2f(-120, 75.0);
	glVertex2f(-120, -75.0);
	glVertex2f(120.0, -75.0);
	glVertex2f(120.0, 75.0);

	glEnd();

	glPopMatrix();
	glPopAttrib();

#pragma endregion


#pragma region NOWA FALA
	if (game_manager->win_played == true)
	{
		//NOWA FALA
		glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();
		glColor3f(1, 1, 1);

		glTranslatef(width*0.5, height * 0.4, 0.2);
		glRotatef(90, 1, 0, 0);
		glColor4f(1, 1, 1, 0.4);
		glScalef(55, 55, 55);
		glCallList(others[0]);
		glTranslatef(0, 0, 0.85);
		float left_time = (game_manager->next_wave - T) / 1000;
		if (left_time >= 10)
		{
			glCallList(HUD_Numbers[(int)left_time / 10]);
			glTranslatef(0.45, 0, 0);
		}
		glCallList(HUD_Numbers[(int)left_time%10]);
		glPopMatrix();
		glPopAttrib();
	}
#pragma endregion


#pragma region GAME OVER
	if (player_dead == true)
	{

		glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();
		glColor3f(1, 1, 1);

		glTranslatef(width*0.5, height * 0.8, 0.2);
		glRotatef(90, 1, 0, 0);
		glColor4f(1, 1, 1, 1.0);
		glScalef(140, 140, 140);
		glTranslatef(0, 0, 1.0);
		glCallList(GameOver);
		glPopMatrix();
		glPopAttrib();
	}
#pragma endregion


#pragma region ZAKUP BRONI
	if (buy_weapon->collision != 100)
	{
		int cena = buy_weapon->bronie[buy_weapon->collision].cost;
		int cena_ammo = buy_weapon->bronie[buy_weapon->collision].ammo_cost;
		//NOWA FALA
		glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();
		glColor3f(1, 1, 1);

		glTranslatef(width*0.1, height * 0.6, 0.2);
		glRotatef(90, 1, 0, 0);
		glColor4f(1, 1, 1, 0.7);
		glScalef(55, 55, 55);
		glCallList(Press);
		glTranslatef(0, 0, 1);
		glCallList(Kup_Bron[0]);
		tmp = money / 10000;
		
		glTranslatef(2.45, 0, 0);
		//Tysiace
		int tmp = cena - (cena / 10000) * 10000;
		if(tmp >= 1000)
		glCallList(HUD_Numbers[tmp / 1000]);
		glTranslatef(0.45, 0, 0);
		//Setki
		tmp = tmp - (tmp / 1000 * 1000);
		glCallList(HUD_Numbers[tmp / 100]);
		glTranslatef(0.45, 0, 0);
		//Dziesiatki
		tmp = tmp - (tmp / 100 * 100);

		glCallList(HUD_Numbers[tmp / 10]);
		glTranslatef(0.45, 0, 0);

		//Jednosci
		tmp = tmp - (tmp / 10 * 10);
		glCallList(HUD_Numbers[tmp]);
		glTranslatef(0.45, 0, 0);

		glCallList(HUD_Numbers[11]);
		glTranslatef(-4.25, 0, 0);
		glTranslatef(0, 0, 1.0);
		if (buy_weapon->collision != 9)
		{
		glCallList(Kup_Bron[1]);
		glTranslatef(3.45, 0, 0);


			tmp = cena_ammo - (cena_ammo / 10000) * 10000;
			if (tmp >= 1000)
				glCallList(HUD_Numbers[tmp / 1000]);
			glTranslatef(0.45, 0, 0);
			//Setki
			tmp = tmp - (tmp / 1000 * 1000);
			glCallList(HUD_Numbers[tmp / 100]);
			glTranslatef(0.45, 0, 0);
			//Dziesiatki
			tmp = tmp - (tmp / 100 * 100);

			glCallList(HUD_Numbers[tmp / 10]);
			glTranslatef(0.45, 0, 0);

			//Jednosci
			tmp = tmp - (tmp / 10 * 10);
			glCallList(HUD_Numbers[tmp]);
			glTranslatef(0.45, 0, 0);
			glCallList(HUD_Numbers[11]);
		}


		glPopMatrix();
		glPopAttrib();
	}
#pragma endregion


#pragma region BRON W PIERWSZYM SLOCIE
	//BRON W PIERWSZYM SLOCIE
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	if (first_weapon == -1)
		glBindTexture(GL_TEXTURE_2D, Empty->GetId());
	else
		glBindTexture(GL_TEXTURE_2D, HUD_Weapons[first_weapon]->GetId());

	
	
	if (height >= 1080)
		glTranslatef(width*0.05, height * 0.29, 0);
	else
		glTranslatef(width*0.05, height * 0.32, 0);
	glScalef(3, 1.5, 3);
	glBegin(GL_QUADS);
	if (id == first_weapon)
		glColor4f(color[0], color[1], color[2], 0.65f);
	else
		glColor4f(1.0, 1.0, 1.0, 0.65f);
	glVertex2f(-8, 0);
	glVertex2f(-8, 64);
	glVertex2f(0, 64);
	glVertex2f(0, 0);
	glTexCoord2f(0.1, 0); glVertex2i(0, 0);
	glTexCoord2f(0.1, 1); glVertex2i(0, 64);
	glTexCoord2f(1, 1); glVertex2i(64, 64);
	glTexCoord2f(1, 0); glVertex2i(64, 0);
	glColor4f(1.0, 1.0, 1.0, 0.65f);
	glVertex2f(64, 0);
	glVertex2f(64, 64);
	glVertex2f(72, 64);
	glVertex2f(72, 0);
	glEnd();

	glPopMatrix();
	glPopAttrib();

#pragma endregion


#pragma region BRON W DRUGIM SLOCIE

	//BRON W DRUGIM SLOCIE
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(width*0.05, height * 0.19, 0);
	glScalef(3, 1.5, 3);
	if (second_weapon == -1)
		glBindTexture(GL_TEXTURE_2D, Empty->GetId());
	else
		glBindTexture(GL_TEXTURE_2D, HUD_Weapons[second_weapon]->GetId());
	glBegin(GL_QUADS);
	if (id == second_weapon)
		glColor4f(color[0], color[1], color[2], 0.65f);
	else
		glColor4f(1.0, 1.0, 1.0, 0.65f);
	glVertex2i(-8, 0);
	glVertex2i(-8, 64);
	glVertex2i(0, 64);
	glVertex2i(0, 0);

	glTexCoord2f(0.1, 0); glVertex2i(0, 0);
	glTexCoord2f(0.1, 1); glVertex2i(0, 64);
	glTexCoord2f(1, 1); glVertex2i(64, 64);
	glTexCoord2f(1, 0); glVertex2i(64, 0);
	glColor4f(1.0, 1.0, 1.0, 0.65f);
	glVertex2i(64, 0);
	glVertex2i(64, 64);
	glVertex2i(72, 64);
	glVertex2i(72, 0);

	glEnd();

	glPopMatrix();
	glPopAttrib();
#pragma endregion


#pragma region PASEK ZDROWIA TEKST

	int pasek_zdrowia = health;
	if (pasek_zdrowia < 0) pasek_zdrowia = 0;
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glTranslatef(width*0.05, height * 0.08, 0.2);
	glRotatef(90, 1, 0, 0);
	glScalef(52, 52, 52);
	glTranslatef(1.6, 0, 0);
		glTranslatef(0.45, 0, 0);
		glCallList(HUD_Numbers[pasek_zdrowia / 100]);
		glTranslatef(0.45, 0, 0);
		glCallList(HUD_Numbers[(pasek_zdrowia - (pasek_zdrowia / 100) * 100) / 10]);
		glTranslatef(0.45, 0, 0);
		glCallList(HUD_Numbers[pasek_zdrowia % 10]);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopAttrib();
#pragma endregion


#pragma region PASEK ZDROWIA

	//PASEK ZDROWIA
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(width*0.04, height * 0.05, 0);
	glScalef(3.3, 1.2, 1.0);
	glBindTexture(GL_TEXTURE_2D, Health_bar->GetId());
	glBegin(GL_QUADS);
	glColor4f(1.0 / (pasek_zdrowia / 15 + 1), pasek_zdrowia*0.01, 0.0, 0.55f);
	glTexCoord2f(0.0, 0); glVertex2i(0, 0);
	glTexCoord2f(0.0, 1); glVertex2i(0, 64);
	glTexCoord2f(1, 1); glVertex2i(64, 64);
	glTexCoord2f(1, 0); glVertex2i(64, 0);
	glColor4f(1.0, 1.0, 1.0, 0.65f);
	glVertex2i(60, 0);
	glVertex2i(64, 64);
	glVertex2i(64, 64);
	glVertex2i(64, 0);

	glEnd();



	glPopMatrix();
	glPopAttrib();
#pragma endregion


#pragma region STAN ZOMBIE
	int zombie_count = game_manager->zombie_count();
	//PASEK ZDROWIA
	glPushAttrib(GL_CURRENT_BIT);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(width*0.8, height * 0.05, 0);
	glScalef(3.3, 1.2, 1.0);
	glBindTexture(GL_TEXTURE_2D, Zombie_left->GetId());
	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 0.0f, 0.55f);
	glTexCoord2f(0.0, 0); glVertex2i(0, 0);
	glTexCoord2f(0.0, 1); glVertex2i(0, 64);
	glTexCoord2f(1, 1); glVertex2i(64, 64);
	glTexCoord2f(1, 0); glVertex2i(64, 0);
	glColor4f(1.0, 1.0, 1.0, 0.65f);
	glVertex2i(60, 0);
	glVertex2i(64, 64);
	glVertex2i(64, 64);
	glVertex2i(64, 0);

	glEnd();
	glPopMatrix();
	glPopAttrib();
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(width*0.82, height * 0.08, 0.2);
	glRotatef(90, 1, 0, 0);
	glScalef(45, 45, 45);
	glTranslatef(1.3, 0, 0);
	if (zombie_count >= 100)
		glCallList(HUD_Numbers[zombie_count / 100]);
	glTranslatef(0.45, 0, 0);
	glCallList(HUD_Numbers[(zombie_count - (zombie_count / 100) * 100) / 10]);
	glTranslatef(0.45, 0, 0);
	glCallList(HUD_Numbers[zombie_count % 10]);


	glPopMatrix();

	glPushMatrix();
	int fala = game_manager->wave();
	glTranslatef(width*0.93, height * 0.01, 0.2);
	glRotatef(90, 1, 0, 0);
	glScalef(43, 43, 43);
	glCallList(Fala);
	glTranslatef(1.3, 0, 0);
	if (fala >= 100)
	{
		glCallList(HUD_Numbers[fala / 100]);
		glTranslatef(0.45, 0, 0);
	}
	if (fala >= 10)
	{

	glCallList(HUD_Numbers[(fala - (fala / 100) * 100) / 10]);
	glTranslatef(0.45, 0, 0);
	}
	glCallList(HUD_Numbers[fala % 10]);


	glPopMatrix();
	glEnable(GL_TEXTURE_2D);

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
