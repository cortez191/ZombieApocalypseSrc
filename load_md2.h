#pragma once


class Model_MD2
{
public:

	void LoadPCX(char *textureFilename);
	int Load(char *filename, char* textureFilename);
	void Draw();
	void Play(int animation, int N);


	Model_MD2();

	float Points[1000000];
	float Faces_Triangles[512][14096];
	float Normals[1000000];
	float Faces_Textures[512][14096];

	float TextureCoords[120048];

	int TotalConnectedPoints;
	int TotalConnectedTriangles;

	int Scale;
	int AngleX, AngleY, AngleZ;


private:
	typedef struct _MD2_Header
	{
		int ident;        // identifies as quake II header  (IDP2)
		int version;      // mine is 8
		int skinwidth;    // width of texture
		int skinheight;   // height of texture
		int framesize;    // number of bytes per frame
		int numSkins;     // number of textures
		int numXYZ;       // number of points
		int numST;        // number of texture
		int numTris;      // number of triangles
		int numGLcmds;
		int numFrames;    // total number of frames
		int offsetSkins;  // offset to skin names (64 bytes each)
		int offsetST;     // offset of texture s-t values
		int offsetTris;   // offset of triangle mesh
		int offsetFrames; // offset of frame data (points)
		int offsetGLcmds;
		int offsetEnd;    // end of file
	} MD2_Header;

	typedef struct _framePoint
	{
		unsigned char v[3];             // the vertex
		unsigned char lightNormalIndex;
	} framePoint;

	typedef struct _frame
	{
		float scale[3];                 // vetex scaling
		float translate[3];             // vertex translation
		char name[16];                  // name of this model
		framePoint fp[1];               // start of a list of framePoints
	} frame;

	typedef struct _mesh
	{
		unsigned short meshIndex[3];     // indices to triangle vertices
		unsigned short stIndex[3];       // indices to texture coordinates
	} mesh;

	int framenr;
	int updatecounter;
	frame *frm;

	int frame_length[70];
	int frame_start[20];
	int animation;

	int texWidth;
	int texHeight;
	int imgWidth;
	int imgHeight;
	unsigned char* texture;
	GLuint	texturen[1];
};


typedef struct _pcxHeader
{
	short id[2];
	short offset[2];
	short size[2];
} pcxHeader;

struct Mesh_UV
{
	unsigned short s;
	unsigned short t;
};

