#include "StdAfx.h"

#define PI 3.14159265 



#pragma region zmienne pomocnicze

GLuint obiekt;

int weapon_id;
int op = 0;
int multiplier;

#pragma endregion
GameManager *gamemanager;


#pragma region Dzwieki
Sound *footsteps;
#pragma endregion

#pragma region Obiekty klas

//Skrzynia
Coins *coins;
weapon_sounds *weapon_sound;
load_models *bronie;
BuyWeapon *kup_bronie;
//Pociski
Bullet *pociski;

//Czcionki


//shadery
Shading shaders;
GLuint program;
GLuint program2;
#pragma endregion







// Konstruktor.
CScene::CScene(void)
{
	DrawCollisions = false;
	DrawNormals = false;
	MarkCollision = false;
}

// Destruktor - sprz¹tamy po sobie.
CScene::~CScene(void)
{
	if (Skydome != NULL) {
		delete Skydome;
	}
	if (Terrain != NULL) {
		delete Terrain;
	}
	delete pociski;
}

void CScene::LoadBuildings()
{

	//Ladowanie drzew
	tree = LoadObj("Data/Models/Buildings/tree.obj");
	tree_tex = new CTexture("Data/Textures/Buildings/tree.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	for (int i = 0; i < 50; i++)
	{
		float rand_x = (rand() % 1000) / ((rand() % 70) + 1) - 10;
		float rand_z = (rand() % 1000) / ((rand() % 70)+1) - 10;

		tree_pos[i].x = rand_x;
		tree_pos[i].z = rand_z;
		tree_pos[i].y = 0;


	}



	buildings = new model[3];
	buildings[0].Building_model = LoadObj("Data/Models/Buildings/house.obj");
	buildings[0].Building_texture = new CTexture("Resources/Grass.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	buildings[0].polozenie[0] = 0;
	buildings[0].polozenie[1] = 0;
	buildings[0].polozenie[2] = 0;
	buildings[0].scale[0] = 1.0;
	buildings[0].scale[1] = 1.0;
	buildings[0].scale[2] = 1.0;
	buildings[0].rotate[0] = 0;
	buildings[0].rotate[1] = 0;
	buildings[0].rotate[2] = 0;
	buildings[0].rotate[3] = 0;



	buildings[1].Building_model = LoadObj("Data/Models/Architecture/statue_1.obj");
	buildings[1].Building_texture = new CTexture("Data/Textures/Buildings/Statue/statue02.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	buildings[1].polozenie[0] = -15;
	buildings[1].polozenie[1] = 0;
	buildings[1].polozenie[2] = 0;
	buildings[1].scale[0] = 1.0;
	buildings[1].scale[1] = 1.0;
	buildings[1].scale[2] = 1.0;
	buildings[1].rotate[0] = 0;
	buildings[1].rotate[1] = 0;
	buildings[1].rotate[2] = 0;
	buildings[1].rotate[3] = 0;


	buildings[2].Building_model = LoadObj("Data/Models/Architecture/statue_2.obj");
	buildings[2].Building_texture = new CTexture("Data/Textures/Buildings/Statue/statue01.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	buildings[2].polozenie[0] = -15;
	buildings[2].polozenie[1] = 0;
	buildings[2].polozenie[2] = 0;
	buildings[2].scale[0] = 1.0;
	buildings[2].scale[1] = 1.0;
	buildings[2].scale[2] = 1.0;
	buildings[2].rotate[0] = 0;
	buildings[2].rotate[1] = 0;
	buildings[2].rotate[2] = 0;
	buildings[2].rotate[3] = 0;


}


// Inicjalizacja sceny.
void CScene::Initialize(void) {
	
	
	#pragma region INICJACJA SHADEROW
	//GLuint program = shaders.LoadShader("Data/Shaders/phong.vert", "Data/Shaders/phong.frag");
	GLuint program2 = shaders.LoadShader("Data/Shaders/phong2.vert", "Data/Shaders/phong2.frag");
	glUseProgram(program2);
#pragma endregion


	#pragma region Ustawienia graficzne

		// Ustawienie wszelkiego rodzaju rzeczy, które s¹ charakterystyczne dla tej konkretnej sceny.
		glEnable(GL_LIGHT0);

		glEnable(GL_FOG);
		float gl_fogcolor[] = { 0.7f, 0.7f, 0.7f, 1.0f };
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, gl_fogcolor);
		glFogf(GL_FOG_START, 2.0f);
		glFogf(GL_FOG_END, 62.0f);

		Player.pos.x = 0.0f;
		Player.pos.y = 0.3f;
		Player.pos.z = 0.0f;

		Player.dir.x = 0.0f;
		Player.dir.y = 0.0f;
		Player.dir.z = -1.0f;

		Player.speed = .25f;

#pragma endregion


	#pragma region Ladowanie obiektow do gry
		weapon_sound = new weapon_sounds;
		pociski = new Bullet;
		glEnable(GL_TEXTURE_2D);
		LoadBuildings();
		Player.LoadBMPHUD();
		glDisable(GL_TEXTURE_2D);
		bronie = new load_models;
		kup_bronie = new BuyWeapon(bronie);
		coins = new Coins;
		gamemanager = new GameManager;


#pragma endregion


	#pragma region Przypisanie graczowi bron

		Player.first_slot = new BLASTER;
		Player.actual_weapon = Player.first_slot;
		Player.second_slot = NULL;
		Player.second_slot = new M249;

	#pragma endregion



	footsteps = Sound::loadWAVE("Data/Wav/footsteps.wav", true);


	#pragma region Zawartosc sceny
	
		// Scena zawieraæ bêdzie skydome...
		Skydome = new CSkydome();
		Skydome->Initialize();

		// ...oraz teren.
	//	Terrain = new CTerrain();
	//	Terrain->Initialize();


		
		// Dodanie wszystkich obiektów sceny do wektora, po którym póŸniej bêdziemy iterowaæ chc¹c je rysowaæ.
		// Dlatego w³aœnie wygodnie jest, gdy wszystkie obiekty sceny dziedzicz¹ po jednej, wspólnej klasie bazowej (CSceneObject).
		
		Objects = new vector<CSceneObject *>();

		// Definicje po³o¿enia naszych œcian. Ka¿da kolejna czwórka wektorów to jeden quad.
		vec3 walls[][4] = {
			{ vec3( -22.0f,  20.0f, 15.0f), vec3( -22.0f,  -2.0f, 15.0f), vec3( 15.0f,  -2.0f, 15.0f), vec3( 15.0f,  20.0f, 15.0f) },
			{ vec3( 15.0f,  20.0f, 15.0f), vec3( 15.0f,  -2.0f, 15.0f), vec3(15.0f,  -2.0f, -5.0f), vec3(15.0f,  20.0f, -5.0f) },
			{ vec3(15.0f,  20.0f, -5.0f), vec3(15.0f,  -2.0f, -5.0f), vec3(-22.0f,  -2.0f, -5.0f), vec3(-22.0f,  20.0f, -5.0f) },
			{ vec3(-22.0f,  20.0f, -5.0f), vec3(-22.0f,  -2.0f, -5.0f), vec3(-22.0f,  -2.0f, 15.0f), vec3(-22.0f,  20.0f, 15.0f) },
			{ vec3(-3.0f,  0.0f, -1.0f), vec3(-3.0f,  1.0f, -1.0f), vec3(-1.0f,  1.0f,  1.0f), vec3(-1.0f,  0.0f,  1.0f) },
			{ vec3(-1.0f,  0.0f,  1.0f), vec3(-1.0f,  1.0f,  1.0f), vec3(-3.0f,  1.0f,  1.0f), vec3(-3.0f,  0.0f,  1.0f) },
			{ vec3(-3.0f,  0.0f,  2.0f), vec3(-3.0f,  1.0f,  2.0f), vec3(-1.0f,  1.0f,  2.0f), vec3(-1.0f,  0.0f,  2.0f) },
			{ vec3(-3.0f,  0.0f, -2.0f), vec3(-3.0f,  1.0f, -2.0f), vec3(-6.0f,  1.0f, -2.0f), vec3(-6.0f,  0.0f, -2.0f) },
			{ vec3(-3.0f,  0.0f,  1.0f), vec3(-3.0f,  1.0f,  1.0f), vec3(-3.0f,  1.0f, -2.0f), vec3(-3.0f,  0.0f, -2.0f) },
			{ vec3(-6.0f,  0.0f, -2.0f), vec3(-6.0f,  1.0f, -2.0f), vec3(-6.0f,  1.0f,  5.0f), vec3(-6.0f,  0.0f,  5.0f) },
			{ vec3(-6.0f,  0.0f,  5.0f), vec3(-6.0f,  1.0f,  5.0f), vec3(-4.0f,  1.0f,  4.0f), vec3(-4.0f,  0.0f,  4.0f) },
			{ vec3(-4.0f,  0.0f,  4.0f), vec3(-4.0f,  1.0f,  4.0f), vec3(-3.0f,  1.0f,  2.0f), vec3(-3.0f,  0.0f,  2.0f) },
			{ vec3(-5.5f,  0.0f,  0.0f), vec3(-5.0f,  0.3f,  1.0f), vec3(-4.0f,  0.3f,  1.0f), vec3(-4.0f,  0.0f,  0.0f) },
			{ vec3(-5.5f,  0.0f,  3.0f), vec3(-4.0f,  0.0f,  3.0f), vec3(-4.0f,  0.3f,  2.0f), vec3(-5.0f,  0.3f,  2.0f) },
			{ vec3(-5.0f,  0.3f,  1.0f), vec3(-5.0f,  0.3f,  2.0f), vec3(-4.0f,  0.3f,  2.0f), vec3(-4.0f,  0.3f,  1.0f) },
			{ vec3(-1.0f,  0.0f,  2.0f), vec3(-1.0f,  1.0f,  2.0f), vec3( 1.0f,  1.0f,  3.0f), vec3( 1.0f,  0.0f,  3.0f) },
			{ vec3( 1.0f,  0.0f,  3.0f), vec3( 1.0f,  1.0f,  3.0f), vec3( 4.0f,  1.0f,  0.0f), vec3( 4.0f,  0.0f,  0.0f) },
			{ vec3( 4.0f,  0.0f,  0.0f), vec3( 4.0f,  1.0f,  0.0f), vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f,  0.0f, -1.0f) },
			{ vec3( 1.0f,  0.0f, -1.0f), vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f,  1.0f, -3.0f), vec3( 1.0f,  0.0f, -3.0f) },
			{ vec3(-4.0f,  0.0f,  0.0f), vec3(-4.0f,  0.3f,  1.0f), vec3(-4.0f,  0.3f,  2.0f), vec3(-4.0f,  0.0f,  3.0f) },
			{ vec3(-5.5f,  0.0f,  0.0f), vec3(-5.5f,  0.0f,  3.0f), vec3(-5.0f,  0.3f,  2.0f), vec3(-5.0f,  0.3f,  1.0f) }
		};

		// Tyle mamy œcian.
		int N = 4;
		
		// Zamieniamy powy¿sz¹ tablicê na obiekty typu CWall, które dodamy do listy obiektów na scenie.
		for (int i = 0; i < N; ++i) {
			CWall *w = new CWall(walls[i][0], walls[i][1], walls[i][2], walls[i][3]);
			sprintf(w->Name, "Wall %d", i); // Nadanie nazwy, aby np. mo¿na by³o póŸniej ³atwo dowiedzieæ siê z czym mamy kolizjê.
			w->Initialize();
	//		Objects->push_back(w); // Dodanie do wektora rysowanych/przetwarzanych obiektów.
		}
		
	#pragma endregion
	
}



// Aktualizacja œwiata gry.
void CScene::Update(void) {



#pragma endregion


	#pragma region Predkosc gracza zalezna od typu noszonej broni
	float current_speed = 1;
	switch (Player.actual_weapon->type) {
	case 1: current_speed = 1.2; break;
	case 2: current_speed =  1.0; break;
	case 3: current_speed = 0.95; break;
	case 4: current_speed = 0.8; break;
	default: current_speed = 1.0;
	}

#pragma endregion


	#pragma region Przechwytywanie myszy
		if (captureMouse) {
			Player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX) + Player.actual_weapon->recoilY;
			Player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY) + Player.actual_weapon->recoilX;
			Player.actual_weapon->recoilX = 0;
			Player.actual_weapon->recoilY = 0;
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

		}

