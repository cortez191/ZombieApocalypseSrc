#include "stdafx.h"
#include "Enemy.h"

#define PI 3.14159265 

Enemy::Enemy(CMD2Model &wzor, bool enabled) {
	postac = wzor;
	damage_time = 0;
	damage = 20;
	pos = { 100,-100,100 };
	slained = enabled;
	collisionEllipsoid = new CCollisionEllipsoid(.15f, .3f, .15f);
	animation = 0;
	postac.SetAnim(0);
	speed = 0.02;
	health = 100;
}

void Enemy::remove_health(int damage)
{
	health -= damage;
	if (health <= 0)
	{ 
		slained = true;
		pos.x = 100;
		pos.y = -10;
		pos.z = 100;
		postac.SetAnim(0);
		damage_time = 0;
		animation = 0;
	
	}

}

void Enemy::spawn_zombie(vec3 pos, int damage, int health, float speed)
{
	nextZombiePos = pos;
	damage_time = 0;
	this->pos = pos;
	this->damage = damage;
	this->health = health;
	this->speed = speed;
	slained = false;
	postac.SetAnim(0);








}

void Enemy::zombie_collision(Enemy * second)
{
	if (abs(nextZombiePos.x - second->nextZombiePos.x) < 0.2 && abs(nextZombiePos.z - second->nextZombiePos.z) < 0.2) {

		if ((nextZombiePos.x - second->nextZombiePos.x) < 0.2) {
			if (nextZombiePos.x < second->nextZombiePos.x) {

				nextZombiePos.x -= 0.005;
			}
			else
			{
				nextZombiePos.x += 0.005;
			}

		}

		if ((nextZombiePos.z - second->nextZombiePos.z) < 0.2) {
			if (nextZombiePos.z < second->nextZombiePos.z) {

				nextZombiePos.z -= 0.005;
			}
			else
			{
				nextZombiePos.z += 0.005;
			}

		}



	}
}

void Enemy::LookDir(vec3 player_pos) {

	float odl_x = pos.x - player_pos.x;
	float odl_z = pos.z - player_pos.z;
	float przekatna = sqrt(abs(odl_x)*abs(odl_x) + abs(odl_z)*abs(odl_z));

	if (przekatna < 0.5)
	{
		if (animation != 1)
		{
			animation = 1;
			postac.SetAnim(1);
		}
	}
	else
	{
		if (przekatna >= 0.5 && przekatna < 3) {
			if (animation != 0)
			{
				animation = 0;
				postac.SetAnim(0);
			}
		}
	}



	float kat = atan2(odl_x, odl_z) * 180 / PI + 180;
	glRotatef(kat, 0, 1, 0);

}

void Enemy::MoveToPlayer(vec3 player_pos, CPlayer *player) {
	
	
	if (slained == false) {
		int multiplier = 1;
		float odl_x = abs(pos.x - player_pos.x);
		float odl_z = abs(pos.z - player_pos.z);
		float przekatna = atan(odl_z / odl_x) * 180 / PI;

		nextZombiePos = pos;

		//Jezeli jest animacja atakowania
		if (animation == 1)
		{
			damage_time += 0.017;

			if (damage_time > 1.2)
			{
				damage_time = 0;
				player->PlayerRemoveHealth(damage);
				player->update_time = 0;
			}
		}
		else
			damage_time = 0;

		if (odl_x > 4 || odl_z > 4)	multiplier = 1.5;

			if (odl_x > 0.3)
			{
				if (nextZombiePos.x < player_pos.x)
					nextZombiePos.x += speed*(cos(przekatna*PI / 180)) * multiplier;
				else
					nextZombiePos.x -= speed*(cos(przekatna*PI / 180)) * multiplier;
			}

			if (odl_z > 0.3)
			{
				if (nextZombiePos.z < player_pos.z)
					nextZombiePos.z += speed*(sin(przekatna*PI / 180)) * multiplier;
				else
					nextZombiePos.z -= speed*(sin(przekatna*PI / 180)) * multiplier;
			}

			nextZombiePos.y -= .1f;
			nextZombiePos.y = __max(0.0f, nextZombiePos.y);
		}
}

void Enemy::Render(vec3 player_pos)
{

	if (slained == false)
	{
		glPushMatrix();
			glTranslatef(pos.x, pos.y, pos.z);
			LookDir(player_pos);
			postac.DrawModel(T*2.5*speed);
		glPopMatrix();
	}

}