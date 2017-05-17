#pragma once
#include "Player.h"

class Enemy : public CPlayer {
	CMD2Model postac;
public:
	int animation;
	int damage;

	float speed;

	//Zmienne czasowe
	float damage_time;
	
	int health;
	bool slained;
	vec3 nextZombiePos;

	Enemy(CMD2Model &wzor, bool);
	void remove_health(int);
	void spawn_zombie(vec3, int, int, float);
	void zombie_collision(Enemy *second);
	void Render(vec3 player_pos);
	void LookDir(vec3 player_pos);
	void MoveToPlayer(vec3 player_pos, CPlayer *player);
};


