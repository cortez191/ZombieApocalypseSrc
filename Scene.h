#pragma once

struct model {
	GLuint Building_model;
	CTexture *Building_texture;
	float polozenie[3];
	float scale[3];
	float rotate[4];
};


// Scena - Jest to podstawowy element organizuj¹cy hierarchiê obiektów w grze.
// Z za³o¿enia, w danym momencie powinna istnieæ tylko jedna scena.
// W sytuacji gdy scen mo¿e byæ wiêcej, dobrze jest utworzyæ klasy dziedzicz¹ce po tej.
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
	CTerrain * Terrain; // Teren - czyli w naszym przyk³adzie trawiasty quad.
	CPlayer Player; // Stan gracza.

	// Wszystkie obiekty na scenie, wektor na podstawie którego bêdzie mo¿na
	// po nich ³atwo iterowaæ, np. w celu ich narysowania.
	vector<CSceneObject *> * Objects;

	CScene(void); // Konstruktor.
	~CScene(void); // Destruktor.
	void LoadBuildings();
	void Initialize(void); // Inicjalizacja (wywo³ywana raz).
	void Update(void); // Aktualizacja œwiata.
	void Render(void); // Rysowanie ca³ej sceny.
	bool DrawCollisions; // Czy maj¹ byæ rysowane kolizje (do debugowania, klawisz "K")?
	bool DrawNormals; // Czy maj¹ byæ rysowane wektory normalne (do debugowania, klawisz "N")?
	vec3 LastCollisionPoint; // Pozycja ostatniej kolizji.
	bool MarkCollision; // Czy ju¿ zaistnia³a jakakolwiek kolizja warta narysowania?

};