#pragma endregion


	#pragma region blyskawiczne dodanie broni
	//Blyskawiczne dodanie nowej broni za pomoca przycisku '+'. Przydatne przy sprawdzaniu kazdej broni
/*
		int tmp = op;
		if (keystate['+']) {
			op++;
		}

		if (tmp != op) {
			weapon *tmp = Player.first_slot;
			int s = op % 10;
			switch (s) {
			case 0: Player.first_slot = new AK74U; Player.actual_weapon = Player.first_slot; break;
			case 1: Player.first_slot = new MP5K; Player.actual_weapon = Player.first_slot; break;
			case 2: Player.first_slot = new SCARH; Player.actual_weapon = Player.first_slot; break;
			case 3: Player.first_slot = new M9; Player.actual_weapon = Player.first_slot; break;
			case 4: Player.first_slot = new AUG; Player.actual_weapon = Player.first_slot; break;
			case 5: Player.first_slot = new M249; Player.actual_weapon = Player.first_slot; break;
			case 6: Player.first_slot = new DESERTDEAGLE; Player.actual_weapon = Player.first_slot; break;
			case 7: Player.first_slot = new BIZON; Player.actual_weapon = Player.first_slot; break;
			case 8: Player.first_slot = new M4A4; Player.actual_weapon = Player.first_slot; break;
			case 9: Player.first_slot = new BLASTER; Player.actual_weapon = Player.first_slot; break;
			}
			delete tmp;
		}
		*/
