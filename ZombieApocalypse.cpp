#include "stdafx.h"
#include "StartGame.h"
#include<fstream>


vec3 LightPos; // pozycja zrodla swiatla


#pragma region Zmienne globalne

int mouseX = 0;
int mouseY = 0;
float T = 0;

bool captureMouse = true;
bool free3DMovement = false;
float mouseSensitivity = .15f;
CScene *Scene;

bool keystate[255];
#pragma endregion

#pragma region Opcje graficzne
bool bTextured = true;
bool bLighGL = false;
bool bAnimated = true;
float angle = 0.0;
extern float g_angle;
#pragma endregion

#pragma region Obsluga dzwieku

ALCdevice* alDevice;
ALCcontext* alContext;
#pragma endregion



void mouseButton(int button, int state, int x, int y);

int main(int argc, char * argv[])
{
	srand(time(NULL));
#pragma region INICJACJA OKNA
	glutInit(&argc, argv);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(600, 400);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutGameModeString("1920x1080:32@144");
#pragma endregion





#pragma region INICJACJA DZWIEKU
	alDevice = alcOpenDevice(NULL);

	if (!alDevice) {
		cout << "Nie mozna odtworzyc dzwieku\n" << endl;
		return 1;
	}
	alContext = alcCreateContext(alDevice, NULL);
	alcMakeContextCurrent(alContext);
#pragma endregion

	void KeyboardSpecial(int key, int x, int y);

	cout << "LADOWANIE GRY. PROSZE O CIERPLIWOSC...\n";

#pragma region INICJACJA GLUT
	// start fullscreen game mode
	//glutEnterGameMode();
	glutCreateWindow("Zombie Apocalypse");
	glutFullScreen();

	GLenum err = glewInit();

#pragma region INICJACJA SHADERÓW


#pragma endregion


	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(KeyboardSpecial);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(mouseButton);
	glutTimerFunc(17, OnTimer, 0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glEnable(GL_TEXTURE_2D);



	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(mouseX, mouseY);
	glutSetCursor(GLUT_CURSOR_NONE);


#pragma endregion

#pragma region INICJACJA SCENY
	Scene = new CScene();
	Scene->Initialize();
#pragma endregion

	glutMainLoop();

	return 0;
}

void KeyboardSpecial(int key, int x, int y) {
	int SpecialKey = glutGetModifiers();
	cout << SpecialKey<<endl;

}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
	//	cout << "NACISNIETO LEWY PRZYCISK\n";
		Scene->Player.left_mouse_button = true;
		// when the button is released
		if (state == GLUT_UP) {
			Scene->Player.left_mouse_button = false;
		}
		else {

		}
	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		Scene->Player.right_mouse_button = true;

		if (state == GLUT_UP) {
			Scene->Player.right_mouse_button = false;
		}

	}
}

void OnReshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(65.0f, (float)width / height, .01f, 100.0f);
	

}

void OnRender(void)
{

	T = glutGet(GLUT_ELAPSED_TIME);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	//game_sound->Render();
	Scene->Render();


#pragma endregion
	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
	
}

void OnTimer(int id)
{

	

	T = glutGet(GLUT_ELAPSED_TIME); // Ile milisekund uplynelo od momentu uruchomienia programu?
	Scene->Update();
	glutTimerFunc(17, OnTimer, 0);
}

#pragma region Obsluga wejscia


void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		if (key >= 'A' && key <= 'Z')
		{
			keystate[key] = false;

			key += 32;

		}
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
	if (key >= 'A' && key <= 'Z')
	{
		key += 32;
	}
	keystate[key] = false;
}

void OnMouseMove(int x, int y) {
	mouseX = x;
	mouseY = y;
}

#pragma endregion