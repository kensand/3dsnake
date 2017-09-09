#include "ObjectLoader.hpp"



Object::Object(const char * filename){
  std::vector<GLfloat *> lvertices;
  std::vector<GLfloat *> luvs;
  std::vector<GLfloat *> lnorms;
  this.numVertices = lvertices.size();
  if(!loadOBJ(filename, lvertices, luvs, lnorms)){
    printf("Error loading file: %s\n", filename);
    throw(filename);
  }
  this.verticies = new Vertex[numVerticies];
  for(int i = 0; i < lvertices.size(); i++){
    //printf("%d, %d, %d\n", lvertices[i][0], lvertices[i][1], lvertices[i][2]);
    for(int j = 0; j < dims; j++){
      vertices[i].position[j] = lvertices[i][j];

      //temp color settings
      //TODO actually implement color
      if(lvertices[i][j] >= -1. && lvertices[i][j] <= 1.){
        vertices[i].color[j] = abs(lvertices[i][j] / 1.0);
      }
      else{
        vertices[i].color[j] = 1.0;
      }
      vertices[i].color[3] = 1.0;
    }
  }
}

Object::~Object(){
  delete[] verticies;
}

template <T>
void Object::setPosition(T x, T y, T z){
  this.Position[0] = (GLfloat) x;
  this.Position[1] = (GLfloat) y;
  this.Position[2] = (GLfloat) z;
  this.update();
}

template <T>
void Object::setPosition(T coords){
  this.Position[0] = (GLfloat) coords[0];
  this.Position[1] = (GLfloat) coords[1];
  this.Position[2] = (GLfloat) coords[2];
  this.update();
}

template <T>
void Object::setRotation(T x, T y, T z){
  this.Rotation[0] = (GLfloat) x;
  this.Rotation[1] = (GLfloat) y;
  this.Rotation[2] = (GLfloat) z;
  this.update();
}

template <T>
void Object::setRotation(T axisRot){
  this.Rotation[0] = (GLfloat) axisRot[0];
  this.Rotation[1] = (GLfloat) axisRot[1];
  this.Rotation[2] = (GLfloat) axisRot[2];
  this.update();
}

vmath::vec3 Object::getRotation(){
  return vmath::vec3(Rotation[0], Rotation[1], Rotation[2]);
}

vmath::vec3 Object::getPosition(){
  return vmath::vec3(Rotation[0], Rotation[1], Rotation[2]);
}

vmath::mat4 Object::getModelMatrix(){
  return modelMatrix;
}


void Object::update(){
  vmath::mat4 ModelS = vmath::scale(this.scale);
  vmath::mat4 ModelR = vmath::rotate(this.Rotation[0], this.Rotation[1], this.Rotation[2]);
  vmath::mat4 ModelT = vmath::translate(this.Position[0], this.Position[1], this.Position[2]);
  this.modelMatrix = ModelT * ModelR * ModelS;
}