#pragma once

class GameManager;

// Stan gracza.
class CPlayer {

public:

#pragma region parametry gracza
	float distance;
	float health;
	int money;
	int update_time;
	bool player_dead;
#pragma endregion

#pragma region ekwipunek gracza
	weapon *first_slot;
	weapon *second_slot;
	weapon *actual_weapon;
#pragma endregion

#pragma region HUD
	GLuint HUD_elements[2];
	GLuint HUD_Slash;
	GLuint HUD_Weapon_Name[10];
	GLuint HUD_Numbers[12];
	GLuint GUI_elements[3];
	GLuint Kup_Bron[2];
	GLuint Press;
	GLuint Fala;
	GLuint GameOver;
	GLuint others[1];
	CTexture *HUD_Weapons[10];
	CTexture *Empty;
	CTexture *Health_bar;
	CTexture *Zombie_left;
	CTexture *font_texture;
#pragma endregion

#pragma region Gracz na mapie
	vec3 pos;
	vec3 dir;
	vec3 cam; // Przesuniêcie punktu zaczepienia kamery wzglêdem pozycji gracza.
	float speed;
	
	float velRX, velRY, velM, velS;
	CCollisionEllipsoid * collisionEllipsoid; // Elipsoida s³u¿¹ca do wykrywania kolizji.
#pragma endregion


	void PlayerUpdate();
	void LoadBMPHUD();
	void HUD(int id, int first_weapon, int second_weapon, int magazine_ammo, int max_ammo, GameManager *game_manager, BuyWeapon *buy_weapon);
	void WeaponPos();
	void PlayerRemoveHealth(int);
	void AddMoney(int);
	void DrawTextHUD(char *);


#pragma region Stany myszy
	bool left_mouse_button;
	bool right_mouse_button;
#pragma endregion


	CPlayer() {

		player_dead = false;
		update_time = 0;
		left_mouse_button = false;
		right_mouse_button = false;
		money = 10000;
		first_slot = NULL;
		actual_weapon = first_slot;
		second_slot = NULL;
		health = 100;
		distance = 0;
		pos.Set(0.0f, 0.0f, 0.0f);
		dir.Set(0.0f, 0.0f, -1.0f);
		cam.Set(0.0f, 0.25f, 0.0f);
		speed = 0.0f;
		velRX = 0.0f;
		velRY = 0.0f;
		velM = 0.0f;
		velS = 0.0f;
		collisionEllipsoid = new CCollisionEllipsoid(.25f, .3f, .25f);
	}

	~CPlayer() {
		if (first_slot != NULL)
			delete first_slot;
		if (second_slot != NULL)
			delete second_slot;
		actual_weapon = NULL;

	}


};
