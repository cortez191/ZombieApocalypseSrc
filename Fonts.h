#pragma once


class Fonts {
private:
	int w, h;
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;

public:
	Fonts();
	void Draw_Text_Bottom(const char* string);
	void printtext(int x, int y, string String);
	void WeaponName(string String);


};