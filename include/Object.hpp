
#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.hpp"
#include "ObjectLoader.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <X11/Xlib.h>





struct VertexData{
  GLfloat color[4];
  GLfloat position[4];
};




class Object{
public:

  enum VAO_IDs { Triangles, NumVAOs };
  enum Buffer_IDs { ArrayBuffer, NumBuffers };
  enum Attrib_IDs { vPosition = 0, vColor = 1};
  //char * VarNames[] = {"vPosition", "vColor"};
  GLuint VarIndicies[2] = {vPosition, vColor};
  int NumVars = 2;
  GLuint VAOs[NumVAOs];
  GLuint Buffers[NumBuffers];
  GLuint dims = 3;
  GLuint color_dims = 4;
  GLuint NumVertices;
  GLuint modelViewLoc;
  GLuint ambientLoc;
  GLfloat drawDistance;

  vmath::mat4 modelMatrix;
  vmath::vec3 ModelLocation;
  vmath::vec3 ModelRotation;
  GLfloat ModelScale;

  void init(std::string objFile, vmath::vec3 location=vmath::vec3(0.f,0.f,0.f), vmath::vec3 rotation=vmath::vec3(0.f,0.f,0.f), GLfloat scale=1.0f);

  void display( vmath::mat4 ViewPerspective );




  template <typename T>
  void setPosition(T x, T y, T z);

  template <typename T>
  void setPosition(T coords);

  template <typename T>
  void setRotation(T x, T y, T z);

  template <typename T>
  void setRotation(T axisRot);


  vmath::vec3 getRotation();
  vmath::vec3 getPosition();
  vmath::mat4 getModelMatrix();
  void update();
  GLfloat getScale();
  void setScale(GLfloat scale);


};
