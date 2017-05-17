#pragma once
#ifndef GLSHADER_H
#define GLSHADER_H

class Shading {

public:
	GLuint LoadShader(const char *vertex_path, const char *fragment_path);
	string readFile(const char *filePath);


};

#endif