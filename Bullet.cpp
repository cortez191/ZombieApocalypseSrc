#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

#include"stdafx.h"


Bullet::Bullet()
{
	pocisk = LoadObj("Data/Models/Weapons/BULLET/bullet1.obj");
	pocisk2 = LoadObj("Data/Models/Weapons/BULLET/bullet2.obj");
	bulletspeed = 10;
	wsk = (typebullet *)init(wsk);
}

int Bullet::init(typebullet * wsk)
{
	wsk = new typebullet;
	wsk->next = NULL;
	wsk->prev = NULL;
	wsk->damage = NULL;
	wsk->distance = NULL;
	wsk->max_distance = NULL;
	wsk->position = { 0,0,0 };
	wsk->direction = { 0,0,0 };
	return(int)wsk;
}

int Bullet::CreateBullet(vec3 *position, vec3 *direction, int damage, int id, int max_distance)
{
	if (damage != NULL) {
		if (wsk == NULL)
		{
			wsk = (typebullet *)init((Bullet::typebullet *)wsk);
		}

		int error = 0;
		struct typebullet *tmp = wsk;
		struct typebullet *new_shape = new typebullet;
		struct typebullet *new_address = wsk;
		struct typebullet *handler;

		new_shape->damage = damage;
		new_shape->distance = 0;
		new_shape->max_distance = max_distance;
		new_shape->position.x = position->x;
		new_shape->position.y = position->y+0.25;
		new_shape->position.z = position->z;
		new_shape->direction.x = direction->x;
		new_shape->direction.y = direction->y;
		new_shape->direction.z = direction->z;
		new_shape->id = id;

		if (error == 0)
		{
			//Jezeli przedtem nie było żadnej figury
			if (tmp->damage == NULL)
			{
				new_address = new_shape;
				delete wsk;
				new_shape->next = NULL;
				new_shape->prev = NULL;
			}
			//Jezeli istnieją już figury
			else
			{
				while (tmp->next != NULL)
				{
					tmp = tmp->next;
				}
				tmp->next = new_shape;
				handler = tmp;
				new_shape->prev = handler;
				new_shape->next = NULL;
			}
		}
		else
			//Jezeli blad w tworzeniu pocisku
		{
			cout << "BLAD W TWORZENIU POCISKU";

			delete new_shape;
		}
		wsk = new_address;
		return (int)new_address;
	}
	return 0;
}

int Bullet::removeBullet(typebullet * wsk,int nr)
{
	int id = nr;
	struct typebullet *main = wsk;

	//Jezeli lista nie jest pusta
	if (wsk != NULL) {
		bool error = false;

		if (id >= 1)
		{
			for (int i = 1; i < id; i++)
			{

				if (wsk->next == NULL && i != id - 1)
				{
					error = true;
					break;
				}
				wsk = wsk->next;
			}
			if (error == false)
			{
				struct typebullet *handler;
				struct typebullet *handler2;
				//Jezeli byl to pierwszy element listy
				if (id == 1) {

					//Jezeli ma nastepnika
					if (wsk->next != NULL)
					{
						main = wsk->next;
						handler = wsk;
						wsk = wsk->next;
						delete handler;
						handler = NULL;
						wsk->prev = NULL;
					}
					//Jest wtedy jedynym rekordem
					else
					{
						delete wsk;
						wsk = NULL;
						main = NULL;
					}


				}
				else
				{
					//Jezeli jest wartoscia pomiedzy
					if (wsk->next != NULL && wsk->prev != NULL) {
						handler = wsk->next;
						handler2 = wsk->prev;
						handler->prev = handler2;
						handler2->next = handler;
						delete wsk;
						wsk = NULL;

					}
					//Jezeli jest ostatnia wartoscia
					else {
						handler = wsk->prev;
						handler->next = NULL;
						delete wsk;
						wsk = NULL;
					}

				}





			}
		//	else
		//	{
		//		cout << "Wprowadzone ID nie istnieje, nie ma tylu elementow...\n";
		//	}
		}
	//	else
	//		cout << "Wprowadzone ID jest niepoprawne...\n";
	}
//	else
//		cout << "Lista jest pusta";
	return (int)main;
}

