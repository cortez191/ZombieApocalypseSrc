#pragma once
class Enemy;
class GameManager;

class Bullet {

	struct typebullet {
		int id;
		int damage;
		float distance;
		int max_distance;
		vec3 position;
		vec3 direction;
		vec3 old_position;
		vec3 old_direction;


		struct typebullet *prev;
		struct typebullet *next;

	};
	GLuint pocisk;
	GLuint pocisk2;
	struct typebullet *wsk = 0;
	int bulletspeed;

public:
	Bullet();
	int init(struct typebullet *wsk);
	int CreateBullet(vec3 *position, vec3 *direction, int damage, int id, int max_distance);
	int removeBullet(struct typebullet *wsk, int nr);
	void render();
	int update();
	void check_collision(Enemy *undead, CPlayer *player, Coins *coin, GameManager *game_manager);


};