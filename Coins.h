#pragma once
class CPlayer;

/* typ monety
0 - nic nie ma
1 - maksymalna amunicja
2 - daje graczowi 2000$
3 - instant kill
4 - wsparcie powietrzne (nieobecne w tej wersji, gdyz brakowalo mi modeli itp)

*/

class Coins {
	CTexture *Coin[4];
	GLuint coin_obj;
	Sound *picking_coin;
	int freeze_duration;
	//Typ monety
	int type;
	//Czy coin moze zostac utworzony
	bool can_create;
	//Pozycja coina, o ile istnieje
	vec3 coin_pos;
	bool draw;


	//czas trwania
	int duration_time;
	int timestamp;


public:
	Coins();
	void set_coin(vec3 position);
	void max_ammo(CPlayer *player);
	void money(CPlayer *player);
	void instant_kill();
	void air_strike();
	void update(CPlayer *player);
	void render();

};