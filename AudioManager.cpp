#include "AudioManager.h"
#include "stdafx.h"


Sound::Sound(bool repeat, int format, int sampleRate, void * data, int size)
{

	alGenBuffers(1, &bufferID);
	alBufferData(bufferID, format, data, size, sampleRate);
	alGenSources(1, &sourceID);
	alSourcei(sourceID, AL_BUFFER, bufferID);

	this->repeat = repeat;
	this->format = format;
	this->sampleRate = sampleRate;
	this->data = data;
	this->size = size;

}


Sound* Sound::loadWAVE(const char * filename, bool repeat)
{
	FILE* fp = NULL;
	fp = fopen(filename, "r");

	if (!fp)
	{
		cout << "Nie mozna otworzyc pliku o nazwie " << filename << endl;
		fclose(fp);
		return NULL;
	}
	char* ChunkID = new char[5];
	
	fread(ChunkID, 4, sizeof(char), fp);
	ChunkID[4] = '\0';
	if (strcmp(ChunkID, "RIFF")) {
		delete[] ChunkID;
		cout << "Not RIFF\n " << filename << endl;
		fclose(fp);
		return NULL;
	}

	fseek(fp, 8, SEEK_SET);
	char* Format = new char[4];
	fread(Format, 4, sizeof(char), fp);
	Format[4] = '\0';

	if (strcmp(Format, "WAVE")) {
		delete[] Format;
		delete[] ChunkID;
		cout << "Not WAVE\n " << filename << endl;
		fclose(fp);
		return NULL;
	}


	char* SubChunk1ID = new char[4];
	fread(SubChunk1ID, 4, sizeof(char), fp);
	SubChunk1ID[4] = '\0';

	if (strcmp(SubChunk1ID, "fmt ")) {
		delete[] Format;
		delete[] ChunkID;
		delete[] SubChunk1ID;
		cout << "USZKODZONY PLIK !" << filename << endl;
		fclose(fp);
		return NULL;
	}
	
	unsigned int SubChunk1Size;
	fread(&SubChunk1Size, 1, sizeof(unsigned int), fp);

	unsigned int SubChunk2Location = (unsigned int) ftell(fp) + SubChunk1Size;

	unsigned short AudioFormat;
	fread(&AudioFormat, 1, sizeof(unsigned short), fp);

	if (AudioFormat != 1)
	{
		delete[] Format;
		delete[] ChunkID;
		delete[] SubChunk1ID;
		cout << "Audio nie jest formatu PCM!" << filename << endl;
		fclose(fp);
	}

	unsigned short NumChannels;
	fread(&NumChannels, 1, sizeof(unsigned short), fp);
	unsigned int SampleRate;
	fread(&SampleRate, 1, sizeof(unsigned short), fp);

	fseek(fp, 34, SEEK_SET);

	unsigned short BitsPerSample;
	fread(&BitsPerSample, 1, sizeof(unsigned short), fp);

	int ALFormat;

	if (NumChannels == 1 && BitsPerSample == 8){
		ALFormat = AL_FORMAT_MONO8;
	}
	else if (NumChannels == 1 && BitsPerSample == 16)
	{
		ALFormat = AL_FORMAT_MONO16;
	}
	else if (NumChannels == 2 && BitsPerSample == 8)
	{
		ALFormat = AL_FORMAT_STEREO8;
	}
	else if (NumChannels == 2 && BitsPerSample == 16)
	{
		ALFormat = AL_FORMAT_STEREO16;
	}
	else
	{
		
		delete[] ChunkID;
		delete[] Format;
		delete[] SubChunk1ID;
		cout << "Plik audio nie jest prawidolowo sformatowany\n";
		fclose(fp);
		return NULL;
		
	}

	fseek(fp, SubChunk2Location, SEEK_SET);
	char* SubChunk2ID = new char[4];
	SubChunk2ID[4] = '\0';
	fread(SubChunk2ID, 4, sizeof(char), fp);

	if (strcmp(SubChunk2ID, "data"))
	{
		delete[] ChunkID;
		delete[] Format;
		delete[] SubChunk1ID;
		delete[] SubChunk2ID;
		cout << "Uszkodzony plik\n";
		fclose(fp);
		return NULL;
	}
	

	unsigned int SubChunk2Size = 0;
	fread(&SubChunk2Size, 1, sizeof(unsigned int), fp);
	
	unsigned char* Data = new unsigned char[SubChunk2Size];
	fread(Data, SubChunk2Size-1000, sizeof(unsigned char), fp);
	//USUWANIE 'ARTEFAKTOW'
	for (int i = 0; i < 10000;i++)
	Data[SubChunk2Size-i] = '\0';
//	delete[] ChunkID;
//	delete[] Format;
//	delete[] SubChunk1ID;
//	delete[] SubChunk2ID;

	fclose(fp);
	return new Sound(repeat, ALFormat, SampleRate, Data, SubChunk2Size);
}

void Sound::play_footsteps()
{
	int state;
	alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
		alSourcePlay(sourceID);


}

void Sound::play()
{
	int state;
	alGetSourcei(sourceID, AL_SOURCE_STATE, &state);
	if (state != AL_PLAYING || repeat) {
		alSourcePlay(sourceID);
	}

}
