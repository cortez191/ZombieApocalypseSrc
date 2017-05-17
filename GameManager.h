#pragma once

class GameManager {
	CMD2Model Zombie;
	Sound *countdown;
	Sound *round_win;


	int zombies_left;
	int max_zombies;
	int fala;
	int actual_zombies;
	bool play;

public:
	int next_wave;
	bool win_played;
	Enemy *undead[50];
	int zombie_count();
	int wave();
	void killed_zombie();
	void load_wav();
	void load_zombies();
	GameManager();
	void new_wave(int);
	void Update();
	void Render();
};