#pragma endregion	

		if (Player.player_dead == false) {
#pragma region Lewy i prawy przycisk myszy
			if (Player.left_mouse_button == true)
			{
				Player.actual_weapon->shooting = true;
				Player.actual_weapon->Shoot(weapon_sound, pociski, &Player.pos, &Player.dir, Player.actual_weapon);
			}
			else
			{
				Player.actual_weapon->shooting = false;
			}
			if (Player.right_mouse_button == true)
			{

			}
			else
			{


			}
#pragma endregion


#pragma region ZAMIANA BRONI
			if (Player.actual_weapon->change_weapon_now == true)
			{
				Player.actual_weapon->change_weapon_now = false;
				Player.actual_weapon->change_weapon = false;
				if (Player.actual_weapon != Player.first_slot)
				{
					Player.actual_weapon = Player.first_slot;
				}
				else
					Player.actual_weapon = Player.second_slot;

			}
			else
			{
				if (keystate['1']) {
					if (Player.first_slot != NULL && Player.first_slot != Player.actual_weapon && Player.actual_weapon->reloading == false && Player.actual_weapon->change_weapon == false)
					{
						Player.actual_weapon->change_weapon = true;
						Player.actual_weapon->timestamp = T + Player.actual_weapon->weapon_hideshow;
					}

				}
				if (keystate['2']) {
					if (Player.second_slot != NULL && Player.second_slot != Player.actual_weapon && Player.actual_weapon->reloading == false && Player.actual_weapon->change_weapon == false)
					{
						Player.actual_weapon->change_weapon = true;
						Player.actual_weapon->timestamp = T + Player.actual_weapon->weapon_hideshow;
					}
				}
			}

#pragma endregion
			if (keystate[0])
			{
				cout << "CAPS LOCK" << endl;
			}
			//	cout << "X = " << Player.pos.x << ", Z = " << Player.pos.z << endl;
#pragma region PORUSZANIE SIE I INNE AKCJE


			if (keystate['r'])
			{
				Player.actual_weapon->Reload(weapon_sound);
			}




			if (keystate['w']) {

				if (keystate['a'] || keystate['d'])
				{
					Player.distance += Player.speed*current_speed;
					Player.velM = Player.speed*current_speed;
				}
				else
				{
					Player.distance += Player.speed*current_speed;
					Player.velM = Player.speed*current_speed;
				}
			}


			if (keystate['s']) {

				if (keystate['a'] || keystate['d'])
				{
					Player.distance += Player.speed * current_speed;
					Player.velM = -Player.speed / sqrt(2) * current_speed;
				}
				else
				{
					Player.distance += Player.speed *current_speed;
					Player.velM = -Player.speed*current_speed;
				}
			}
			if (keystate['a']) {

				if (keystate['w'] || keystate['s'])
				{
					Player.distance += 0;
					Player.velS = -Player.speed / sqrt(2)*current_speed;
				}
				else
				{
					Player.distance += Player.speed*current_speed;
					Player.velS = -Player.speed*current_speed;
				}
			}
			if (keystate['d']) {
				Player.velS = Player.speed*current_speed;
				if (keystate['w'] || keystate['s'])
				{
					Player.distance += 0;
					Player.velS = Player.speed / sqrt(2)*current_speed;
				}
				else
				{
					Player.distance += Player.speed*current_speed;
					Player.velS = Player.speed*current_speed;
				}

			}

			float T = acos(Player.dir.y);
			float G = atan2(Player.dir.z, Player.dir.x);
			T -= Player.velRX * .03f;
			G += Player.velRY * .03f;
			Player.dir.x = sin(T) * cos(G);
			Player.dir.y = cos(T);
			Player.dir.z = sin(T) * sin(G);



#pragma endregion


#pragma region PORUSZANIE SIE I INNE AKCJE 2

			vec3 per;
			per.x = -Player.dir.z;
			per.y = 0;
			per.z = Player.dir.x;

			vec3 nextPlayerPos = Player.pos;

			nextPlayerPos.x += Player.dir.x * Player.velM * .1f;
			if (free3DMovement) {
				nextPlayerPos.y += Player.dir.y * Player.velM * .1f;
			}
			else {
				// Niby-grawitacja
				nextPlayerPos.y -= .1f;
			}
			nextPlayerPos.z += Player.dir.z * Player.velM * .1f;

			nextPlayerPos.x += per.x * Player.velS * .1f;
			if (free3DMovement) {
				nextPlayerPos.y += Player.dir.y * Player.velM * .1f;
			}
			nextPlayerPos.z += per.z * Player.velS * .1f;


			// Uniemo¿liwiamy zejœcie gracza poni¿ej poziomu terenu
			nextPlayerPos.y = __max(0.3f, nextPlayerPos.y);
			//aktualizacja zdrowia gracza itp
			Player.PlayerUpdate();

#pragma endregion

			//Zmiana polozenia gracza
			Player.pos = CCollisionDetection::GetPositionAfterWorldCollisions(Player.pos, nextPlayerPos, Player, Objects);
		}

	#pragma region Aktualizacja stanu zombie
		for (int i = 0; i < 50; i++)
		{
			if (gamemanager->undead[i]->slained == false)
			{
				gamemanager->undead[i]->MoveToPlayer(Player.pos, &Player);
			
				for (int j = 0; j < 50; j++)
				{
					if (j != i && gamemanager->undead[i]->slained == false) {
					
						gamemanager->undead[i]->zombie_collision(gamemanager->undead[j]);
					}

				}
				gamemanager->undead[i]->pos = CCollisionDetection::GetPositionAfterWorldCollisions(gamemanager->undead[i]->pos, gamemanager->undead[i]->nextZombiePos, Player, Objects);
				pociski->check_collision(gamemanager->undead[i], &Player, coins, gamemanager);
			}
		}

