#pragma once


class Sound {


public:
	unsigned int bufferID;
	unsigned int sourceID;

	bool repeat;
	void* data;
	int size;

	int format;
	int sampleRate;

	Sound(bool repeat, int format, int sampleRate, void* data, int size);
	 static Sound* loadWAVE(const char *filename, bool repeat);
	 void play_footsteps();
	 void play();


};