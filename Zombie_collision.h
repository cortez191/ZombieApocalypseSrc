#pragma once


class ZombieAABB_Collision{

	int collision_space;

public:

	void BulletCollision(vec3 bullet_pos,Enemy *zombie);

};