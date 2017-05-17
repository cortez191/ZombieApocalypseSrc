#include "stdafx.h"
#include "StartGame.h"
#include<fstream>

struct SCameraState {
	vec3 pos;
	vec3 dir;
	float speed;
	float velM, velS; // zmienne pomocnicze do efektu bezwladnosci kamery - aktualna predkosc
};
float tr;
SCameraState player;

vec3 LightPos; // pozycja zrodla swiatla

float T;

#pragma region Zmienne globalne

int mouseX = 0;
int mouseY = 0;

bool captureMouse = true;
bool free3DMovement = false;

float mouseSensitivity = .15f;
CScene *Scene;

bool keystate[255];

#pragma endregion

bool keystate_special[256];
GLuint id;
int s;

Model_MD2 Gracz;
Model_MD2 Zombie;
Model_MD2 Gracz_hands;

Enemy *enemies[40];
Enemy *zombie[10];


//Enemy *przeciwnik[20];


int start(int argc, char * argv[])
{
	
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1366, 768);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("GKiW: Lab 5");
	//glutFullScreen();
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutTimerFunc(17, OnTimer, 0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(mouseX, mouseY);
	glutSetCursor(GLUT_CURSOR_NONE);
	Scene = new CScene();
	Scene->Initialize();


	Gracz.Load("Data\\Textures\\Characters\\Player\\player.md2", "Data\\Textures\\Characters\\Player\\player.pcx");
	Gracz_hands.Load("Data\\Textures\\Characters\\Player\\hands.md2", "Data\\Textures\\Characters\\Player\\player.pcx");
	Zombie.Load("Data\\Textures\\Characters\\Zombie\\zombie.md2", "Data\\Textures\\Characters\\Zombie\\zombie_texture.pcx");


	for (int i = 0; i < 40; i++)
	{
		enemies[i] = new Enemy(Gracz, i, 0, i);
	}

	for (int i = 0; i < 10; i++)
	{
		zombie[i] = new Enemy(Zombie, 2 * i, 0, 2 * i);
	}
//	Gracz.Play(0,5);

	player.pos.x = 0.0f;
	player.pos.y = 2.0f;
	player.pos.z = 8.0f;

	player.dir.x = 0.0f;
	player.dir.y = 0.0f;
	player.dir.z = -1.0f;

	player.speed = 1.50f;

	id = glGenLists(249);

	glPushMatrix();
	glPopMatrix();

	glutMainLoop();

	return 0;
}
void OnReshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float)width / height, .01f, 100.0f);

}
float g_rotation = 0;
void OnRender(void)
{


	
	T = glutGet(GLUT_ELAPSED_TIME);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_pos[] = { 1.0f, 5.0f, 4.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);

	Scene->Render();

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_CULL_FACE);
	
	// W³¹czamy teksturowanie
	glEnable(GL_TEXTURE_2D);

	// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

//	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);

	glPushMatrix();
	glTranslatef(2,0, 2);
	glScalef(0.009, 0.009, 0.009);

	//	glScalef(collisionEllipsoid->r.x, collisionEllipsoid->r.y, collisionEllipsoid->r.z);
	
	glRotatef(270, 1, 0, 0);
	glRotatef(6, 0, 1, 0);
	glRotatef(180, 0, 0, 1);
	//Gracz.Draw();
	//glutWireSphere(1.0f, 64, 64);
	//Gracz.Play(0, 1);
	glPopMatrix();

	for (int i = 0; i < 10; i++)
	{
		zombie[i]->Render();
	}



	/*for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			glPushMatrix();
			glTranslatef(9+i*0.5, 0.25, j*0.5);
			//glTranslatef(player.pos.x, player.pos.y, player.pos.z);
			glScalef(0.009, 0.009, 0.009);
			tr =(int) (-0.05*T) % 1500;
			glTranslatef(tr, 0, 0);
			glRotatef(270, 1, 0, 0);
			glRotatef(6, 0, 1, 0);
			glRotatef(180, 0, 0, 1);
			//glRotatef(1, player.dir.x, player.dir.y, player.dir.z);

			Gracz.Draw();
			Gracz.Play(i, N);
			glPopMatrix();
		}
	}*/
	



	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);



	// Ustawienie materia³u
	float m_amb[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

	// K¹t obrotu quadów
	float rot = T / 50.0f;
	//float rot = 0.0f;


#pragma endregion

	Gracz_hands.Draw();



	// Wy³¹czenie teksturowania - geometria renderowana od tego miejsca nie bêdzie ju¿ oteksturowana
	glDisable(GL_TEXTURE_2D);

#pragma endregion

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
	
}

void OnTimer(int id)
{

	glutTimerFunc(17, OnTimer, 0);

	T = glutGet(GLUT_ELAPSED_TIME); // Ile milisekund uplynelo od momentu uruchomienia programu?
	Scene->Update();
/*#pragma region Ruch kamery

									// Zmiana predkosci gracza jesli wcisniete W/S/A/D
	if (keystate['w']) {
		player.velM = player.speed;
	}
	if (keystate['s']) {
		player.velM = -player.speed;
	}
	if (keystate['a']) {
		player.velS = -player.speed;
	}
	if (keystate['d']) {
		player.velS = player.speed;
	}

	// Obrot kamery
	float phi = atan2(player.dir.z, player.dir.x);
	if (keystate['q']) {
		phi -= .03f;
	}
	if (keystate['e']) {
		phi += .03f;
	}

	player.dir.x = cos(phi);
	player.dir.z = sin(phi);

	// Znalezienie kierunku prostopadlego
	vec3 per;
	per.x = -player.dir.z;
	per.z = player.dir.x;

	// Chodzenie przod/tyl
	player.pos.x += player.dir.x * player.velM * .1f;
	player.pos.y += player.dir.y * player.velM * .1f;
	player.pos.z += player.dir.z * player.velM * .1f;

	// Chodzenie na boki
	player.pos.x += per.x * player.velS * .1f;
	player.pos.z += per.z * player.velS * .1f;

	// Bezwladnosc - w kazdym cyklu maleje predkosc gracza
	player.velM /= 1.2;
	player.velS /= 1.2;

#pragma endregion

#pragma region Ruch swiatla

	if (keystate_special[GLUT_KEY_LEFT]) {
		LightPos.x -= .05f;
	}
	if (keystate_special[GLUT_KEY_RIGHT]) {
		LightPos.x += .05f;
	}
	if (keystate_special[GLUT_KEY_UP]) {
		LightPos.y += .05f;
	}
	if (keystate_special[GLUT_KEY_DOWN]) {
		LightPos.y -= .05f;
	}

#pragma endregion*/


}

#pragma region Obsluga wejscia

void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		keystate[key] = true;
		OnKeyDown(key, x, y);
	}
}

void OnKeyDown(unsigned char key, int x, int y) {
	if (key == 27) {
		glutLeaveMainLoop();
	}
	if (key == 'm' || key == 'M') {
		if (captureMouse) {
			captureMouse = false;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
		else {
			captureMouse = true;
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
	}
	if (key == 'l' || key == 'L') {
		free3DMovement = !free3DMovement;
	}
	if (key == 'k' || key == 'K') {
		// Rysowanie kolizji.
		Scene->DrawCollisions = !Scene->DrawCollisions;
	}
	if (key == 'n' || key == 'N') {
		// Rysowanie wektorów normalnych.
		Scene->DrawNormals = !Scene->DrawNormals;
	}
}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}

void OnMouseMove(int x, int y) {
	mouseX = x;
	mouseY = y;
}

#pragma endregion