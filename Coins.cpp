#include"Coins.h"
#include "stdafx.h"

Coins::Coins()
{
	freeze_duration;
	duration_time = 10000;
	timestamp = 0;
	draw = false;
	can_create = true;
	type = 0;
	coin_pos = { 0,0,0 };
	Coin[0] = new CTexture("Data/Models/Coins/coin_ammo.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Coin[1] = new CTexture("Data/Models/Coins/coin_money.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Coin[2] = new CTexture("Data/Models/Coins/coin_skeleton.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Coin[3] = new CTexture("Data/Models/Coins/coin_vader.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	coin_obj = LoadObj("Data/Models/Coins/coin.obj");
	picking_coin = Sound::loadWAVE("Data/Wav/Coin.wav", false);
}

void Coins::set_coin(vec3 position)
{

	if (can_create == true) {
		coin_pos = position;
		int losuj = rand() % 100;
		
		if (losuj < 60)
			type = 1;
		else
		if (losuj < 70)
			type = 2;
		else
			type = 3;

		can_create = false;
		draw = true;
		timestamp = T + duration_time;

	}
}

void Coins::max_ammo(CPlayer *player)
{
	type = 0;
	can_create = true;
	if (player->first_slot != NULL)
		player->first_slot->fill_ammo();
	if (player->second_slot != NULL)
		player->second_slot->fill_ammo();

}

void Coins::money(CPlayer *player)
{
	player->AddMoney(2000);
	type = 0;
	can_create = true;
}

void Coins::instant_kill()
{
	type = 0;
	can_create = true;
}

void Coins::air_strike()
{
	type = 0;
	can_create = true;
}

void Coins::update(CPlayer *player)
{




	//Jezeli nie ma zadnych elektow coinow
	if (draw == true) {

		//sprawdza kolizje z graczem
		if (abs(player->pos.x - coin_pos.x) < 0.5 && abs(player->pos.y - coin_pos.y) < 0.5 && abs(player->pos.z - coin_pos.z) < 0.5)
		{
			picking_coin->play();
			draw = false;
		}

		//Usuwa zbyt dlugo znajdujacy sie coin
		if (timestamp < T)
		{
			type = 0;
			draw = false;
			can_create = true;
			coin_pos = { 0,0,0 };

		}



	}
	//Zarzadza coinami
	else
	{
		switch (type) {
		case 0: break;
		case 1: max_ammo(player); break;
		case 2: money(player); break;
		case 3: instant_kill(); break;
		case 4: air_strike(); break;
		}
	}
}

void Coins::render()
{
	if (draw == true) {
		glEnable(GL_TEXTURE_2D);
		glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();
		glTranslatef(coin_pos.x, coin_pos.y + 0.4 + sin(T*0.001)*0.1, coin_pos.z);
		glScalef(6, 6, 6);
		glRotatef(T*0.1, 0, 1, 0);
		switch (type) {
		case 1:	glBindTexture(GL_TEXTURE_2D, Coin[0]->GetId()); break;
		case 2: glBindTexture(GL_TEXTURE_2D, Coin[1]->GetId()); break;
		case 3: glBindTexture(GL_TEXTURE_2D, Coin[2]->GetId()); break;
		case 4:glBindTexture(GL_TEXTURE_2D, Coin[3]->GetId()); break;
		}
		glCallList(coin_obj);



		glPopMatrix();
		glPopAttrib();
	}
}
