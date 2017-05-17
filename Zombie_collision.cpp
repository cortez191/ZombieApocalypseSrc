#include "Zombie_collision.h"
#include "stdafx.h"

void ZombieAABB_Collision::BulletCollision(vec3 bullet_pos, Enemy *zombie)
{

	if (abs(bullet_pos.x - zombie->pos.x) < 0.4 && abs(bullet_pos.z - zombie->pos.z) < 0.4 && abs(bullet_pos.y - zombie->pos.y) < 1) {

		cout << "ZOMBIE DOSTAL xD" << endl;

	}


}

