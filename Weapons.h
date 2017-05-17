#pragma once
#include "Bullet.h"


class weapon_sounds {
	int n = 10;
	Sound* weapon_shoots[10];
	Sound* reloading[2];

public:

	weapon_sounds();
	void shoot(int id);
	void reload(int id);

	


};

//Zmienna type rodzaj broni
/*
1 - pistolet
2 - pistolet maszynowy
3 - karabin szturmowy
4 - karabin maszynowy
*/

class weapon {
public:
	string name;
	int type;
	int id;
	bool special;
	int special_ammo_take;

#pragma AMUNICJA
	float max_ammo;
	float max_ammo_magazine;
	float current_ammo;
	float current_ammo_magazine;
	bool can_shoot;
	bool shooting;
	bool hiding;
	bool reloading;

#pragma Procedura zamiany broni
	bool change_weapon;
	bool change_weapon_now;
	

#pragma endregion

#pragma endregion

#pragma region ZMIENNE PRZECHOWUJACE CZAS
	float last_shoot;
	float timestamp;
	float reload_end;
	float showhide_end;
#pragma endregion

#pragma region CECHY CHARAKTERYSTYCZNE BRONI
	float weapon_damage;
	float weapon_range;
	float weapon_cooldown;
	float weapon_hideshow;
	float weapon_reload_time;
	float recoil;
	float recoilX;
	float recoilY;
#pragma endregion

	//Zmiana polozenia broni - offset
	float offset[4][3];

		weapon();
		void Status();
		void Shoot(weapon_sounds *weapon_sound, Bullet *pocisk, vec3 *player_pos, vec3 *player_dir, weapon *actual);
		void Reload(weapon_sounds *weapon_sound);
		int Get_id();
		int Get_ammo1();
		int Get_ammo2();
		void fill_ammo();


};

#pragma region RODZAJE BRONI

class MP5K : public weapon {
public:
	MP5K();
};

class M4A4 : public weapon {
public:
	M4A4();
};

class AK74U : public weapon {
public:
	AK74U();
};

class SCARH : public weapon {
public:
	SCARH();
};

class M9 : public weapon {
public:
	M9();
};

class AUG : public weapon {
public:
	AUG();

};

class M249 : public weapon {
public:
	M249();

};

class DESERTDEAGLE : public weapon {
public:
	DESERTDEAGLE();

};

class BIZON : public weapon {
public:
	BIZON();

};

class BLASTER : public weapon {
public:
	BLASTER();

};


#pragma endregion


class load_models {
public:
	GLuint MP5K;
	CTexture *MP5K_texture;

	GLuint M4A4;
	CTexture *M4A4_texture;

	GLuint AKS74U;
	CTexture *AKS74U_texture;

	GLuint SCARH;
	CTexture *SCARH_texture;

	GLuint M9;
	CTexture *M9_texture;

	GLuint AUG;
	CTexture *AUG_texture;

	GLuint M249;
	CTexture *M249_texture;

	GLuint DesertDeagle;
	CTexture *DesertDeagle_texture;

	GLuint Bizon;
	CTexture *Bizon_texture;

	GLuint Blaster;
	CTexture *Blaster_texture;

	GLuint hands;
	CTexture *hands_texture;


	CMD2Model postac;

	
	load_models();
	void draw_weapons(int type);
	void show_weapons();
};