#pragma endregion

		gamemanager->Update();
		cout << Player.pos.x << ", " << Player.pos.z << endl;

	#pragma region Player lookdir update

		//Limiter lookdira
		if (Player.dir.y > 0.95)
			Player.dir.y = 0.95;
		if (Player.dir.y < -0.95)
			Player.dir.y = -0.95;

		Player.velRX /= 1.2;
		Player.velRY /= 1.2;
		Player.velM /= 1.2;
		Player.velS /= 1.2;

	#pragma endregion


	#pragma region Aktualizacja obiektow sceny

		// Ró¿ne obiekty mog¹ potrzebowaæ aktualizacji - np. poruszaj¹cy siê wrogowie.
	/*	for (int i = 0; i < Objects->size(); ++i) {
			Objects->at(i)->Update();
		}
		*/
	
//		Terrain->Update();
		Skydome->Update();
		kup_bronie->Update(&Player);
	#pragma endregion


	#pragma region Update pociskow na scenie
		pociski->update();
#pragma endregion


	#pragma region Aktualizacja coinow

			coins->update(&Player);

	#pragma endregion

}

// Narysowanie sceny.
void CScene::Render(void) {

	
	#pragma region Kamera
		gluLookAt(
			Player.pos.x + Player.cam.x, Player.pos.y + Player.cam.y, Player.pos.z + Player.cam.z,
			Player.pos.x + Player.cam.x + Player.dir.x + cos(Player.distance / 3)*0.02, Player.pos.y + Player.cam.y + Player.dir.y + sin(Player.distance / 3)*0.02, Player.pos.z + Player.cam.z + Player.dir.z+cos(Player.distance/3)*0.02,
			0.0f, 1.0f, 0.0f
		);
	#pragma endregion

	#pragma region Proces rysowania broni
		if (Player.player_dead == false) {
			weapon_id = Player.actual_weapon->Get_id() - 1;
			glPushMatrix();
			Player.WeaponPos();
			bronie->draw_weapons(weapon_id);
			glPopMatrix();
		}
#pragma endregion

	#pragma region Swiatlo
	
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_TEXTURE_2D);

		float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_pos[] = { 0, 15, 0, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);



		float l0_amb1[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float l0_dif1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_spe1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_pos1[] = { Player.pos.x, 1, Player.pos.z, 1.0f };
		glLightfv(GL_LIGHT1, GL_AMBIENT, l0_amb1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, l0_dif1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, l0_spe1);
		glLightfv(GL_LIGHT1, GL_POSITION, l0_pos1);

#pragma endregion

#pragma region Rysowanie coinow
				glDisable(GL_LIGHTING);
		coins->render();
		glEnable(GL_LIGHTING);
		kup_bronie->Render();
#pragma endregion


#pragma region rysowanie skrzyn / wyswietlanie wszystkich broni

#pragma endregion


	#pragma region Rysowanie Budynków
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glRotatef(buildings[i].rotate[0], buildings[i].rotate[1], buildings[i].rotate[2], buildings[i].rotate[3]);
		glTranslatef(buildings[i].polozenie[0], buildings[i].polozenie[1], buildings[i].polozenie[2]);
		glScalef(buildings[i].scale[0], buildings[i].scale[1], buildings[i].scale[2]);
		
		glBindTexture(GL_TEXTURE_2D, buildings[i].Building_texture->GetId());
		glCallList(buildings[i].Building_model);

		glPopMatrix();
	}

	glBindTexture(GL_TEXTURE_2D, tree_tex->GetId());
	for (int i = 0; i < 50; i++)
	{
			glPushMatrix();
			glTranslatef(tree_pos[i].x, tree_pos[i].y, tree_pos[i].z);
			glCallList(tree);
			glPopMatrix();
	}

