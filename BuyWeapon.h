#pragma once
class load_models;


class BuyWeapon {

	load_models *models;
	struct weapon_stat {
		string name;
		vec3 position;
		int cost;
		int ammo_cost;
	};
	bool pressed;
	

	


public:
	weapon_stat bronie[10];
	int collision;
	BuyWeapon(load_models *models);

	void Render();
	void Update(CPlayer *gracz);




};