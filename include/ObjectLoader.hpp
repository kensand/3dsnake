#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <vector>
#include "vgl.h"
#include <GLFW/glfw3.h>

bool loadOBJ(
	const char * path, 
	std::vector<GLfloat *> & out_vertices, 
	std::vector<GLfloat *> & out_uvs, 
	std::vector<GLfloat *> & out_normals
);



bool loadAssImp(
	const char * path, 
	std::vector<unsigned short> & indices,
	std::vector<GLfloat *> & vertices,
	std::vector<GLfloat *> & uvs,
	std::vector<GLfloat *> & normals
);

#endif