void Bullet::render()
{
	glDisable(GL_CULL_FACE);
	int i = 0;
	struct typebullet *tmp = wsk;
	while (tmp != NULL && tmp->damage != NULL) {
		if (tmp->distance > 2) {
			glPushMatrix();
			glTranslatef(tmp->position.x, tmp->position.y, tmp->position.z);
			glRotatef(atan2(tmp->direction.x, tmp->direction.z) * 180 / 3.1415 + 90, 0, 1, 0);
			glRotatef(acos(tmp->direction.y) * 180 / 3.1415 - 90, 0, 0, 1);
			if (tmp->id == 10)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glDisable(GL_TEXTURE_2D);
				glPushAttrib(GL_CURRENT_BIT);
				
				glColor4f(1, 1, 0, 1);
				glCallList(pocisk2);
				glPopAttrib();
			}
			else
				glCallList(pocisk);
			glPopMatrix();
		}
		tmp = tmp->next;
		i++;
	}
	glEnable(GL_CULL_FACE);
}

int Bullet::update()
{
	int i = 1;
	struct typebullet *tmp = wsk;
	struct typebullet *actual = NULL;
	
	while (tmp != NULL && tmp->damage != 0) {
		tmp->old_position = tmp->position;
		tmp->old_direction = tmp->direction;

		tmp->position.x +=tmp->direction.x * 0.2;
		tmp->position.y += tmp->direction.y * 0.2;
		tmp->position.z += tmp->direction.z * 0.2;
		tmp->distance += 1;
		if(tmp->id != 10)
		tmp->direction.y -= 0.0002;
		actual = tmp;
		tmp = tmp->next;

		//Jezeli pocisk osiagnie limit odleglosci to jest usuwany lub wpadnie pod mape

		i++;
	}

	i = 1;
	tmp = wsk;
	//Usuwanie przedawnonych pociskow
	while (tmp != NULL && tmp->damage != 0) {

		actual = tmp;
		tmp = tmp->next;
		//Jezeli pocisk osiagnie limit odleglosci to jest usuwany lub wpadnie pod mape
		if ((actual->distance >= actual->max_distance && actual != NULL))
		{
			wsk = (Bullet::typebullet*) removeBullet(wsk, i);
		}
		i++;
	}


	return 0;
}

void Bullet::check_collision(Enemy *undead, CPlayer *cplayer, Coins *coin, GameManager *game_manager)
{

	struct typebullet *tmp = wsk;
	struct typebullet *nastepnik = NULL;
	int i = 1;
	vec3 tmp_vector;
	int losuj;
	vec3 tmp_position;
	//Aktualizajca stanow dla pociskow
	while (tmp != NULL && tmp->damage != 0) {
		tmp_vector = tmp->old_position;
		tmp_position = undead->pos;
		losuj = rand() % 100;
		nastepnik = tmp->next;
		if (abs(tmp_vector.x - undead->pos.x) < 1.5 && abs(tmp_vector.y - undead->pos.y) < 1.5 && (abs(tmp_vector.z - undead->pos.z) < 1.5))
		{
			for (int j = 0; j < 5; j++)
			{
				tmp_vector = tmp_vector + tmp->old_direction* 0.04;


				//Trafienie w tolow
				if (abs(tmp_vector.x - undead->pos.x) < 0.15 && abs(tmp_vector.y - undead->pos.y - 0.42) < 0.12 && abs(tmp_vector.z - undead->pos.z) < 0.15)
				{
					undead->remove_health(tmp->damage);
					wsk = (Bullet::typebullet*) removeBullet(wsk, i);
					if (undead->slained == true)
					{
						cplayer->AddMoney(15);
						if(losuj < 7)
						coin->set_coin(tmp_position);
						game_manager->killed_zombie();
					
					}


					break;
				}
				//Trafienie w nogi
				if (abs(tmp_vector.x - undead->pos.x) < 0.15 && abs(tmp_vector.y - undead->pos.y - 0.15) < 0.15 && abs(tmp_vector.z - undead->pos.z) < 0.15)
				{
					undead->remove_health(tmp->damage * 0.75);
					wsk = (Bullet::typebullet*) removeBullet(wsk, i);
					if (undead->slained == true)
					{
						cplayer->AddMoney(10);
						if (losuj < 5)
						coin->set_coin(tmp_position);
						game_manager->killed_zombie();
					}
						
					break;
				}

				//Trafienie w glowe
				if (abs(tmp_vector.x - undead->pos.x) < 0.07 && abs(tmp_vector.y - undead->pos.y - 0.64) < 0.1 && abs(tmp_vector.z - undead->pos.z) < 0.07)
				{

					undead->remove_health(tmp->damage * 2.3);
					wsk = (Bullet::typebullet*) removeBullet(wsk, i);
					if (undead->slained == true)
					{
						cplayer->AddMoney(25);
						if (losuj < 9)
						coin->set_coin(tmp_position);
						game_manager->killed_zombie();
					}
					break;
				}
			}
		}
		tmp = nastepnik;
		i++;
	}

}
