
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once



#include<Windows.h>
#include <Xinput.h>
#include "targetver.h"
#include<time.h>
#include <vector>
#include <cstdio>
#include<list>
#include<string>
#include<fstream>
#include<iostream>
#include <string>
#include <sstream>
#include <vector>
#include<stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <algorithm>
#include <GL/glew.h>
#include <GL/freeglut.h>



#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glew32s.lib")

//BIBLIOTEKI DZWIEKOWE
#include <al.h>
#include <alc.h>
#include <efx.h>
#include <efx-creative.h>
#include <EFX-Util.h>
#include <xram.h>


#include "AudioManager.h"



#include"StartGame.h"
//#include"load_md2.h"

using namespace std;

#include "Vec3.h"
#include "Texture.h"
#include "bmp.h"
#include "pcx.h"
#include "tga.h"


#include "CollisionDetection.h"
#include "Collision.h"
#include "CollisionEllipsoid.h"
#include "CollisionPlane.h"
#include "CollisionPolygon.h"
#include "BuyWeapon.h"
#include "Obj_loader_beta.h"
#include "map.h"
#include "timer.h"
#include "Coins.h"
#include "MD2_loader.h"
#include "MD2_texture.h"
#include "Weapons.h"
#include "Bullet.h"
#include "Player.h"
#include "Bitmap.h"
#include "SceneObject.h"
#include "Skydome.h"
#include "Terrain.h"
#include "Wall.h"
#include "Chest.h"
#include "Scene.h"
#include "Shader.h"

#include "Enemy.h"
#include "GameManager.h"
#pragma region Zmienne globalne



extern int mouseX;
extern int mouseY;

extern bool captureMouse;
extern bool free3DMovement;
extern float mouseSensitivity;

extern CScene * Scene;

extern bool keystate[255];

extern float T;


#pragma endregion