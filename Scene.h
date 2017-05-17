#pragma once

struct model {
	GLuint Building_model;
	CTexture *Building_texture;
	float polozenie[3];
	float scale[3];
	float rotate[4];
};


// Scena - Jest to podstawowy element organizuj�cy hierarchi� obiekt�w w grze.
// Z za�o�enia, w danym momencie powinna istnie� tylko jedna scena.
// W sytuacji gdy scen mo�e by� wi�cej, dobrze jest utworzy� klasy dziedzicz�ce po tej.
class CScene
{
public:

	model *buildings;

	GLuint tree;
	vec3 tree_pos[50];
	CTexture *tree_tex;
	int n = 4;
	int SpecialKey;
	CSkydome * Skydome; // Skydome - niebo.
	CTerrain * Terrain; // Teren - czyli w naszym przyk�adzie trawiasty quad.
	CPlayer Player; // Stan gracza.

	// Wszystkie obiekty na scenie, wektor na podstawie kt�rego b�dzie mo�na
	// po nich �atwo iterowa�, np. w celu ich narysowania.
	vector<CSceneObject *> * Objects;

	CScene(void); // Konstruktor.
	~CScene(void); // Destruktor.
	void LoadBuildings();
	void Initialize(void); // Inicjalizacja (wywo�ywana raz).
	void Update(void); // Aktualizacja �wiata.
	void Render(void); // Rysowanie ca�ej sceny.
	bool DrawCollisions; // Czy maj� by� rysowane kolizje (do debugowania, klawisz "K")?
	bool DrawNormals; // Czy maj� by� rysowane wektory normalne (do debugowania, klawisz "N")?
	vec3 LastCollisionPoint; // Pozycja ostatniej kolizji.
	bool MarkCollision; // Czy ju� zaistnia�a jakakolwiek kolizja warta narysowania?

};

