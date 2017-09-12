#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.hpp"
#include "ObjectLoader.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <X11/Xlib.h>

struct Vertex{
  GLfloat color[4];
  GLfloat position[4];
  Vertex(){
    for(int i = 0; i < 4; i++){
      this->color[i] = 0.f;
      this->position[i] = 0.f;
    }
  }

  Vertex(const Vertex& v){
    for(int i = 0; i < 4; i++){
      this->color[i] = v.color[i];
      this->position[i] = v.position[i];
    }
  }
};

class Object{
public:
  Object(const char * filename);
  ~Object();
  Object(const Object& o);
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
  GLfloat getScale();
  vmath::mat4 getModelMatrix();

  size_t getDataSize();

  Vertex * getVertices();
  GLuint getNumVertices();
  void draw();



  std::vector<GLfloat *> lvertices;


  std::vector<GLfloat *> vecuvs;

  std::vector<GLfloat *> normvec;

private:
  Vertex * vertices;
  GLuint numVertices;
  GLfloat scale;
  GLfloat Position[3];
  GLfloat Rotation[3];
  vmath::mat4 modelMatrix;

  GLuint dims = 3;
  GLuint color_dims = 4;
  void update();
};
