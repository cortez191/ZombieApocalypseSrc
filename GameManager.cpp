#include "GameManager.h"
#include "stdafx.h"

int GameManager::zombie_count()
{
	return zombies_left;
}

int GameManager::wave()
{
	return fala;
}

void GameManager::killed_zombie()
{
	zombies_left--;
}

void GameManager::load_wav()
{
	countdown = Sound::loadWAVE("Data/Wav/countdown.wav", false);
	round_win = Sound::loadWAVE("Data/Wav/victory.wav", false);
}

void GameManager::load_zombies()
{

	Zombie.LoadModel("Data/Models/Characters/Zombie/Zombie.md2");
	Zombie.LoadSkin("Data/Models/Characters/Zombie/Zombie_texture.bmp");

	Zombie.ScaleModel(0.18);
	cout << "\nWCZYTANO Zombie.md2\n";
	for (int i = 0; i < 50; i++)
	{
		undead[i] = new Enemy(Zombie, true);
	}

}

GameManager::GameManager()
{
	win_played = false;
	fala = 10;
	load_wav();
	new_wave(10);
	play = false;
	load_zombies();
	


	
}

void GameManager::new_wave(int level)
{
	if (play == true)
	{
		zombies_left = level * 18 + 8;
		if (zombies_left > 450)
			zombies_left = 450;
		max_zombies = level * 4.2 + 9;
		if (max_zombies > 50)
			max_zombies = 50;
	}

}

void GameManager::Update()
{
	if (play == true) {
		if (zombies_left > 0)
		{

			actual_zombies = 0;
			for (int i = 0; i < 50; i++)
			{
				if (undead[i]->slained == false) actual_zombies++;
			}

			int remain = zombies_left - actual_zombies;

			int i = 0;
			while (remain > 0 && i < 50) {

				if (undead[i]->slained == true)
				{
					int random_x = (rand() % 12) - 7;
					int random_z = (rand() % 23) - 10;
					vec3 pozycja;
					pozycja.x = random_x;
					pozycja.y = 0;
					pozycja.z = random_z;

					int max_health = log2(fala) * 100 + 25;
					if (max_health > 250)
						max_health = 250;

					int damage = fala * 2.2 + 15;
					if (damage > 45)
						damage = 45;

					float speed = fala *  0.006 + 0.015;
					if (speed > 0.032)
						speed = 0.032;


					undead[i]->spawn_zombie(pozycja, damage, max_health, speed);
					remain--;

				}
				i++;
			}
		}

		if (win_played == true)
		{
			if (next_wave < T)
			{
				new_wave(fala);
				win_played = false;
				next_wave = 0;
			}
		}


		if (zombies_left == 0 && win_played == false)
		{
			round_win->play();
			fala++;
			next_wave += T + 15000;
			win_played = true;

		}
	}
}

void GameManager::Render()
{
}
