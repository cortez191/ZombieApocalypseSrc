#pragma once


class chest{
	GLuint chest_obj;
	GLuint chest_upper;
	GLuint chest_upper2;
	GLuint chest_upper3;
	CTexture *chest_texture;
	float coords[3];
	float rotate;
	bool opened;
	float Time;



	GLuint create_chest();
	GLuint create_chest_upper();
	GLuint create_chest_upper2();
	GLuint create_chest_upper3();
public:


	chest(float,float,float,float);
	void close();
	void open();
	void render();


};