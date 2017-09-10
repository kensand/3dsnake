#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.hpp"
#include "ObjectLoader.hpp"
#include "object.hpp"
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <X11/Xlib.h>


Object::Object(const char * filename){

  this->numVertices = this->lvertices.size();
  if(!loadOBJ(filename, this->lvertices, this->vecuvs, this->normvec)){
    printf("Error loading file: %s\n", filename);
    throw(filename);
  }
  this->vertices = new Vertex[numVertices];
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



  //setup the opengl VAOS

  /*
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
               vertices, GL_STATIC_DRAW);

  glVertexAttribPointer( vColor, color_dims, GL_FLOAT,
                         GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
  glVertexAttribPointer(vPosition, dims, GL_FLOAT,
                        GL_FALSE, sizeof(Vertex),
                        BUFFER_OFFSET(sizeof(GLfloat) * color_dims));
  glEnableVertexAttribArray( vPosition );
  glEnableVertexAttribArray(vColor);
  */
}

void Object::draw(){

}
GLuint Object::getNumVertices(){
  return this->numVertices;
}

GLfloat Object::getScale(){
  return this->scale;
}

Object::~Object(){
  delete vertices;
}

Object::Object(const Object& o){
  this->vertices = new Vertex[o.numVertices];
  for(int i = 0; i< o.numVertices; i++){
    this->vertices[i] = o.vertices[i];
  }
  this->numVertices = o.numVertices;
  for(int i = 0; i < 3; i++){
    this->Position[i] = o.Position[i];
    this->Rotation[i] = o.Rotation[i];
  }
  this->scale = o.scale;
}

template <typename T>
void Object::setPosition(T x, T y, T z){
  this->Position[0] = (GLfloat) x;
  this->Position[1] = (GLfloat) y;
  this->Position[2] = (GLfloat) z;
  this->update();
}

template <typename T>
void Object::setPosition(T coords){
  this->Position[0] = (GLfloat) coords[0];
  this->Position[1] = (GLfloat) coords[1];
  this->Position[2] = (GLfloat) coords[2];
  this->update();
}

template <typename T>
void Object::setRotation(T x, T y, T z){
  this->Rotation[0] = (GLfloat) x;
  this->Rotation[1] = (GLfloat) y;
  this->Rotation[2] = (GLfloat) z;
  this->update();
}

template <typename T>
void Object::setRotation(T axisRot){
  this->Rotation[0] = (GLfloat) axisRot[0];
  this->Rotation[1] = (GLfloat) axisRot[1];
  this->Rotation[2] = (GLfloat) axisRot[2];
  this->update();
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

size_t Object::getDataSize(){
  return sizeof(vertices);
}

Vertex * Object::getVertices(){
  return this->vertices;
}

void Object::update(){
  vmath::mat4 ModelS = vmath::scale(this->scale);
  vmath::mat4 ModelR = vmath::rotate(this->Rotation[0], this->Rotation[1], this->Rotation[2]);
  vmath::mat4 ModelT = vmath::translate(this->Position[0], this->Position[1], this->Position[2]);
  this->modelMatrix = ModelT * ModelR * ModelS;
}
