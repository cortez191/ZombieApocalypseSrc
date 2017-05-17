#include"stdafx.h"
#include"Weapons.h"




load_models::load_models() {




	cout << "\nLADUJE MODELE BRONI\n";
	//Wczytuje model broni P90
	MP5K = LoadObj("Data/Models/Weapons/MP5K/MP5K.obj");
 	MP5K_texture = new CTexture("Data/Models/Weapons/MP5K/MP5K.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	M4A4 = LoadObj("Data/Models/Weapons/M4A4/M4A4.obj");
	M4A4_texture = new CTexture("Data/Models/Weapons/M4A4/M4A4.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	AKS74U = LoadObj("Data/Models/Weapons/AKS-74U/AKS-74U.obj");
	AKS74U_texture = new CTexture("Data/Models/Weapons/AKS-74U/aks74u.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	SCARH = LoadObj("Data/Models/Weapons/SCAR-H/SCAR-H.obj");
	SCARH_texture = new CTexture("Data/Models/Weapons/SCAR-H/SCAR-H.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	M9 = LoadObj("Data/Models/Weapons/M9/M9.obj");
	M9_texture = new CTexture("Data/Models/Weapons/M9/M9.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	AUG = LoadObj("Data/Models/Weapons/AUG/AUG.obj");
	AUG_texture = new CTexture("Data/Models/Weapons/AUG/AUG.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	M249 = LoadObj("Data/Models/Weapons/M249/M249.obj");
	M249_texture = new CTexture("Data/Models/Weapons/M249/M249.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	Bizon = LoadObj("Data/Models/Weapons/Bizon/Bizon.obj");
	Bizon_texture = new CTexture("Data/Models/Weapons/Bizon/Bizon.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	Blaster = LoadObj("Data/Models/Weapons/Blaster/Blaster.obj");
	Blaster_texture = new CTexture("Data/Models/Weapons/Blaster/Blaster.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);


	DesertDeagle = LoadObj("Data/Models/Weapons/DesertDeagle/DesertDeagle.obj");
	DesertDeagle_texture = new CTexture("Data/Models/Weapons/DesertDeagle/DesertDeagle.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);



	postac.LoadModel("Data/Models/Characters/Player/player.md2");
	postac.LoadSkin("Data/Models/Characters/Player/player.bmp");
	cout << "\nWSZYSTKIE MODELE BRONI ZALADOWANE\n";
}

void load_models::draw_weapons(int type)
{
	//glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	switch (type)
	{
	case 0: glBindTexture(GL_TEXTURE_2D, MP5K_texture->GetId()); break;
	case 1:glBindTexture(GL_TEXTURE_2D, M4A4_texture->GetId()); break;
	case 2:glBindTexture(GL_TEXTURE_2D, AKS74U_texture->GetId()); break;
	case 3:glBindTexture(GL_TEXTURE_2D, SCARH_texture->GetId()); break;
	case 4:glBindTexture(GL_TEXTURE_2D, M9_texture->GetId()); break;
	case 5:glBindTexture(GL_TEXTURE_2D, AUG_texture->GetId()); break;
	case 6:glBindTexture(GL_TEXTURE_2D, M249_texture->GetId()); break;
	case 7:glBindTexture(GL_TEXTURE_2D, DesertDeagle_texture->GetId()); break;
	case 8:glBindTexture(GL_TEXTURE_2D, Bizon_texture->GetId()); break;
	case 9:glBindTexture(GL_TEXTURE_2D, Blaster_texture->GetId()); break;
	default: glBindTexture(GL_TEXTURE_2D, M4A4_texture->GetId());
	}
	//glBindTexture(GL_TEXTURE_2D, M4A4_texture->GetId());
	glRotatef(270, 0, 1, 0);
	
	//Parametry

	

	//glScalef(0.03, 0.03, 0.03);
	switch (type)
	{
	case 0: glCallList(MP5K); break;
	case 1:glCallList(M4A4); break;
	case 2:glCallList(AKS74U); break;
	case 3:glCallList(SCARH); break;
	case 4:glCallList(M9); break;
	case 5:glCallList(AUG); break;
	case 6:glCallList(M249); break;
	case 7:glCallList(DesertDeagle); break;
	case 8:glCallList(Bizon); break;
	case 9:glCallList(Blaster); break;
	default: glCallList(M4A4);
	}
	postac.DrawModel(0);


	glPopMatrix();

	//glEnable(GL_LIGHTING);
}

void load_models::show_weapons() {
	glDisable(GL_LIGHTING);
			glPushMatrix();
			glPushMatrix();
			glTranslatef(0, 0.5 + sin(T*0.001) / 15, 0);
			glRotatef(T*0.03, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, M4A4_texture->GetId());
			glCallList(M4A4);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.5, 0.5 + sin(T*0.001) / 15, 0);
			glRotatef(T*0.03, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, MP5K_texture->GetId());
			glCallList(MP5K);


			glPopMatrix();

			glPushMatrix();
			glTranslatef(1.0, 0.5 + sin(T*0.001) / 15, 0);
			glRotatef(T*0.03, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, AKS74U_texture->GetId());
			glCallList(AKS74U);


			glPopMatrix();
			glPushMatrix();
			glTranslatef(1.5, 0.5 + sin(T*0.001) / 15, 0);
			glRotatef(T*0.03, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, SCARH_texture->GetId());
			glCallList(SCARH);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(2.0, 0.5 + sin(T*0.001) / 15, 0);
			glRotatef(T*0.03, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, M9_texture->GetId());
			glCallList(M9);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(2.5, 0.5 + sin(T*0.001) / 15, 0);
			glRotatef(T*0.03, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, AUG_texture->GetId());
			glCallList(AUG);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(3.0, 0.5 + sin(T*0.001) / 15, 0);
			glRotatef(T*0.03, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, M249_texture->GetId());
			glCallList(M249);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(3.5, 0.5 + sin(T*0.001) / 15, 0);
			glRotatef(T*0.03, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, DesertDeagle_texture->GetId());
			glCallList(DesertDeagle);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(4.0, 0.5 + sin(T*0.001) / 15, 0);
			glRotatef(T*0.03, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, Bizon_texture->GetId());
			glCallList(Bizon);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(4.5, 0.5 + sin(T*0.001) / 15, 0);
			glRotatef(T*0.03, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, Blaster_texture->GetId());
			glCallList(Blaster);
			glPopMatrix();


			glPopMatrix();


	glEnable(GL_LIGHTING);
}



AK74U::AK74U()
{
	name = "AKS74U";
	special = false;
	type = 2;
	id = 3;
	weapon_damage = 45;
	weapon_range = 150;
	weapon_cooldown = 100; //w milisekundach
	weapon_reload_time = 2800; //w milisekundach
	weapon_hideshow = 1200;
	max_ammo = 110;
	max_ammo_magazine = 30;
	current_ammo = 110;
	current_ammo_magazine = 30;
	recoil = 0.11;
	offset[0][0] = 0.0f;
	offset[0][1] = 0.18f;
	offset[0][2] = 0.0f;

	offset[1][0] = 0.0f;
	offset[1][1] = 0.07f;
	offset[1][2] = 0.0f;

	offset[2][0] = 0.0f;
	offset[2][1] = -0.04f;
	offset[2][2] = 0.0f;

	offset[3][0] = -0.09f;
	offset[3][1] = 0.0f;
	offset[3][2] = -0.03f;
}

MP5K::MP5K()
{
	name = "MP5K";
	special = false;
	type = 2;
	id = 1;
	weapon_damage = 45;
	weapon_range = 150;
	weapon_cooldown = 95; //w milisekundach
	weapon_reload_time = 2100; //w milisekundach
	weapon_hideshow = 1000;
	max_ammo = 140;
	max_ammo_magazine = 40;
	current_ammo = 140;
	current_ammo_magazine = 40;
	recoil = 0.1;
	

	offset[0][0] = 0.0f;
	offset[0][1] = 0.18f;
	offset[0][2] = 0.0f;

	offset[1][0] = 0.0f;
	offset[1][1] = 0.07f;
	offset[1][2] = 0.0f;

	offset[2][0] = 0.0f;
	offset[2][1] = -0.04f;
	offset[2][2] = 0.0f;

	offset[3][0] = -0.09f;
	offset[3][1] = 0.0f;
	offset[3][2] = -0.03f;
}

M4A4::M4A4()
{
	name = "M4A4";
	special = false;
	type = 3;
	id = 2;
	weapon_damage = 50;
	weapon_range = 150;
	weapon_cooldown =105; //w milisekundach
	weapon_reload_time = 2300; //w milisekundach
	weapon_hideshow = 1400;
	max_ammo = 100;
	max_ammo_magazine = 30;
	current_ammo = 100;
	current_ammo_magazine = 30;
	recoil = 0.15;

	offset[0][0] = 0.0f;
	offset[0][1] = 0.18f;
	offset[0][2] = 0.0f;

	offset[1][0] = 0.0f;
	offset[1][1] = 0.07f;
	offset[1][2] = 0.0f;

	offset[2][0] = 0.0f;
	offset[2][1] = -0.04f;
	offset[2][2] = 0.0f;

	offset[3][0] = -0.07f;
	offset[3][1] = -0.005f;
	offset[3][2] = -0.03f;


}

SCARH::SCARH()
{
	name = "SCARH";
	special = false;
	type = 3;
	id = 4;
	weapon_damage = 58;
	weapon_range = 150;
	weapon_cooldown = 105; //w milisekundach
	weapon_reload_time = 2850; //w milisekundach
	weapon_hideshow = 1500;
	max_ammo = 75;
	max_ammo_magazine = 20;
	current_ammo = 75;
	current_ammo_magazine = 20;
	recoil = 0.06;

	offset[0][0] = 0.0f;
	offset[0][1] = 0.18f;
	offset[0][2] = 0.0f;

	offset[1][0] = 0.0f;
	offset[1][1] = 0.07f;
	offset[1][2] = 0.0f;

	offset[2][0] = 0.0f;
	offset[2][1] = -0.04f;
	offset[2][2] = 0.0f;

	offset[3][0] = -0.09f;
	offset[3][1] = 0.0f;
	offset[3][2] = -0.03f;
}

M9::M9()
{
	name = "M9";
	special = false;
	type = 1;
	id = 5;
	weapon_damage = 25;
	weapon_range = 150;
	weapon_cooldown = 340; //w milisekundach
	weapon_reload_time = 2500; //w milisekundach
	weapon_hideshow = 500;

	max_ammo = 45;
	max_ammo_magazine = 12;
	current_ammo = 45;
	current_ammo_magazine = 12;
	recoil = 0.18;

	offset[0][0] = 0.0f;
	offset[0][1] = 0.18f;
	offset[0][2] = 0.0f;

	offset[1][0] = 0.0f;
	offset[1][1] = 0.07f;
	offset[1][2] = 0.0f;

	offset[2][0] = 0.0f;
	offset[2][1] = -0.04f;
	offset[2][2] = 0.0f;

	offset[3][0] = -0.09f;
	offset[3][1] = 0.0f;
	offset[3][2] = -0.03f;

}

AUG::AUG()
{
	name = "AUG";
	special = false;
	type = 3;
	id = 6;
	weapon_damage = 40;
	weapon_range = 190;
	weapon_cooldown = 100; //w milisekundach
	weapon_reload_time = 2850; //w milisekundach
	weapon_hideshow = 1350;
	max_ammo = 120;
	max_ammo_magazine = 42;
	current_ammo = 120;
	current_ammo_magazine = 42;
	recoil = 0.16;

	offset[0][0] = 0.0f;
	offset[0][1] = 0.18f;
	offset[0][2] = 0.0f;

	offset[1][0] = 0.0f;
	offset[1][1] = 0.07f;
	offset[1][2] = 0.0f;

	offset[2][0] = 0.0f;
	offset[2][1] = -0.04f;
	offset[2][2] = 0.0f;

	offset[3][0] = -0.09f;
	offset[3][1] = 0.0f;
	offset[3][2] = -0.03f;

}

M249::M249()
{
	name = "M249";
	special = false;
	type = 4;
	id = 7;
	weapon_damage = 50;
	weapon_range = 150;
	weapon_cooldown = 85; //w milisekundach
	weapon_reload_time = 4200; //w milisekundach
	weapon_hideshow = 1800;
	max_ammo = 250;
	max_ammo_magazine = 90;
	current_ammo = 250;
	current_ammo_magazine = 90;
	recoil = 0.08;

	offset[0][0] = 0.0f;
	offset[0][1] = 0.18f;
	offset[0][2] = 0.0f;

	offset[1][0] = 0.0f;
	offset[1][1] = 0.07f;
	offset[1][2] = 0.0f;

	offset[2][0] = 0.0f;
	offset[2][1] = -0.04f;
	offset[2][2] = 0.0f;

	offset[3][0] = -0.09f;
	offset[3][1] = -0.01f;
	offset[3][2] = -0.045f;

}

DESERTDEAGLE::DESERTDEAGLE()
{
	name = "DESERTDEAGLE";
	special = false;
	type = 1;
	id = 8;
	weapon_damage = 50;
	weapon_range = 150;
	weapon_cooldown = 420; //w milisekundach
	weapon_reload_time = 2500; //w milisekundach
	weapon_hideshow = 450;
	max_ammo = 35;
	max_ammo_magazine = 10;
	current_ammo = 35;
	current_ammo_magazine = 10;
	recoil = 0.25;

	offset[0][0] = 0.0f;
	offset[0][1] = 0.18f;
	offset[0][2] = 0.0f;

	offset[1][0] = 0.0f;
	offset[1][1] = 0.07f;
	offset[1][2] = 0.0f;

	offset[2][0] = 0.0f;
	offset[2][1] = -0.04f;
	offset[2][2] = 0.0f;

	offset[3][0] = -0.09f;
	offset[3][1] = 0.0f;
	offset[3][2] = -0.03f;
}

BIZON::BIZON()
{
	name = "BIZON";
	special = false;
	type = 2;
	id = 9;
	weapon_damage = 42;
	weapon_range = 150;
	weapon_cooldown = 80; //w milisekundach
	weapon_reload_time = 2500; //w milisekundach
	weapon_hideshow = 1150;
	max_ammo = 130;
	max_ammo_magazine = 64;
	current_ammo = 130;
	current_ammo_magazine = 64;
	recoil = 0.13;

	offset[0][0] = 0.0f;
	offset[0][1] = 0.18f;
	offset[0][2] = 0.0f;

	offset[1][0] = 0.0f;
	offset[1][1] = 0.07f;
	offset[1][2] = 0.0f;

	offset[2][0] = 0.0f;
	offset[2][1] = -0.04f;
	offset[2][2] = 0.0f;

	offset[3][0] = -0.09f;
	offset[3][1] = 0.0f;
	offset[3][2] = -0.03f;

}

BLASTER::BLASTER()
{
	name = "BLASTER";
	special = true;
	special_ammo_take = 1.5;
	type = 3;
	id = 10;
	weapon_damage = 70;
	weapon_range = 150;
	weapon_cooldown = 180; //w milisekundach
	weapon_reload_time = 5500; //w milisekundach
	weapon_hideshow = 750;
	max_ammo = 0;
	max_ammo_magazine = 50;
	current_ammo = 0;
	current_ammo_magazine = 50;
	recoil = 0.1;

	offset[0][0] = 0.0f;
	offset[0][1] = 0.175f;
	offset[0][2] = 0.0f;

	offset[1][0] = 0.0f;
	offset[1][1] = 0.07f;
	offset[1][2] = 0.0f;

	offset[2][0] = 0.0f;
	offset[2][1] = -0.04f;
	offset[2][2] = 0.0f;

	offset[3][0] = -0.09f;
	offset[3][1] = 0.0f;
	offset[3][2] = -0.03f;
}


weapon::weapon()
{
	special = false;
	change_weapon_now = false;
	change_weapon = false;
	reloading = false;
	hiding = false;
	shooting = false;
	can_shoot = true;
	recoilX = 0;
	recoilY = 0;
	last_shoot = 0;
}

//Przebieg przeladowania broni
void weapon::Status()
{
	

	//Zamiana broni
	if (change_weapon == true) {
		can_shoot == false;
		int czas = abs(T-timestamp + weapon_hideshow);
		if (czas > weapon_hideshow)
		{
			czas = 0;
			change_weapon_now = true;
		}
		if (weapon_hideshow < 700)
		{
			glTranslatef(0, -czas*0.00012, czas*0.00003);
			glRotatef(czas*0.05, 0, 1, 0);
			glRotatef(czas*0.04, 0, 0, 1);

		}
		else
		{
			glTranslatef(0, -czas*0.000065, czas*0.00003);
			glRotatef(czas*0.04, 0, 1, 0);
			glRotatef(czas*0.03, 0, 0, 1);
		}





	}
	else {
		if (can_shoot == false)
		{
			reloading = true;
			shooting == false;
			if (T >= reload_end)
			{
				can_shoot = true;
			}
			else
			{
				int czas;

				//Pierwszy etap przeladowania
				if (T + 700 < reload_end)
				{

					if (T - timestamp > 700)
						czas = 700;
					else
						czas = T - timestamp;
					glTranslatef(0, -czas*0.00004, czas*0.00007);
					glRotatef(czas*0.1, 0, 1, 0);
					glRotatef(czas*0.03, 0, 0, 1);
				}
				//Drugi etap przeladowania
				else
				{
					czas = reload_end - T;
					glTranslatef(0, -czas*0.00004, czas*0.00007);
					glRotatef(czas*0.1, 0, 1, 0);
					glRotatef(czas*0.03, 0, 0, 1);
				}
			}
		}
		else
			reloading = false;
	}
}

void weapon::Shoot(weapon_sounds *weapon_sound, Bullet *pocisk, vec3 *player_pos, vec3 *player_dir, weapon *actual)
{
	if (can_shoot == true && change_weapon == false)
	{

		if (current_ammo_magazine > 0)
		{
			if (T > last_shoot + weapon_cooldown)
			{
				weapon_sound->shoot(id-1);
				shooting = true;
				pocisk->CreateBullet(player_pos, player_dir, actual->weapon_damage, actual->id, actual->weapon_range);
				recoilX = 0;
				recoilY = 0;
				last_shoot = T;
				current_ammo_magazine--;
				bool side = rand() % 2;
				if (side == false)
					recoilY = (rand() % 10000) / 2500 * recoil;
				else
					recoilY = -(rand() % 10000) / 2500 * recoil;
				recoilX = (rand() % 10000) / 1500 * recoil;

				//WYSZTRZEL POCISK
			}
		}
		else
			shooting = false;

	}
	else
		shooting = false;
}


void weapon::Reload(weapon_sounds *weapon_sound)
{
	if (can_shoot == true)
	{
		//Dla broni specjalnej
		if (special == true)
		{
			if (current_ammo_magazine < max_ammo_magazine)
			{
				weapon_sound->reload(1);
				shooting = false;
				int roznica = max_ammo_magazine - current_ammo_magazine;
				current_ammo_magazine = max_ammo_magazine;
				can_shoot = false;
				timestamp = T;
				reload_end = T + weapon_reload_time;
			}
		}
		else
		{

			if (current_ammo_magazine < max_ammo_magazine && current_ammo > 0)
			{
				weapon_sound->reload(0);
				shooting = false;
				int roznica = max_ammo_magazine - current_ammo_magazine;

				if (roznica > current_ammo)
				{
					current_ammo_magazine = current_ammo_magazine + current_ammo;
					current_ammo = 0;
				}
				else
				{
					current_ammo_magazine = max_ammo_magazine;
					current_ammo = current_ammo - roznica;
				}
				can_shoot = false;
				timestamp = T;
				reload_end = T + weapon_reload_time;

			}
		}
		//JEST W TRAKCIE PRZELADOWYWANIA
	}

}


int weapon::Get_id()
{
	return id;
}

int weapon::Get_ammo1()
{
	return current_ammo_magazine;
}

int weapon::Get_ammo2()
{
	return current_ammo;
}

void weapon::fill_ammo()
{
	current_ammo_magazine = max_ammo_magazine;
	current_ammo = max_ammo;


}

weapon_sounds::weapon_sounds()
{
	cout << "LADUJE DZWIEKI BRONI....\n";
	weapon_shoots[0] = Sound::loadWAVE("Data/Wav/MP5K.wav",true);
	weapon_shoots[1] = Sound::loadWAVE("Data/Wav/M4A4.wav", true);
	weapon_shoots[2] = Sound::loadWAVE("Data/Wav/AKS74U.wav", true);
	weapon_shoots[3] = Sound::loadWAVE("Data/Wav/SCARH.wav", true);
	weapon_shoots[4] = Sound::loadWAVE("Data/Wav/M9.wav", true);
	weapon_shoots[5] = Sound::loadWAVE("Data/Wav/AUG.wav", true);
	weapon_shoots[6] = Sound::loadWAVE("Data/Wav/M249.wav", true);
	weapon_shoots[7] = Sound::loadWAVE("Data/Wav/DESERTDEAGLE.wav", true);
	weapon_shoots[8] = Sound::loadWAVE("Data/Wav/BIZON.wav", true);
	weapon_shoots[9] = Sound::loadWAVE("Data/Wav/BLASTER.wav", true);

	reloading[0] = Sound::loadWAVE("DATA/Wav/RELOAD.wav", true);
	reloading[1] = Sound::loadWAVE("DATA/Wav/RELOAD_BLASTER.wav", true);
	cout << "\nDZWIEKI BRONI ZALADOWANE POMYSLNIE";

}

void weapon_sounds::shoot(int id)
{
	if(id<n)
	weapon_shoots[id]->play();
}

void weapon_sounds::reload(int id)
{
	reloading[id]->play();
}

