#include "vgl.h"
#include "vmath.h"
#include "ObjectLoader.hpp"
struct Vertex{
  GLfloat color[4];
  GLfloat position[4];
};

class Object{
public:
  Object(const char * filename);
  ~Object();

  template <T>
  void setPosition(T x, T y, T z);

  template <T>
  void setPosition(T coords);

  template <T>
  void setRotation(T x, T y, T z);

  template <T>
  void setRotation(T axisRot);

  vmath::vec3 getRotation();
  vmath::mat4 getModelMatrix();

private:
  Vertex * verticies;
  GLuint numVerticies;
  GLfloat scale;
  GLfloat Position[3];
  GLfloat Rotation[3];
  vmath::mat4 modelMatrix;
  void update();
}