#pragma endregion

	#pragma region Skydome

		glDisable(GL_FOG);


		Skydome->Position = Player.pos;
		Skydome->Render();
		
		glEnable(GL_FOG);

	#pragma endregion

	#pragma region Teren

	//	Terrain->Render();

	#pragma endregion
	
	#pragma region Obiekty

		// Narysowanie wszystkich obiektów sceny (w tym przypadku - tylko œcian, ale do Objects mo¿na dodaæ te¿ wszystkie inne obiekty).

	#pragma endregion




	#pragma region Rysowanie zombie
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);

		for (int i = 0; i < 50; i++)
		{
			gamemanager->undead[i]->Render(Player.pos);
		}
		
#pragma endregion




	#pragma region Rysowanie pociskow
		pociski->render();
	//	bronie->show_weapons();
#pragma endregion


	#pragma region Pomocnicze rysowanie kolizji
		// Narysowanie elipsoidy gracza oraz znalezionego punktu kolizji jeœli u¿ytkownik sobie tego ¿yczy (klawisz "K").
		if (DrawCollisions) {
			glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glLineWidth(1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glPushMatrix();
				glTranslatef(Player.pos.x, Player.pos.y, Player.pos.z);
				glScalef(Player.collisionEllipsoid->r.x, Player.collisionEllipsoid->r.y, Player.collisionEllipsoid->r.z);
				glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
				glutWireSphere(1.0f, 64, 64);
			glPopMatrix();
			if (MarkCollision) {
				glColor3f(1.0f, 0.0f, 1.0f);
				glPointSize(16.0f);
				glDisable(GL_DEPTH_TEST);
				glBegin(GL_POINTS);
					glVertex3f(LastCollisionPoint.x, LastCollisionPoint.y, LastCollisionPoint.z);
				glEnd();
				glEnable(GL_DEPTH_TEST);
			}
			glEnable(GL_LIGHTING);
		}
	#pragma endregion
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		//glDisable(GL_LIGHTING);
		glColor3f(0.74, 0.74, 0.74);
		glScalef(2, 2, 2);

		glTranslatef(0, 0.5, 0);
		glScalef(0.1, 0.1, 0.1);

		
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();

			for (int i = 0; i < Objects->size(); ++i) {
			Objects->at(0)->Render();
			}
		glDisable(GL_LIGHTING);

#pragma region RYSOWANIE HUD - SLOTY

		int first_slot;
		int second_slot;

		if (Player.first_slot != NULL)
			first_slot = Player.first_slot->Get_id() - 1;
		else
			first_slot = -1;
		if (Player.second_slot != NULL)
			second_slot = Player.second_slot->Get_id() - 1;
		else
			second_slot = -1;
#pragma endregion


#pragma region RYSOWANIE HUD
		Player.HUD(weapon_id,first_slot,second_slot,Player.actual_weapon->Get_ammo1(),Player.actual_weapon->Get_ammo2(), gamemanager, kup_bronie);
	//Player.DrawTextHUD((char *)"TEKST");
	//	glUseProgram(program);
#pragma endregion

}
